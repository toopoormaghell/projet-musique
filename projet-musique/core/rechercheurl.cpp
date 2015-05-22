#include "rechercheurl.h"
#include <QObject>
#include "kqoauthsingleton.h"
#include <QtXml/QDomDocument>
#include <QtXml/qdom.h>
#include <QtNetwork>

RechercheURL::RechercheURL(QObject *parent)
{
}

void RechercheURL::RequeteAlbums(QString rech)
{
    theOAuthSingleton.makeRequest( "release/search", "ean", rech );

      //on attend que le signal finished soit reçu
      QEventLoop loop;
      QObject::connect(&theOAuthSingleton, SIGNAL(finished( QByteArray )), &loop, SLOT(quit()));
      loop.exec();
}
