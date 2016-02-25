#include "rechercheurl.h"
#include <QObject>
#include <QtXml/QDomDocument>
#include <QtXml/qdom.h>
#include <QtNetwork>
#include <QMap>
#include "bddpoch.h"
#include "bddalbum.h"
#include "choixalbumphysdialog.h"
RechercheURL::RechercheURL(QObject *parent)
{
    Q_UNUSED(parent);
}

AlbumPhys RechercheURL::RequeteAlbums(QString rech,int Type)
{
    m_album.Type=Type;
    m_album.titres.clear();
    m_interaction = "Requete en cours...";
    emit test();
    //1ère étape, on récupère l'id, le nom de l'album et l'année
    QStringList temp;
    temp << "release/search"  << "ean" << rech;
    QMap<QString, QString> lecture =   Requete(temp);
    m_interaction= "Récupération du nom de l'album, de l'année faite.";
    emit test();
    m_album.Album = lecture["title"];
    QString annee = lecture["release_date"];
    annee.resize(4);
    m_album.Annee = annee.toInt();
    m_album.Id_Release = lecture["id"].toInt();

    //2ème étape, on s'occupe de l'artiste
    if (Type==1 || Type==3)
    {
        temp.clear();
        temp << "release/"+QString::number(m_album.Id_Release)+"/artists";
        lecture = Requete(temp);
        m_album.Artiste=lecture["name"];
        m_interaction= "Récupération du nom de l'artiste faite.";
        emit test();
    } else {
        m_album.Artiste="Artistes Divers";
        m_interaction= "Le type de l'album est une compilation.";
        emit test();
    }

    //3ème étape, on récupère les titres
    RecupererTitres();
    //4ème étape, on s'occupe de la pochette
    BDDPoch* toto = BDDPoch::recupererPoch(m_album.Album,m_album.Artiste);
    if (toto == NULL)
    {
        ChoixAlbumPhysDialog choixalbum(m_album.Artiste);
        choixalbum.exec();
        int id_alb=0;
        if( choixalbum.m_selection!=0)
        {
            id_alb=choixalbum.m_selection;
        }
        if (id_alb==0)
        {
            m_interaction= "Récupération de la pochette..."; emit test();
            temp.clear();
            temp <<"release/"+QString::number(m_album.Id_Release)+"/pictures";
            lecture =Requete(temp);
            RecupererPoch(lecture["url"]);
        } else {
            BDDAlbum* albu = BDDAlbum::RecupererAlbum(id_alb);
            m_album.Id_Album=albu->m_id;
            m_album.Poch=albu->m_pochette->m_image;
            m_album.Album=albu->m_nom;
        }

    } else {

        m_interaction= "La pochette existe déjà.";
        emit test();
        m_album.Poch=toto->m_image;
    }

    m_interaction= "Récupération de l'album réalisée. Affichage en cours...";
    emit test();

    return m_album;
}


