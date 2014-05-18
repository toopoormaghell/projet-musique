#include "discogs.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QStringList>
#include <QEventLoop>
#include "util.h"
#include "BDDcommun.h"
#include <QDebug>
#include "kqoauthsingleton.h"
#include <QtXml/QDomDocument>
#include <QtXml/qdom.h>
#include <QMessageBox>

Discogs::Discogs(QObject *parent) :
    QObject(parent)
{

}
AlbumGestion Discogs::RequeteAlbums(QString rech)
{
    theOAuthSingleton.makeRequest( "release/search", "ean", rech );

    //on attend que le signal finished soit reçu
    QEventLoop loop;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();

    AlbumGestion alb= LectureXMLSearch(theOAuthSingleton.getResponse());
    if ( alb.Album!="Non trouvé")
    {
        //On récupère l'artiste
        alb.Artiste=RecupererArtistes(QString::number(alb.Id_Album));


        //On récupère la pochette
        QByteArray Poch = LirePochette(QString::number(alb.Id_Album));
        alb.ErreurPochette = LectureErreurPochette(Poch);
        if (alb.ErreurPochette)
        {
            alb.Chem_Poch_Alt="release/"+QString::number(alb.Id_Album)+"/pictures";
            QImage image("./Pochettes/def.jpg");
            alb.Pochette= image;
        } else {
            alb.Pochette=LectureXMLPochette(Poch);
        }

        //On récupère les titres
        alb.titres=RecupererTitres(QString::number(alb.Id_Album));

        if(alb.titres.isEmpty())
        {
            QString Id_Album = RecupererId_Album(QString::number(alb.Id_Album));
            alb.titres=RecupererTitresAlbums(Id_Album);
        }
    }
    return alb;
}
QString Discogs::RecupererId_Album(QString Id_Album)
{
    QString req="release/"+Id_Album+"/album";
    theOAuthSingleton.makeRequest(req);
    QEventLoop loop2;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop2, SLOT(quit()));
    loop2.exec();
    return LectureXMLId_Album(theOAuthSingleton.getResponse());
}

QString Discogs::RecupererArtistes(QString Id_Album)
{
    QString req="release/"+Id_Album+"/artists";
    theOAuthSingleton.makeRequest(req);
    QEventLoop loop3;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop3, SLOT(quit()));
    loop3.exec();
    return LectureXMLArtiste(theOAuthSingleton.getResponse());
}

bool Discogs::LectureErreurPochette(QByteArray fich)
{
    bool erreur=false;
    QDomDocument doc;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <site>
        if(racine.tagName() == "code")
        {
            if ( racine.text()=="-1")
            {
                erreur=true;
            }

        }
        racine=racine.nextSiblingElement();
    }

    return erreur;

}

QByteArray Discogs::LirePochette(QString Id_Album)
{
    QString req="release/"+Id_Album+"/pictures";
    theOAuthSingleton.makeRequest(req);
    QEventLoop loop4;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop4, SLOT(quit()));
    loop4.exec();

    return theOAuthSingleton.getResponse();
}
QList<TitreGestion> Discogs::RecupererTitresAlbums(QString Id_Album)
{
    //On récupère toutes les releases disponibles de l'album
    QStringList Releases;
    QString req="album/"+Id_Album+"/releases";
    theOAuthSingleton.makeRequest(req);
    QEventLoop loop4;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop4, SLOT(quit()));
    loop4.exec();

    int cpt=LectureXMLPages(theOAuthSingleton.getResponse());
    int pageactuelle=1;
    Releases= LectureXMLReleases(theOAuthSingleton.getResponse());

    while(cpt-pageactuelle>0)
    {
        theOAuthSingleton.makeRequest(req,"page",QString::number(pageactuelle+1));
        QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop4, SLOT(quit()));
        loop4.exec();
        Releases <<LectureXMLReleases(theOAuthSingleton.getResponse());
        pageactuelle++;
    }

    // Pour chaque release, on voit si les titres sont disponibles
    QList<TitreGestion> titres;
    int Id_Release=0;
    while( Id_Release<Releases.count()&&titres.isEmpty())
    {
        QList<TitreGestion> temp;
        QString affichage;
        temp= RecupererTitres(Releases[Id_Release]);
        if ( !temp.isEmpty()) {
            for (int compTitres=0;compTitres<temp.count();compTitres++)
            {
                affichage += temp[compTitres].Num_Piste + " - "+ temp[compTitres].Titre+"\n";
            }
            QMessageBox::StandardButton clickedButton = QMessageBox::information(0,"Titre",affichage,QMessageBox::Ok | QMessageBox::Cancel);
            if ( clickedButton == QMessageBox::Ok )
            {
                titres=temp;
            }
        }
        Id_Release++;
    }
    return titres;
}


