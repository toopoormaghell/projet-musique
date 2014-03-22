#include "deezer.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include "util.h"
#include "BDDcommun.h"
#include <QDebug>

Deezer::Deezer(QObject *parent) :
    QObject(parent)
{
}

QStringList Deezer::RequeteAlbums(QString rech)
{
    QString adresse= "http://api.discogs.com/database/search?barcode="+rech;
    const QUrl url = QUrl(adresse);
    const QNetworkRequest requete(url);
    QNetworkAccessManager *m = new QNetworkAccessManager;
    QNetworkReply *r = m->get(requete);
    QStringList resultat;
    //on attend que le signal finished soit reçu
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //on va lire ligne par ligne, jusqu'à trouver l'id
    while (!r->atEnd()) {
        QString pageWeb=r->readLine();
    }

    return resultat;

}
AlbumGestion* Deezer::RequeteInfosAlbum(QString chemin,QString type)
{
    AlbumGestion* album = new AlbumGestion;

    QString adresse= "http://api.discogs.com/"+type+"/"+chemin;
    qDebug() << adresse;
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
    }
    return album;

}
QString Deezer::accents(QString nom)
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
    temp=temp.replace("\\u00ef","ï");
    temp=temp.replace("\\u00e7","ç");

    nomretravaille=temp.replace("\\u00e8","è");

    return nomretravaille;
}

