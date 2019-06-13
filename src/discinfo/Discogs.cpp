#include <Discogs.h>

#include <QScopedPointer>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

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

void discinfo::Discogs::requestFromEan(const std::string& ean)
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
    connect(&getInstance(), &QNetworkAccessManager::finished, this, &Discogs::slotFinished);
}

void discinfo::Discogs::requestFromReleaseId(const std::string& releaseId)
{
    // Build the URL for the request
    QUrl requestUrl("https://api.discogs.com/releases/" + QString::fromStdString(releaseId));
    // Create a request from this URL
    QNetworkRequest request(requestUrl);
    // Initiate the request
    getInstance().get(request);
    // Connect to reply signals to manage any cases
    connect(&getInstance(), &QNetworkAccessManager::finished, this, &Discogs::slotFinished);
}

void discinfo::Discogs::slotFinished(QNetworkReply* reply)
{
    Q_EMIT(success(reply->readAll()));
    reply->deleteLater();
}
