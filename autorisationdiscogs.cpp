#include "autorisationdiscogs.h"
#include <QDebug>
#include <kqoauthrequest_xauth.h>

AutorisationDiscogs::AutorisationDiscogs( QObject* parent ):QObject( parent )
{
    oauthRequest = new KQOAuthRequest;
    oauthManager = new KQOAuthManager(this);
    oauthRequest->setEnableDebugOutput(true);
}
AutorisationDiscogs::~AutorisationDiscogs()
{
    delete oauthRequest;
    delete oauthManager;
}
void AutorisationDiscogs::getAccess() {
    connect(oauthManager, SIGNAL(temporaryTokenReceived(QString,QString)),
            this, SLOT(onTemporaryTokenReceived(QString, QString)));

    connect(oauthManager, SIGNAL(authorizationReceived(QString,QString)),
            this, SLOT( onAuthorizationReceived(QString, QString)));

    connect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)),
            this, SLOT(onAccessTokenReceived(QString,QString)));

    connect(oauthManager, SIGNAL(requestReady(QByteArray)),
            this, SLOT(onRequestReady(QByteArray)));

    oauthRequest->initRequest(KQOAuthRequest::TemporaryCredentials, QUrl("http://api.discogs.com/oauth/request_token"));
    oauthRequest->setConsumerKey("jFaxBKHLiQXtPQedKrjT");
    oauthRequest->setConsumerSecretKey("uvKmmopuzrQOmnCDGNjyTugygyOQxqFc");

    oauthManager->setHandleUserAuthorization(true);

    oauthManager->executeRequest(oauthRequest);

}

void AutorisationDiscogs::onTemporaryTokenReceived(QString token, QString tokenSecret)
{
    qDebug() << "Token temporaire recu: " << token << tokenSecret;

    QUrl userAuthURL("http://www.discogs.com/oauth/authorize");

    if( oauthManager->lastError() == KQOAuthManager::NoError) {
        qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << userAuthURL;
        oauthManager->getUserAuthorization(userAuthURL);
    }

}

void AutorisationDiscogs::onAuthorizationReceived(QString token, QString verifier) {
    qDebug() << "Autorisation utilisateur recue : " << token << verifier;

    oauthManager->getUserAccessTokens(QUrl("http://api.discogs.com/oauth/access_token"));
    if( oauthManager->lastError() != KQOAuthManager::NoError) {
        //  QCoreApplication::exit();
    }
}

void AutorisationDiscogs::onAccessTokenReceived(QString token, QString tokenSecret) {
    qDebug() << "Token acces recu: " << token << tokenSecret;

    oauthSettings.setValue("oauth_token", token);
    oauthSettings.setValue("oauth_token_secret", tokenSecret);

    qDebug() << "Access tokens now stored. Ca marche!";

    sendTweet("alex");
}

void AutorisationDiscogs::onAuthorizedRequestDone() {
    qDebug() << "Request sent to Twitter!";

}

void AutorisationDiscogs::onRequestReady(QByteArray response) {
    qDebug() << "Response from the service: " << response;

}

void AutorisationDiscogs::xauth() {

    connect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)),
            this, SLOT(onAccessTokenReceived(QString,QString)));

    KQOAuthRequest_XAuth *oauthRequest = new KQOAuthRequest_XAuth(this);
    oauthRequest->initRequest(KQOAuthRequest::AccessToken, QUrl("http://api.discogs.com/oauth/access_token"));
    oauthRequest->setConsumerKey("jFaxBKHLiQXtPQedKrjT");
    oauthRequest->setConsumerSecretKey("uvKmmopuzrQOmnCDGNjyTugygyOQxqFc");
    oauthRequest->setXAuthLogin("farloth","15963210");

    oauthManager->executeRequest(oauthRequest);
}

void AutorisationDiscogs::sendTweet(QString tweet) {

     if( oauthSettings.value("oauth_token").toString().isEmpty() ||
            oauthSettings.value("oauth_token_secret").toString().isEmpty()) {
        qDebug() << "No access tokens. Aborting.";

        return;
    }

     /*
    oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest, QUrl("http://api.twitter.com/1/statuses/update.xml"));
    oauthRequest->setConsumerKey("jFaxBKHLiQXtPQedKrjT");
    oauthRequest->setConsumerSecretKey("uvKmmopuzrQOmnCDGNjyTugygyOQxqFc");
    oauthRequest->setToken(oauthSettings.value("oauth_token").toString());
    oauthRequest->setTokenSecret(oauthSettings.value("oauth_token_secret").toString());

    KQOAuthParameters params;
    params.insert("status", tweet);
    oauthRequest->setAdditionalParameters(params);

    oauthManager->executeRequest(oauthRequest);

    connect(oauthManager, SIGNAL(requestReady(QByteArray)),
            this, SLOT(onRequestReady(QByteArray)));
    connect(oauthManager, SIGNAL(authorizedRequestDone()),
            this, SLOT(onAuthorizedRequestDone()));
            */
}

