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

QStringList Discogs::RequeteAlbums(QString rech)
{
    QString adresse= "http://api.discogs.com/database/search?barcode="+rech;
    const QUrl url = QUrl(adresse);
    const QNetworkRequest requete(url);
    QNetworkAccessManager *m = new QNetworkAccessManager;
    QNetworkReply *r = m->get(requete);
    QStringList resultat;
    //on attend que le signal finished soit re�u
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //on va lire ligne par ligne, jusqu'� trouver l'id
    while (!r->atEnd()) {
        QString pageWeb=r->readLine();
        QStringList parsing=pageWeb.split("\"master\", \"id\": ");

        if (parsing.count()!=1)
        {
            QStringList pars=parsing[1].split("}");
            resultat<< pars[0];
            resultat<<"masters";
        } else{
            parsing=pageWeb.split("\"release\", \"id\": ");
            if(parsing.count()!=1)
{            QStringList pars=parsing[1].split("}");
            resultat<< pars[0];
            resultat<<"releases";
            }
        }


    }

    return resultat;
}
AlbumGestion* Discogs::RequeteInfosAlbum(QString chemin,QString type)
{
    AlbumGestion* album = new AlbumGestion;

    QString adresse= "http://api.discogs.com/"+type+"/"+chemin;
    const QUrl url = QUrl(adresse);
    const QNetworkRequest requete(url);
    QNetworkAccessManager *m = new QNetworkAccessManager;
    QNetworkReply *r = m->get(requete);

    //on attend que le signal finished soit re�u
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //Le parsing d�bute ici: le r�sultat va �tre lu ligne par ligne
    while (!r->atEnd()) {

        QString pageWeb=r->readLine();

        //On r�cup�re le titre de l'album
        QStringList pars=pageWeb.split("title\": \"");
        QStringList par2=pars[1].split("\"");
        album->Album= accents(par2[0]);

        //On r�cup�re le nom de l'artiste
        pars=pageWeb.split("artists\": [{\"join\": \"\", \"name\": \"");
        par2=pars[1].split("\"");
        album->Artiste=accents(par2[0]);

        QStringList parsing=pageWeb.split("\"images\": [{\"uri\": \"");

        //On r�cup�re l'ann�e
        QStringList temp=parsing[0].split("\"year\": ");
        QStringList temp1=temp[1].split(",");
        album->Annee= temp1[0];

        //On r�cup�re la pochette
        if (parsing.size()>1) {
            QStringList images=parsing[1].split("\"");
            QNetworkRequest toto( QUrl::fromEncoded( images[0].toAscii() ) );
            toto.setAttribute( QNetworkRequest::User, images[0] );
            QNetworkReply* r = m->get( toto );
            //on attend que le signal finished soit re�u
            QEventLoop loop;
            QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            QImage image;
            image.loadFromData((r->readAll()));
            album->Pochette=image;
        }
        //On r�cup�re les titres
        QStringList Web=pageWeb.split("tracklist");
        parsing=Web[1].split("\"title\": \"");
        int cpt=1;
        //Et la dur�e de chaque titre
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
            titre.Num_Piste=cpt;
            titre.Titre=titreLisible;

            album->titres << titre;


            duree=titre1[4];
            cpt++;
        }
    }

    return album;
}
QString Discogs::accents(QString nom)
{
    QString nomretravaille;

    QString temp= nom.toUtf8().replace("\\u00e9", "�");
    temp=temp.replace("\\u00ea","�");
    temp=temp.replace("\\u00e0","�");
    temp=temp.replace("\\u0153","oe");
    temp=temp.replace("\\u00c2","�");
    temp=temp.replace("\\u00c0","�");
    temp=temp.replace("\\u00c9","�");
    temp=temp.replace("\\u00c8","�");
    temp=temp.replace("\\u00ca","�");
    temp=temp.replace("\\u00f4","�");
    temp=temp.replace("\\u00ee","�");
    temp=temp.replace("\\u00f9","�");
    temp=temp.replace("\\u00c7","�");
    temp=temp.replace("\\u00ef","�");
    temp=temp.replace("\\u00e7","�");

    nomretravaille=temp.replace("\\u00e8","�");

    return nomretravaille;
}

