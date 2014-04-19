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

    //On récupère l'artiste
    QString req="release/"+QString::number(alb.Id_Album)+"/artists";
    theOAuthSingleton.makeRequest(req);
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    alb.Artiste=LectureXMLArtiste(theOAuthSingleton.getResponse());

    //On récupère la pochette
    req="release/"+QString::number(alb.Id_Album)+"/pictures";
    theOAuthSingleton.makeRequest(req);
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    alb.Pochette=LectureXMLPochette(theOAuthSingleton.getResponse());

    //On récupère les titres
    req="release/"+QString::number(alb.Id_Album)+"/tracks";
    theOAuthSingleton.makeRequest(req);
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    alb.titres=LectureXMLTitres(theOAuthSingleton.getResponse());

    int cpt=LectureXMLPages(theOAuthSingleton.getResponse());
    int compteur=1;
    while(cpt-compteur>0)
    {
        theOAuthSingleton.makeRequest(req,"page",QString::number(compteur+1));
        QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
        loop.exec();
        alb.titres<<LectureXMLTitres(theOAuthSingleton.getResponse());
        compteur++;
    }

    return alb;
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
                            alb.Annee=donnees.text();
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
