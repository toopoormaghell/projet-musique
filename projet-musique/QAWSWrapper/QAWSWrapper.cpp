#include "QAWSWrapper.h"
#include "QAWSGlobalInfo.h"
#include "QAWSWrapperNotifier.h"

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
    bool isReponseValid( const QByteArray& xmlToParse )
    {
        bool isValid = false;
        QXmlStreamReader reader( xmlToParse );
        while ( !reader.atEnd() )
        {
            reader.readNext();
            if ( ( reader.tokenType() == QXmlStreamReader::StartElement ) &&
                 ( reader.name() == "IsValid" ) )
            {
                reader.readNext();
                if ( reader.tokenType() == QXmlStreamReader::Characters )
                    isValid = ( reader.text() == "True" );
            }
        }
        return isValid;
    }

    AlbumPhys parseXml( const QByteArray& xmlToParse, QStringList& artistsList )
    {
        AlbumPhys albumToFill;
        unsigned int trackNumber = 1;

        QXmlStreamReader reader( xmlToParse );
        while ( !reader.atEnd() )
        {
            reader.readNext();
            switch ( reader.tokenType() )
            {
                case QXmlStreamReader::StartElement:
                {
                    if ( reader.name() == "Track" )
                    {
                        reader.readNext();
                        if ( reader.tokenType() == QXmlStreamReader::Characters )
                        {
                            TitresPhys titre;
                            titre.Titre = reader.text().toString();
                            titre.Num_Piste = trackNumber;
                            titre.Duree = "0:00";
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
                            else
                                artistsList << reader.text().toString();
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

        return albumToFill;
    }
}



QAWSWrapper::QAWSWrapper():
    m_notifier( new QAWSWrapperNotifier )
  , m_artistsList()
{
}



QAWSWrapper::~QAWSWrapper()
{
}



QAWSWrapperNotifier& QAWSWrapper::getNotifier()
{
    return *m_notifier;
}



AlbumPhys QAWSWrapper::getAlbumFromEAN( const QString& ean )
{
    // Build the list of parameters that the URL must contain
    QUrlQuery listOfParameters;
    listOfParameters.addQueryItem( "AWSAccessKeyId", QAWSGlobalInfo::getAccessKeyID() );
    listOfParameters.addQueryItem( "AssociateTag", QAWSGlobalInfo::getAssociateTag() );
    listOfParameters.addQueryItem( "IdType", "EAN" );
    listOfParameters.addQueryItem( "ItemId", ean );
    listOfParameters.addQueryItem( "Operation", "ItemLookup" );
    listOfParameters.addQueryItem( "ResponseGroup", QString( "Tracks,Small,Images,ItemAttributes" ).toUtf8().toPercentEncoding() );
    listOfParameters.addQueryItem( "SearchIndex", "Music" );
    listOfParameters.addQueryItem( "Service", "AWSECommerceService" );
    listOfParameters.addQueryItem( "Timestamp", QDateTime::currentDateTimeUtc().toString( Qt::ISODate ).toUtf8().toPercentEncoding() );

    // Prepare the string that will be used to compute the signature
    QString stringToSign( QString( "GET\n%1\n%2\n" ).arg( QAWSGlobalInfo::getMarketPlaceURL() ).arg( QAWSGlobalInfo::getMarketPlaceURI() ) );
    stringToSign += listOfParameters.query();

    // Compute the signature of the string
    QString signature = QMessageAuthenticationCode::hash( stringToSign.toLatin1(), QAWSGlobalInfo::getSecretAccessKey(), QCryptographicHash::Sha256 ).toBase64();

    // Build the signed URL
    listOfParameters.addQueryItem( "Signature", signature.toUtf8().toPercentEncoding() );
    QUrl signedUrl( QString( "http://%1%2" ).arg( QAWSGlobalInfo::getMarketPlaceURL() ).arg( QAWSGlobalInfo::getMarketPlaceURI() ) );
    signedUrl.setQuery( listOfParameters );

    QNetworkRequest networkRequestApi( signedUrl );
    QNetworkAccessManager* networkAccessManagerApi = new QNetworkAccessManager;
    QNetworkReply* networkReplyApi = networkAccessManagerApi->get( networkRequestApi );

    QEventLoop loop;
    QObject::connect( networkReplyApi, SIGNAL( finished() ), &loop, SLOT( quit() ) );
    loop.exec();

    QByteArray response( networkReplyApi->readAll() );

    QString message;
    message += "Amazon Web Services response is ";
    message += isReponseValid( response ) ? "" : "not ";
    message += "valid.";
    getNotifier().emitStepAchieved( message );

    m_artistsList.clear();
    return parseXml( response, m_artistsList );
}



const QStringList& QAWSWrapper::getArtistsList() const
{
    return m_artistsList;
}