void RechercheURL::RecupererPoch(QString lien)
{

    QNetworkRequest toto (QUrl::fromEncoded(lien.toLatin1()));
    toto.setAttribute(QNetworkRequest::User,lien);
    QNetworkAccessManager *m=new QNetworkAccessManager;
    QNetworkReply* r= m->get(toto);
    //on attend que le signal finished soit recu
    QEventLoop loop;
    QObject::connect(r,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    m_album.Poch.loadFromData(r->readAll());
}
QStringList RechercheURL::RequeteReleases(QStringList attributs)
{
    if (attributs.count()==3)
    {
        //theOAuthSingleton.makeRequest( attributs[0], attributs[1], attributs[2] );
    } else
    {
        //theOAuthSingleton.makeRequest( attributs[0] );
    }
    //on attend que le signal finished soit reçu
    QEventLoop loop;
    //QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    QStringList lecture/* = LectureXMLReleases(theOAuthSingleton.getResponse())*/;
    return lecture;

}

QMap<QString,QString> RechercheURL::Requete(QStringList attributs)
{
    if (attributs.count()==3)
    {
        //theOAuthSingleton.makeRequest( attributs[0], attributs[1], attributs[2] );
    } else
    {
        //theOAuthSingleton.makeRequest( attributs[0] );
    }
    //on attend que le signal finished soit reçu
    QEventLoop loop;
    //QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    QMap<QString, QString> lecture/* =   LectureXML(theOAuthSingleton.getResponse())*/;
    return lecture;

}
void RechercheURL::RequeteTitres(QStringList attributs)
{
    if (attributs.count()==3)
    {
        //theOAuthSingleton.makeRequest( attributs[0], attributs[1], attributs[2] );
    } else
    {
        //theOAuthSingleton.makeRequest( attributs[0] );
    }
    //on attend que le signal finished soit reçu
    QEventLoop loop;
    //QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    //LectureXMLTitres(theOAuthSingleton.getResponse());
}
void RechercheURL::LectureXMLTitres(QByteArray fichier)
{
    QXmlStreamReader reader(fichier);
    QString element;

    QList<TitresPhys> titres;
    TitresPhys titre_en_cours;
    int cpt=0;
    while (!reader.atEnd())
    {
        reader.readNext();
        switch(reader.tokenType())
        {

        case QXmlStreamReader::StartElement:
        {
            element = reader.name().toString();

            if (element == "item")
            {
                if (cpt!=0)
                {
                    titres << titre_en_cours;
                }
                cpt++;
            }

            break;
        }
        case QXmlStreamReader::Characters:
        {
            if (element=="length")
            {
                titre_en_cours.Duree= reader.text().toString();
            }
            if (element=="track_number")
            {
                titre_en_cours.Num_Piste=reader.text().toInt();
            }
            if (element=="title")
            {
                titre_en_cours.Titre=reader.text().toString();
            }
            if (element == "pageCount")
            {
                m_pages = reader.text().toInt();
            }
            if (element == "id")
            {
                titre_en_cours.id=reader.text().toString();

            }
            break;
        }
        case QXmlStreamReader::StartDocument :  break;
        case QXmlStreamReader::EndElement: break;
        case QXmlStreamReader::EndDocument: break;
        case QXmlStreamReader::NoToken: break;
        case QXmlStreamReader::Invalid: break;
        case QXmlStreamReader::Comment:break;
        case QXmlStreamReader::DTD:break;
        case QXmlStreamReader::EntityReference:break;
        case QXmlStreamReader::ProcessingInstruction:break;
        }
    }
    if (titre_en_cours.Titre!="")
    {
        titres << titre_en_cours;
    }
    m_album.titres << titres;

}
QStringList RechercheURL::LectureXMLReleases(QByteArray fichier)
{
    QStringList temp;
    QXmlStreamReader reader(fichier);
    QString element;

    while (!reader.atEnd())
    {
        reader.readNext();
        switch(reader.tokenType())
        {
        case QXmlStreamReader::StartElement:
        {
            element = reader.name().toString();
            break;
        }
        case QXmlStreamReader::Characters:
        {
            if ( element == "id")
            {
                temp << reader.text().toString();
            }
            break;
        }
        case QXmlStreamReader::StartDocument :  break;
        case QXmlStreamReader::EndDocument: break;
        case QXmlStreamReader::EndElement: break;
        case QXmlStreamReader::NoToken: break;
        case QXmlStreamReader::Invalid: break;
        case QXmlStreamReader::Comment:break;
        case QXmlStreamReader::DTD:break;
        case QXmlStreamReader::EntityReference:break;
        case QXmlStreamReader::ProcessingInstruction:break;
        }
    }
    return temp;
}

void RechercheURL::RecupererTitres()
{

    QString releasebonne= QString::number(m_album.Id_Release);

    //3ème étape, on s'occupe des titres
    m_interaction= "Récupération des titres en cours...";
    emit test();


    QStringList temp;
    temp <<"release/"+QString::number(m_album.Id_Release)+"/tracks";
    RequeteTitres(temp);

    //Si l'étape 3 n'a rien donné
    if ( m_album.titres.count()==0)
    {
        m_interaction= "Récupération des titres échouée. On vérifie les autres versions de l'album.";
        emit test();

        //On va chercher l'id de l'album
        temp.clear();
        temp << "release/"+QString::number(m_album.Id_Release)+"/album";
        QMap<QString, QString> lecture =   Requete(temp);

        m_album.Id_Album=lecture["id"].toInt();
        //On cherche maintenant toutes les releases de l'album
        temp.clear();
        temp << "album/"+QString::number(m_album.Id_Album)+"/releases";
        QStringList releases = RequeteReleases(temp);
        m_interaction= "Liste des releases créée.";
        emit test();

        int cpt=0;

        while (m_album.titres.count() == 0 )
        {
            if (cpt>=releases.count())
            {
                m_interaction= "Titres non récupérés.";
                emit test();
                break;
            }
            //On refait la troisième étape, on s'occupe des titres
            temp.clear();
            temp <<"release/"+releases[cpt]+"/tracks";
            RequeteTitres(temp);
            releasebonne = releases[cpt];
            cpt++;

        }
    }
    //On récupère les pages suivantes des titres
    for (int i=2;i<=m_pages;i++)
    {
        temp.clear();
        temp <<"release/"+releasebonne+"/tracks" << "page" << QString::number(i);
        RequeteTitres(temp);
    }

    if (m_album.titres.count()!=0)
    {
        m_interaction= "Titres récupérés.";
        emit test();
    }

    //Si le type de l'album est une compil, on récupère les artistes des titres
    if( m_album.Type==2)
    {

        for (int compt=0;compt<m_album.titres.count();compt++)
        {

            temp.clear();
            temp << "track/"+m_album.titres[compt].id+"/artists";
            QMap<QString, QString> lecture =   Requete(temp);
            m_album.titres[compt].Artiste=lecture["name"];
            m_interaction= "Récupération du nom de l'artiste du titre "+QString::number(compt)+" faite.";
            emit test();
        }
    }


}
QMap<QString, QString> RechercheURL::LectureXML(QByteArray fichier)
{
    QMap<QString,QString> temp;
    QXmlStreamReader reader(fichier);
    QString element;

    while (!reader.atEnd())
    {
        reader.readNext();
        switch(reader.tokenType())
        {
        case QXmlStreamReader::StartElement:
        {
            element = reader.name().toString();
            break;
        }
        case QXmlStreamReader::Characters:
        {
            temp.insert(element,reader.text().toString());
            if ( reader.text().toString()=="Main" || element=="format" )
            {
                return temp;
            }
            break;
        }
        case QXmlStreamReader::StartDocument :  break;
        case QXmlStreamReader::EndDocument:   break;
        case QXmlStreamReader::EndElement: break;
        case QXmlStreamReader::NoToken: break;
        case QXmlStreamReader::Invalid: break;
        case QXmlStreamReader::Comment:break;
        case QXmlStreamReader::DTD:break;
        case QXmlStreamReader::EntityReference:break;
        case QXmlStreamReader::ProcessingInstruction:break;
        }
    }
    return temp;
}