QList<TitreGestion> Discogs::RecupererTitres(QString Id_Album)
{
    QList<TitreGestion> titres;
    QString req="release/"+Id_Album+"/tracks";
    theOAuthSingleton.makeRequest(req);
    QEventLoop loop;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    titres=LectureXMLTitres(theOAuthSingleton.getResponse());

    int cpt=LectureXMLPages(theOAuthSingleton.getResponse());
    qDebug() << cpt;
    int compteur=1;
    while(cpt-compteur>0)
    {
        theOAuthSingleton.makeRequest(req,"page",QString::number(compteur+1));
        QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
        loop.exec();
        titres<<LectureXMLTitres(theOAuthSingleton.getResponse());
        compteur++;
    }
    return titres;
}

int Discogs::LectureXMLPages(QByteArray fich)
{
    int cpt;
    QDomDocument doc;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <site>
        if(racine.tagName() == "pageCount")
        {
            cpt=racine.text().toInt();
        }
        racine=racine.nextSiblingElement();
    }

    return cpt;

}
QStringList Discogs::LectureXMLReleases(QByteArray fich)
{
    QDomDocument doc;
    QStringList alb;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <site>
        if(racine.tagName() == "data")
        {
            // On récupère le premier enfant de l'élément site c'est a dire <nom> ou <url>
            QDomElement unElement = racine.firstChildElement();

            // On parcourt tous les enfants de l'élément <site>
            while(!unElement.isNull())
            {
                // Si l'enfant de l'élément site est l'élément <nom>
                if(unElement.tagName() == "item")
                {
                    QDomElement donnees = unElement.firstChildElement();

                    while(!donnees.isNull())
                    {
                        if(donnees.tagName()=="id")
                        {
                            alb << donnees.text();
                        }

                        donnees =donnees.nextSiblingElement();
                    }
                }
                // Permet d'aller au prochain enfant de <site> et de poursuivre la boucle
                unElement = unElement.nextSiblingElement();
            }
        }
        // On va à l'élément fils de <root> suivant
        racine = racine.nextSiblingElement();
    }

    return alb;
}

AlbumGestion Discogs::LectureXMLSearch(QByteArray fich)
{
    QDomDocument doc;
    AlbumGestion alb;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <site>
        if(racine.tagName() == "data")
        {
            // On récupère le premier enfant de l'élément site c'est a dire <nom> ou <url>
            QDomElement unElement = racine.firstChildElement();

            // On parcourt tous les enfants de l'élément <site>
            while(!unElement.isNull())
            {
                // Si l'enfant de l'élément site est l'élément <nom>
                if(unElement.tagName() == "item")
                {
                    QDomElement donnees = unElement.firstChildElement();

                    while(!donnees.isNull())
                    {
                        if(donnees.tagName()=="id")
                        {
                            alb.Id_Album= donnees.text().toInt();
                        }
                        if(donnees.tagName()=="title")
                        {
                            alb.Album=donnees.text();
                        }
                        if(donnees.tagName()=="release_date")
                        {
                            QString temp = donnees.text();
                            temp.resize(4);
                            alb.Annee=temp;
                        }
                        donnees =donnees.nextSiblingElement();
                    }
                }
                // Permet d'aller au prochain enfant de <site> et de poursuivre la boucle
                unElement = unElement.nextSiblingElement();
            }
        }
        // On va à l'élément fils de <root> suivant
        racine = racine.nextSiblingElement();
    }
    if (alb.Album.isNull())
    {
        alb.Album="Non trouvé";
    }

    return alb;
}
QList<TitreGestion> Discogs::LectureXMLTitres(QByteArray fich)
{

    QList<TitreGestion> Titres;
    QDomDocument doc;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <data>
        if(racine.tagName() == "data")
        {
            // On récupère le premier enfant de l'élément site c'est a dire <nom> ou <url>
            QDomElement unElement = racine.firstChildElement();

            // On parcourt tous les enfants de l'élément <data>
            while(!unElement.isNull())
            {
                // Si l'enfant de l'élément site est l'élément <item>
                if(unElement.tagName() == "item")
                {

                    TitreGestion titre;
                    QDomElement donnees = unElement.firstChildElement();
                    while(!donnees.isNull())
                    {
                        if(donnees.tagName()=="track_number")
                        {
                            titre.Num_Piste=donnees.text().toInt();
                        }
                        if(donnees.tagName()=="title")
                        {
                            titre.Titre=donnees.text();
                        }
                        if(donnees.tagName()=="length")
                        {
                            titre.Duree=donnees.text();
                        }
                        donnees =donnees.nextSiblingElement();

                    }
                    Titres<<titre;
                }
                // Permet d'aller au prochain enfant de <site> et de poursuivre la boucle
                unElement = unElement.nextSiblingElement();

            }
        }
        // On va à l'élément fils de <root> suivant
        racine = racine.nextSiblingElement();
    }
    return Titres;
}
QString Discogs::LectureXMLId_Album(QByteArray fich)
{
    QDomDocument doc;
    QString Id_Album;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <data>
        if(racine.tagName() == "data")
        {
            // On récupère le premier enfant de l'élément site c'est a dire <nom> ou <url>
            QDomElement unElement = racine.firstChildElement();

            // On parcourt tous les enfants de l'élément <data>
            while(!unElement.isNull())
            {
                // Si l'enfant de l'élément site est l'élément <item>
                if(unElement.tagName() == "item")
                {
                    QDomElement donnees = unElement.firstChildElement();
                    while(!donnees.isNull())
                    {

                        if(donnees.tagName()=="id")
                        {
                            Id_Album= donnees.text();

                        }
                        donnees =donnees.nextSiblingElement();
                    }
                }
                // Permet d'aller au prochain enfant de <site> et de poursuivre la boucle
                unElement = unElement.nextSiblingElement();
            }
        }
        // On va à l'élément fils de <root> suivant
        racine = racine.nextSiblingElement();
    }
    return Id_Album;
}

