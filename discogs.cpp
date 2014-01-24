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
Discogs::Discogs(QObject *parent) :
    QObject(parent)
{
}

QString Discogs::RequeteAlbums(QString rech)
{
    QString adresse= "http://api.discogs.com/database/search?barcode="+rech;
    const QUrl url = QUrl(adresse);
    const QNetworkRequest requete(url);
    QNetworkAccessManager *m = new QNetworkAccessManager;
    QNetworkReply *r = m->get(requete);

    //on attend que le signal finished soit reçu
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //on va lire ligne par ligne, jusqu'à trouver l'id
    while (!r->atEnd()) {
        QString pageWeb=r->readLine();
        QStringList parsing=pageWeb.split("\"id\": ");
        QStringList pars=parsing[1].split("}");
       return pars[0];
    }
}
AlbumGestion* Discogs::RequeteInfosAlbum(QString chemin)
{
    AlbumGestion* album = new AlbumGestion;

    QString adresse= "http://api.discogs.com/masters/"+chemin;
    const QUrl url = QUrl(adresse);
    const QNetworkRequest requete(url);
    QNetworkAccessManager *m = new QNetworkAccessManager;
    QNetworkReply *r = m->get(requete);

    //on attend que le signal finished soit reçu
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //Le parsing débute ici: le résultat va être lu ligne par ligne
    while (!r->atEnd()) {

        QString pageWeb=r->readLine();

        //On récupère le titre de l'album
        QStringList pars=pageWeb.split("title\": \"");
        QStringList par2=pars[1].split("\"");
        album->Album= accents(par2[0]);

        //On récupère le nom de l'artiste
        pars=pageWeb.split("artists\": [{\"join\": \"\", \"name\": \"");
        par2=pars[1].split("\"");
        album->Artiste=accents(par2[0]);

        QStringList parsing=pageWeb.split("\"images\": [{\"uri\": \"");

        //On récupère l'année
        QStringList temp=parsing[0].split("\"year\": ");
        QStringList temp1=temp[1].split(",");
        album->Annee= temp1[0];

        //On récupère la pochette
        if (parsing.size()>1) {
            QStringList images=parsing[1].split("\"");
            QNetworkRequest toto( QUrl::fromEncoded( images[0].toAscii() ) );
            toto.setAttribute( QNetworkRequest::User, images[0] );
            QNetworkReply* r = m->get( toto );
            //on attend que le signal finished soit reçu
            QEventLoop loop;
            QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            QImage image;
            image.loadFromData((r->readAll()));
            album->pochette=image;
        }
        //On récupère les titres
        QStringList Web=pageWeb.split("tracklist");
        parsing=Web[1].split("\"title\": \"");
        int cpt=2;
        //Et la durée de chaque titre
        QString duree;
        QStringList durr=parsing[1].split("duration\": \"");
        if(durr.size()!=0) {
            QStringList dure=durr[1].split("\"");
            duree = dure[0];
        }
        while (cpt<parsing.size())
        {
            QStringList titre1 = parsing[cpt].split("\"");
            QString titreLisible = accents(titre1[0]);

            if(duree=="")
            {
                duree="0:00";
            }

            TitreGestion titre;
            titre.Duree=duree;
            titre.Num_Piste=cpt-2;
            titre.Titre=titreLisible;

            album->titres << titre;

          //  album->titres << titreLisible << duree;
            duree=titre1[4];
            cpt++;
        }
    }
    return album;
}
QString Discogs::accents(QString nom)
{
    QString nomretravaille;

    QString temp= nom.toUtf8().replace("\\u00e9", "é");
    temp=temp.replace("\\u00ea","ê");
    temp=temp.replace("\\u00e0","à");
    temp=temp.replace("\\u0153","oe");
    temp=temp.replace("\\u00c2","â");
    temp=temp.replace("\\u00c0","à");
    temp=temp.replace("\\u00c9","é");
    temp=temp.replace("\\u00c8","è");
    temp=temp.replace("\\u00ca","ê");
    temp=temp.replace("\\u00f4","ô");
    temp=temp.replace("\\u00ee","î");
    temp=temp.replace("\\u00f9","ù");
    temp=temp.replace("\\u00c7","ç");

    nomretravaille=temp.replace("\\u00e8","è");

    return nomretravaille;
}

