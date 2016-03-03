#include "QAWSWrapper.h"
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMessageAuthenticationCode>
#include <QXmlStreamReader>
#include <QDebug>



namespace
{
    /**
     * @brief Return the French market place URL
     */
    const char* getMarketPlaceURL()
    {
        return "webservices.amazon.fr";
    }

    /**
     * @brief Return the market place URI to get XML
     */
    const char* getMarketPlaceURI()
    {
        return "/onca/xml";
    }

    /**
     * @brief Return the associate tag
     *
     * The associate tag is an alphanumeric token that uniquely identifies
     * someone as an associate
     */
    const char* getAssociateTag()
    {
        return "990460715344";
    }

    /**
     * @brief Return the access key ID
     *
     * The Amazon Web Services access key ID which uniquely identifies someone.
     */
    const char* getAccessKeyID()
    {
        return "AKIAJOCTDCSVNM5IJ5PQ";
    }

    /**
     * @brief Return the secret access key
     *
     * A key that is used in conjunction with the Access Key ID to
     * cryptographically sign an API request.
     */
    const char* getSecretAccessKey()
    {
        return "fVKexEofcDNu7s1DAUlbygltFqnb+GoYseafq5+6";
    }

    /**
     * @brief Return current time stamp with the ISO formatting
     */
    QString getTimeStamp()
    {
        return QDateTime::currentDateTimeUtc().toString( Qt::ISODate );
    }

    /**
     * @brief Return the string to sign
     */
    QString getStringToSign( const QUrlQuery& listOfParameters )
    {
        QString stringToSign( QString( "GET\n%1\n%2\n" ).arg( getMarketPlaceURL() ).arg( getMarketPlaceURI() ) );
        stringToSign += listOfParameters.query();
        return stringToSign;
    }

    AlbumPhys parseXml( const QByteArray& xmlToParse, QStringList& artistsList )
    {
        AlbumPhys albumToFill;
        bool isValid = false;
        unsigned int trackNumber = 1;

        QXmlStreamReader reader( xmlToParse );
        while ( !reader.atEnd() )
        {
            reader.readNext();
            switch ( reader.tokenType() )
            {
                case QXmlStreamReader::StartElement:
                {
                    // look for the validity of the request
                    if ( reader.name() == "IsValid" )
                    {
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                            isValid = ( reader.text() == "True" );
                    }
                    else if ( reader.name() == "Track" )
                    {
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                        {
                            TitresPhys titre;
                            titre.Titre = reader.text().toString();
                            titre.Num_Piste = trackNumber;
                            titre.Duree="0:00";
                            trackNumber++;
                            albumToFill.titres.append( titre );
                        }
                    }
                    else if ( ( reader.name() == "Creator" ) &&
                              ( reader.attributes().hasAttribute( "Role" ) ) &&
                              ( reader.attributes().value( "Role" ) == "Performer" ) )
                    {
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                            artistsList << reader.text().toString();
                    }
                    else if ( reader.name() == "Title" )
                    {
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                            albumToFill.Album = reader.text().toString();
                    }
                    else if ( reader.name() == "Artist" )
                    {
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                        {
                            albumToFill.Artiste = reader.text().toString();
                            if ( reader.text().toString() == "Multi-Artistes" )
                                albumToFill.Artiste = "Artistes Divers";
                        }
                    }
                    else if ( reader.name() == "ReleaseDate" )
                    {
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                            albumToFill.Annee = reader.text().toString().left( 4 ).toInt();
                    }
                    else if ( ( reader.name() == "ImageSet" ) &&
                              ( reader.attributes().hasAttribute( "Category" ) ) &&
                              ( reader.attributes().value( "Category" ) == "primary" ) )
                    {
                        reader.readNext();
                        while ( !reader.atEnd() && ( reader.name() != "LargeImage" ) )
                            reader.readNext();
                        reader.readNext();
                        while ( !reader.atEnd() && ( reader.name() != "URL" ) )
                            reader.readNext();
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                        {
                            QUrl urlCover( reader.text().toString() );
                            QNetworkRequest coverRequest( urlCover );
                            QNetworkAccessManager* accessCover = new QNetworkAccessManager;
                            QNetworkReply* coverReply = accessCover->get( coverRequest );

                            QEventLoop loop;
                            QObject::connect( coverReply, SIGNAL( finished() ), &loop, SLOT( quit() ) );
                            loop.exec();
                            albumToFill.Poch = QImage::fromData( coverReply->readAll() );
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
        if ( reader.hasError() )
        {
            qDebug() << "error while reading XML:" << reader.error();
        }
        else if ( !isValid )
        {
            qDebug() << "invalide request";
        }

        return albumToFill;
    }
}



QAWSWrapper::QAWSWrapper():
    m_artistsList()
{

}



QAWSWrapper::~QAWSWrapper()
{
}



AlbumPhys QAWSWrapper::getAlbumFromEAN( const QString& ean )
{
    AlbumPhys albumRelatedToEAN;

    // Build the list of parameters that the URL must contain
    QUrlQuery listOfParameters;
    listOfParameters.addQueryItem( "AWSAccessKeyId", getAccessKeyID() );
    listOfParameters.addQueryItem( "AssociateTag", getAssociateTag() );
    listOfParameters.addQueryItem( "IdType", "EAN" );
    listOfParameters.addQueryItem( "ItemId", ean );
    listOfParameters.addQueryItem( "Operation", "ItemLookup" );
    listOfParameters.addQueryItem( "ResponseGroup", QString( "Tracks,Small,Images,ItemAttributes" ).toUtf8().toPercentEncoding() );
    listOfParameters.addQueryItem( "SearchIndex", "Music" );
    listOfParameters.addQueryItem( "Service", "AWSECommerceService" );
    listOfParameters.addQueryItem( "Timestamp", getTimeStamp().toUtf8().toPercentEncoding() );
    //qDebug() << listOfParameters.query();

    // Prepare the string that will be used to compute the signature
    QString stringToSign( getStringToSign( listOfParameters ) );
//    qDebug() << stringToSign;

    // Compute the signature of the string
    QString signature = QMessageAuthenticationCode::hash( stringToSign.toLatin1(), getSecretAccessKey(), QCryptographicHash::Sha256 ).toBase64();
//    qDebug() << signature;


    // Build the signed URL
    listOfParameters.addQueryItem( "Signature", signature.toUtf8().toPercentEncoding() );
    QUrl signedUrl( QString( "http://%1%2" ).arg( getMarketPlaceURL() ).arg( getMarketPlaceURI() ) );
    signedUrl.setQuery( listOfParameters );
//    qDebug() << signedUrl.toString();

    QNetworkRequest networkRequestApi( signedUrl );
    QNetworkAccessManager* networkAccessManagerApi = new QNetworkAccessManager;
    QNetworkReply* networkReplyApi = networkAccessManagerApi->get( networkRequestApi );

    QEventLoop loop;
    QObject::connect( networkReplyApi, SIGNAL( finished() ), &loop, SLOT( quit() ) );
    loop.exec();

    albumRelatedToEAN = parseXml( networkReplyApi->readAll(), m_artistsList );

    return albumRelatedToEAN;
}



const QStringList& QAWSWrapper::getArtistsList() const
{
    return m_artistsList;
}
