#include "rechercheurl.h"
#include <QObject>
#include "kqoauthsingleton.h"
#include <QtXml/QDomDocument>
#include <QtXml/qdom.h>
#include <QtNetwork>
#include <QMap>

RechercheURL::RechercheURL(QObject *parent)
{
}

AlbumPhys RechercheURL::RequeteAlbums(QString rech)
{
    //1ère étape, on récupère l'id, le nom de l'album et l'année
    QStringList temp;
    temp << "release/search"  << "ean" << rech;
    QMap<QString, QString> lecture =   Requete(temp);

    m_album.Album = lecture["title"];
    QString annee = lecture["release_date"];
    annee.resize(4);
    m_album.Annee = annee.toInt();
    m_album.Id = lecture["id"].toInt();

    //2ème étape, on s'occupe de l'artiste
    temp.clear();
    temp << "release/"+QString::number(m_album.Id)+"/artists";
    lecture = Requete(temp);
    m_album.Artiste=lecture["name"];


    //3ème étape, on s'occupe des titres
    temp.clear();
    temp <<"release/"+QString::number(m_album.Id)+"/tracks";
    RequeteTitres(temp);
    for (int i=2;i<=m_pages;i++)
    {
        temp.clear();
        temp <<"release/"+QString::number(m_album.Id)+"/tracks" << "page" << QString::number(i);
        RequeteTitres(temp);
    }

    //4ème étape, on s'occupe de la pochette
    temp.clear();
    temp <<"release/"+QString::number(m_album.Id)+"/pictures";
    lecture =Requete(temp);

    RecupererPoch(lecture["url"]);

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

QMap<QString,QString> RechercheURL::Requete(QStringList attributs)
{
    if (attributs.count()==3)
    {
        theOAuthSingleton.makeRequest( attributs[0], attributs[1], attributs[2] );
    } else
    {
        theOAuthSingleton.makeRequest( attributs[0] );
    }
    //on attend que le signal finished soit reçu
    QEventLoop loop;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    QMap<QString, QString> lecture =   LectureXML(theOAuthSingleton.getResponse());

    return lecture;

}
void RechercheURL::RequeteTitres(QStringList attributs)
{
    if (attributs.count()==3)
    {
        theOAuthSingleton.makeRequest( attributs[0], attributs[1], attributs[2] );
    } else
    {
        theOAuthSingleton.makeRequest( attributs[0] );
    }
    //on attend que le signal finished soit reçu
    QEventLoop loop;
    QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
    loop.exec();
    LectureXMLTitres(theOAuthSingleton.getResponse());
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
        case QXmlStreamReader::StartDocument :  break;
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
            break;
        }
        case QXmlStreamReader::EndElement:
        {
            break;
        }
        case QXmlStreamReader::EndDocument:
            break;
        }
    }
    titres << titre_en_cours;
    m_album.titres << titres;
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
        case QXmlStreamReader::StartDocument :  break;
        case QXmlStreamReader::StartElement:
        {
            element = reader.name().toString();
            break;
        }
        case QXmlStreamReader::Characters:
        {
            temp.insert(element,reader.text().toString());

            break;
        }
        case QXmlStreamReader::EndElement:
        {
            break;
        }
        case QXmlStreamReader::EndDocument:
            break;
        }

    }
    return temp;
}