QString Discogs::LectureXMLArtiste(QByteArray fich)
{
    QDomDocument doc;
    QString Artiste;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <data>
        if(racine.tagName() == "data")
        {
            // On récupère le premier enfant de l'élément site c'est a dire <nom> ou <url>
            QDomElement unElement = racine.firstChildElement();

            // On parcourt tous les enfants de l'élément <data>
            while(!unElement.isNull())
            {
                // Si l'enfant de l'élément site est l'élément <item>
                if(unElement.tagName() == "item")
                {
                    QDomElement donnees = unElement.firstChildElement();
                    QString Nom;
                    while(!donnees.isNull())
                    {

                        if(donnees.tagName()=="name")
                        {
                            Nom= donnees.text();

                        }
                        if(donnees.tagName()=="link")
                        {
                            QDomElement link=donnees.firstChildElement();
                            while(!link.isNull())
                            {
                                if(link.tagName()=="item")
                                {
                                    if(link.text()=="Main")
                                    {
                                        Artiste= Nom;
                                    }
                                }
                                link=link.nextSiblingElement();
                            }
                        }

                        donnees =donnees.nextSiblingElement();
                    }
                }
                // Permet d'aller au prochain enfant de <site> et de poursuivre la boucle
                unElement = unElement.nextSiblingElement();
            }
        }
        // On va à l'élément fils de <root> suivant
        racine = racine.nextSiblingElement();
    }
    return Artiste;
}
QImage Discogs::LectureXMLPochette(QByteArray fich)
{
    QDomDocument doc;
    QImage poch;

    // Ajoute le contenu du Qstring XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc.setContent(fich,false);

    // Ici, racine pointe sur l'élément <root> de notre document
    QDomElement racine = doc.documentElement();

    // Ici, racine pointe sur une fils de <root> c'est à dire <site>
    racine = racine.firstChildElement();

    //Boucle permettant la navigation dans le fichier XML
    while(!racine.isNull())
    {
        // Si on pointe sur un élément de type <data>
        if(racine.tagName() == "data")
        {
            // On récupère le premier enfant de l'élément site c'est a dire <nom> ou <url>
            QDomElement unElement = racine.firstChildElement();

            // On parcourt tous les enfants de l'élément <data>
            while(!unElement.isNull())
            {
                // Si l'enfant de l'élément site est l'élément <item>
                if(unElement.tagName() == "item")
                {
                    QDomElement donnees = unElement.firstChildElement();
                    QString Nom;
                    while(!donnees.isNull())
                    {
                        if(donnees.tagName()=="url")
                        {
                            poch= RecupererPochette(donnees.text());
                        }
                        donnees = donnees.nextSiblingElement();
                    }
                }
                unElement = unElement.nextSiblingElement();
            }
        }
        racine=racine.nextSiblingElement();
    }
    return poch;
}
QImage Discogs::RecupererPochette(QString lien)
{
    QImage poch;
    QNetworkRequest toto (QUrl::fromEncoded(lien.toAscii()));
    toto.setAttribute(QNetworkRequest::User,lien);
    QNetworkAccessManager *m=new QNetworkAccessManager;
    QNetworkReply* r= m->get(toto);
    //on attend que le signal finished soit recu
    QEventLoop loop;
    QObject::connect(r,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    poch.loadFromData(r->readAll());

    return poch;
}
