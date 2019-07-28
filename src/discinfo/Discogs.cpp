#include <Discogs.h>

#include <QScopedPointer>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace
{
    static QScopedPointer<QNetworkAccessManager> s_networkAccessMananger(nullptr);
    QNetworkAccessManager& getInstance()
    {
        if (s_networkAccessMananger == nullptr)
            s_networkAccessMananger.reset(new QNetworkAccessManager);
        return *s_networkAccessMananger;
    }
}

namespace discinfo
{
void Discogs::requestFromEan(const std::string& ean)
{
    // Build the URL for the request
    QUrl requestUrl("https://api.discogs.com/database/search");
    QUrlQuery requestParameters;
    requestParameters.addQueryItem("barcode", QString::fromStdString(ean));
    requestParameters.addQueryItem("key", "jFaxBKHLiQXtPQedKrjT");
    requestParameters.addQueryItem("secret", "uvKmmopuzrQOmnCDGNjyTugygyOQxqFc");
    requestUrl.setQuery(requestParameters);
    // Create a request from this URL
    QNetworkRequest request(requestUrl);
    // Initiate the request
    getInstance().get(request);
    // Connect to reply signals to manage any cases
    connect(&getInstance(), &QNetworkAccessManager::finished, this, &Discogs::slotFinishedFromEan);
}

void Discogs::requestFromReleaseId(const std::string& releaseId)
{
    // Build the URL for the request
    QUrl requestUrl("https://api.discogs.com/releases/" + QString::fromStdString(releaseId));
    // Create a request from this URL
    QNetworkRequest request(requestUrl);
    // Initiate the request
    getInstance().get(request);
    // Connect to reply signals to manage any cases
    connect(&getInstance(), &QNetworkAccessManager::finished, this, &Discogs::slotFinishedFromReleaseId);
}

void Discogs::slotFinishedFromEan(QNetworkReply* reply)
{
    QByteArray replyBytes(reply->readAll());
    QJsonDocument document = QJsonDocument::fromJson(replyBytes);
    QJsonObject object = document.object();
    if (object.contains("results") && object["results"].isArray())
    {
        qDebug() << "youpi1";
        QJsonArray object2 = object["results"].toArray();
        if ((object2.size() > 0) && object2[0].isObject())
        {
            qDebug() << "youpi2";
            QJsonObject object3 = object2[0].toObject();
            if (object3.contains("resource_url") && object3["resource_url"].isString())
            {
                QString releaseUrl = object3["resource_url"].toString();
                qDebug() << releaseUrl;
            }
        }
    }

    Q_EMIT(successFromEan(replyBytes));
    reply->deleteLater();
}

void Discogs::slotFinishedFromReleaseId(QNetworkReply* reply)
{
    QByteArray replyBytes(reply->readAll());
    QJsonDocument document = QJsonDocument::fromJson(replyBytes);
    QJsonObject object = document.object();
    if (object.contains("results") && object["results"].isArray())
    {
        qDebug() << "youpi1";
        QJsonArray object2 = object["results"].toArray();
        if ((object2.size() > 0) && object2[0].isObject())
        {
            qDebug() << "youpi2";
            QJsonObject object3 = object2[0].toObject();
            if (object3.contains("resource_url") && object3["resource_url"].isString())
            {
                QString releaseUrl = object3["resource_url"].toString();
                qDebug() << releaseUrl;
            }
        }
    }

    Q_EMIT(successFromReleaseId(replyBytes));
    reply->deleteLater();
}
}
