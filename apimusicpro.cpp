#include "apimusicpro.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include <QDebug>
#include "kqoauthsingleton.h"

ApiMusicPro::ApiMusicPro(QObject *parent) :
    QObject(parent)
{

}

QStringList ApiMusicPro::Requete()
{
    //QString adresse = "http://api.music-story.com/oauth/request_token?oauth_consumer_key=cb4749e720e30206b488fe891ec416330d87fe5c&oauth_signature=ab8dddb10182ae33a9d0066e013b06ee082fba17";
    //QString adresse="http://api.music-story.com/artist/search?name=Bob%20Marley&oauth_token="+m_bddInterface.getjetonAcces()+"&oauth_signature="+m_bddInterface.getjetonSecret();
    //QString adresse = OAuthRequestFinisher::getFinishedRequest( "http://api.music-story.com/artist/search?name=Bob%20Marley" );
    //adresse = adresse.mid( 4 );
    //qDebug() << adresse;
//    const QUrl url = QUrl(adresse.toUtf8());
//    const QNetworkRequest requete(url);
//    QNetworkAccessManager *m = new QNetworkAccessManager;
//    QNetworkReply *r = m->get(requete);
//    QStringList resultat;
//    //on attend que le signal finished soit reçu
//    QEventLoop loop;
//    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
//    loop.exec();

//    //on va lire ligne par ligne, jusqu'à trouver l'id
//    while (!r->atEnd()) {
//        QString pageWeb=r->readLine();
//        qDebug() << pageWeb;
//    }
//    theOAuthSingleton.makeRequest();
}
