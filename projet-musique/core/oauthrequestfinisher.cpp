#include "oauthrequestfinisher.h"
#include <QCryptographicHash>
#include <QUrl>
#include <QDebug>



QString OAuthRequestFinisher::getFinishedRequest(const QString &initialRequest)
{
    // get the consumer secret key from data base (for the moment, hard coded)
    const QString consumerSecretKey( QUrl::toPercentEncoding( "ab8dddb10182ae33a9d0066e013b06ee082fba17" ) );
    // get the secret token from data base (for the moment, hard coded)
    const QString secretToken( QUrl::toPercentEncoding( "b503630eb7c0ad630a16dc6ff643213acedde4b7" ) );
    // build the hash key
    const QString hashKey( consumerSecretKey + "&" + secretToken );

    qDebug() << "hash key: " << hashKey;

    // get HTTP method (GET or POST) (could be a parameter)
    const QString httpMethod( "GET" );
    // get the base adress for requests (could be in database)
    const QString baseAdress( QUrl::toPercentEncoding( "http://api.music-story.com" ) );
    // get the category (could be a parameter)
    const QString category( QUrl::toPercentEncoding( "artist/search" ) );
    // get the parameters of the request (could be a list, could be a parameter)
    const QPair<QString, QString> parameters1( "name", "Bob Marley" );
    // get the access token from the data base (for the moment, hard coded)
    const QPair<QString, QString> parameters2( "oauth_token", "db164a3be49ecebf981c7475614d9ddd1c88ad8e" );
    // build the request
    const QString request =
            httpMethod + QUrl::toPercentEncoding( "&" ) +
            baseAdress + QUrl::toPercentEncoding( "/" ) +
            category + QUrl::toPercentEncoding( "&" ) +
            QUrl::toPercentEncoding( parameters1.first ) + QUrl::toPercentEncoding( "=" ) +
            QUrl::toPercentEncoding( parameters1.second ) + QUrl::toPercentEncoding( "&" ) +
            QUrl::toPercentEncoding( parameters2.first ) + QUrl::toPercentEncoding( "=" ) +
            QUrl::toPercentEncoding( parameters2.second );

    // hash the request with the kQOAuth utils
    const QString signature( hmac_sha1( request, hashKey ) );

    // add the signature: "&oauth_signature="
    const QString finishedRequest( request + QUrl::toPercentEncoding( "&oauth_signature=" ) + QUrl::toPercentEncoding( signature ) );

    return finishedRequest;
}



QString OAuthRequestFinisher::hmac_sha1(const QString &message, const QString &key)
{
    QByteArray keyBytes = key.toAscii();
    int keyLength;              // Lenght of key word
    const int blockSize = 64;   // Both MD5 and SHA-1 have a block size of 64.

    keyLength = keyBytes.size();
    // If key is longer than block size, we need to hash the key
    if (keyLength > blockSize) {
        QCryptographicHash hash(QCryptographicHash::Sha1);
        hash.addData(keyBytes);
        keyBytes = hash.result();
    }

    /* http://tools.ietf.org/html/rfc2104  - (1) */
    // Create the opad and ipad for the hash function.
    QByteArray ipad;
    QByteArray opad;

    ipad.fill( 0, blockSize);
    opad.fill( 0, blockSize);

    ipad.replace(0, keyBytes.length(), keyBytes);
    opad.replace(0, keyBytes.length(), keyBytes);

    /* http://tools.ietf.org/html/rfc2104 - (2) & (5) */
    for (int i=0; i<64; i++) {
        ipad[i] = ipad[i] ^ 0x36;
        opad[i] = opad[i] ^ 0x5c;
    }

    QByteArray workArray;
    workArray.clear();

    workArray.append(ipad, 64);
    /* http://tools.ietf.org/html/rfc2104 - (3) */
    workArray.append(message.toAscii());


    /* http://tools.ietf.org/html/rfc2104 - (4) */
    QByteArray sha1 = QCryptographicHash::hash(workArray, QCryptographicHash::Sha1);

    /* http://tools.ietf.org/html/rfc2104 - (6) */
    workArray.clear();
    workArray.append(opad, 64);
    workArray.append(sha1);

    sha1.clear();

    /* http://tools.ietf.org/html/rfc2104 - (7) */
    sha1 = QCryptographicHash::hash(workArray, QCryptographicHash::Sha1);
    return QString(sha1.toBase64());
}
