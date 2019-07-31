#include "QAWSWrapper.h"
#include "QAWSGlobalInfo.h"
#include "QAWSWrapperNotifier.h"
#include "Meta_Titre.h"
#include "meta_album.h"

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
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


namespace
{
    QString getToken()
    {
        return QString("dgoRcajfWFCHGnSpejifplnfndKJCQoZTLECVrPP");
    }

    bool isReponseValid( const QByteArray& xmlToParse )
    {
        Q_UNUSED(xmlToParse)
        bool isValid = true;
        return isValid;
    }

    Meta_Album* parseXml( const QByteArray& xmlToParse, const QString& m_ean )
    {
        QString nomAlbum;
        QString nomArtiste;
        int annee = -1;
        QImage pochette;
        int type = -1;
        int supportP = -1;
        QString commentaires;
        QString ean = m_ean;
        int supportM = -1;
        QString chemin;
        struct TitreTemp
        {
            QString nomTitre;
            QString duree;
            QString artiste;
            int numPiste;
        };
        QList<TitreTemp> titresTemp;

        QJsonDocument document = QJsonDocument::fromJson(xmlToParse);
        QJsonObject object1 = document.object();
        // Get the artist name
        if (object1.contains("artists") && object1["artists"].isArray())
        {
            QJsonArray array1 = object1["artists"].toArray();
            if (array1[0].isObject())
            {
                QJsonObject object2 = array1[0].toObject();
                if (object2.contains("name") && object2["name"].isString())
                {
                    nomArtiste = object2["name"].toString();
                }
                // Multiple artists case
                if (nomArtiste == "Various")
                {
                    nomArtiste = "Artistes Divers";
                }
            }
        }

        // Get the album name
        if (object1.contains("title") && object1["title"].isString())
        {
            nomAlbum = object1["title"].toString();
        }

        // Get the release date
        if (object1.contains("year") && object1["year"].isDouble())
        {
            annee = object1["year"].toInt();
        }

        // Get track list
        if (object1.contains("tracklist") && object1["tracklist"].isArray())
        {
            QJsonArray array1 = object1["tracklist"].toArray();
            for (int i = 0; i < array1.size(); ++i)
            {
                TitreTemp tmp;
                if (array1[i].isObject())
                {
                    tmp.numPiste = i + 1;
                    QJsonObject object2 = array1[i].toObject();
                    if (object2.contains("title") && object2["title"].isString())
                    {
                        tmp.nomTitre = object2["title"].toString();
                    }
                    if (object2.contains("duration") && object2["duration"].isString())
                    {
                        tmp.duree = object2["duration"].toString();
                    }
                    if (object2.contains("artists") && object2["artists"].isArray())
                    {
                        QJsonArray array2 = object2["artists"].toArray();
                        if ((array2.size() > 0 ) && array2[0].isObject())
                        {
                            QJsonObject object3 = array2[0].toObject();
                            if (object3.contains("name") && object3["name"].isString())
                            {
                                tmp.artiste = object3["name"].toString();
                            }
                        }
                    }
                }
                titresTemp.append(tmp);
            }
        }

        // Get picture
        if (object1.contains("images") && object1["images"].isArray())
        {
            QJsonArray array1 = object1["images"].toArray();
            if (array1[0].isObject())
            {
                QJsonObject object2 = array1[0].toObject();
                if (object2.contains("uri") && object2["uri"].isString())
                {
                    QUrl urlCover(object2["uri"].toString());
                    QNetworkRequest coverRequest(urlCover);
                    QNetworkAccessManager* accessCover = new QNetworkAccessManager;
                    QNetworkReply* coverReply = accessCover->get(coverRequest);
                    QEventLoop loop;
                    QObject::connect(coverReply, SIGNAL(finished()), &loop, SLOT(quit()));
                    loop.exec();
                    pochette = QImage::fromData(coverReply->readAll());
                }
            }
        }

        QList<Meta_Titre*> titres;
        for ( auto it : titresTemp )
        {
            Meta_Titre* titre = Meta_Titre::CreerMeta_Titre(nomAlbum, it.artiste, it.nomTitre, annee, it.duree, it.numPiste, pochette, type, supportP, supportM, chemin, commentaires, ean);
            titres.append(titre);
        }

        Meta_Album* albumToFill = Meta_Album::CreerMeta_Album(nomAlbum, nomArtiste, annee, pochette, type, titres, supportP, commentaires, ean);
        return albumToFill;
    }
}



QAWSWrapper::QAWSWrapper():
    m_notifier( new QAWSWrapperNotifier )
{
}



QAWSWrapper::~QAWSWrapper()
{
}



QAWSWrapperNotifier& QAWSWrapper::getNotifier()
{
    return *m_notifier;
}



Meta_Album* QAWSWrapper::getAlbumFromEAN( const QString& ean )
{
    // Build the URL for the request
    QUrl requestUrl("https://api.discogs.com/database/search");
    QUrlQuery requestParameters;
    requestParameters.addQueryItem("barcode", ean);
    requestParameters.addQueryItem("token", getToken());
    requestUrl.setQuery(requestParameters);

    QNetworkRequest networkRequestApi(requestUrl);
    QNetworkAccessManager* networkAccessManagerApi = new QNetworkAccessManager;
    QNetworkReply* networkReplyApi = networkAccessManagerApi->get(networkRequestApi);

    QEventLoop loop;
    QObject::connect( networkReplyApi, SIGNAL( finished() ), &loop, SLOT( quit() ) );
    loop.exec();

    QByteArray response( networkReplyApi->readAll() );
    networkReplyApi->deleteLater();

    // Extract the URL to the release from the response
    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonObject object1 = document.object();
    QString releaseUrl;
    if (object1.contains("results") && object1["results"].isArray())
    {
        QJsonArray object2 = object1["results"].toArray();
        if ((object2.size() > 0) && object2[0].isObject())
        {
            QJsonObject object3 = object2[0].toObject();
            if (object3.contains("resource_url") && object3["resource_url"].isString())
            {
                releaseUrl = object3["resource_url"].toString();
            }
        }
    }
    // Add the token to this URL
    requestParameters.clear();
    requestParameters.addQueryItem("token", getToken());
    requestUrl = releaseUrl;
    requestUrl.setQuery(requestParameters);
    // Initiate the request
    networkRequestApi.setUrl(requestUrl);
    networkReplyApi = networkAccessManagerApi->get(networkRequestApi);
    QObject::connect( networkReplyApi, SIGNAL( finished() ), &loop, SLOT( quit() ) );
    loop.exec();

    response = networkReplyApi->readAll();
    QString message;
    message += "Amazon Web Services response is ";
    message += isReponseValid( response ) ? "" : "not ";
    message += "valid.";
    getNotifier().emitStepAchieved( message );


    return parseXml( response, ean );
}
