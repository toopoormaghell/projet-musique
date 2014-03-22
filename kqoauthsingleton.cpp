#include "kqoauthsingleton.h"
#include <QImage>
#include <QSettings>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QDesktopServices>
#include <kqoauthmanager.h>
#include <kqoauthrequest.h>



static const bool s_defaultIsTokensOk = false;
static const QUrl s_requestTokenURL( "http://api.discogs.com/oauth/request_token" );
static const QUrl s_authorizationURL( "http://www.discogs.com/oauth/authorize" );
static const QUrl s_accessTokenURL( "http://api.discogs.com/oauth/access_token" );
static const QString s_consumerKey( "jFaxBKHLiQXtPQedKrjT" );
static const QString s_consumerSecretKey( "uvKmmopuzrQOmnCDGNjyTugygyOQxqFc" );



kQOAuthSingleton::kQOAuthSingleton( QObject* parent ):
    QObject( parent ),
    m_isTokensOk( s_defaultIsTokensOk ),
    m_isReplyOk( false ),
    m_image(),
    m_manager(),
    m_request(),
    m_settings()
{
    m_manager = new KQOAuthManager( this );

    m_request = new KQOAuthRequest( this );
    m_request->setEnableDebugOutput(true);

    m_settings = new QSettings( this );

    connect( m_manager, SIGNAL( temporaryTokenReceived( QString, QString ) ),
             this, SLOT( onTemporaryTokenReceived( QString, QString ) ) );
    connect( m_manager, SIGNAL( authorizationReceived( QString, QString ) ),
             this, SLOT( onAuthorizationReceived( QString, QString ) ) );
    connect( m_manager, SIGNAL( accessTokenReceived( QString, QString ) ),
             this, SLOT( onAccessTokenReceived( QString, QString ) ) );
    connect( m_manager, SIGNAL( requestReady( QByteArray ) ),
             this, SLOT( onRequestReady( QByteArray ) ) );
}

kQOAuthSingleton::~kQOAuthSingleton()
{
}

kQOAuthSingleton &kQOAuthSingleton::getInstance()
{
    static kQOAuthSingleton s_singleton;
    return s_singleton;
}

QImage kQOAuthSingleton::getPochette(const QUrl &url)
{
    if ( !m_isTokensOk )
        initTokens();

//    while ( !m_manager->isAuthorized() );
//    m_request->initRequest( KQOAuthRequest::AuthorizedRequest, url );
//    m_request->setConsumerKey( s_consumerKey );
//    m_request->setConsumerSecretKey( s_consumerSecretKey );
//    m_request->setToken( m_settings->value( "oauth_token" ).toString() );
//    m_request->setTokenSecret( m_settings->value( "oauth_token_secret" ).toString() );

//    m_manager->executeRequest( m_request );

//    // we must wait for the request to be finished
//    while ( !m_isReplyOk );
//    m_isReplyOk = false;

    return m_image;
}

void kQOAuthSingleton::onTemporaryTokenReceived( QString temporaryToken, QString temporaryTokenSecret )
{
    qDebug() << "Temporary token received: " << temporaryToken << temporaryTokenSecret;

    if( m_manager->lastError() == KQOAuthManager::NoError )
    {
        qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << s_authorizationURL;
        QUrl tmp( m_manager->getUserAuthorization( s_authorizationURL ) );
        QDesktopServices::openUrl( tmp );
    }
}

void kQOAuthSingleton::onAuthorizationReceived( QString token, QString verifier )
{
    qDebug() << "User authorization received: " << token << verifier;

    if( m_manager->lastError() == KQOAuthManager::NoError )
    {
        qDebug() << "Asking for access token.";
        m_manager->getUserAccessTokens( s_accessTokenURL );
    }
}

void kQOAuthSingleton::onAccessTokenReceived(QString token, QString tokenSecret)
{
    qDebug() << "Access token received: " << token << tokenSecret;

    if( m_manager->lastError() == KQOAuthManager::NoError )
    {
        m_settings->setValue( "oauth_token", token );
        m_settings->setValue( "oauth_token_secret", tokenSecret );
        qDebug() << "Access tokens now stored. Ready to send requests.";
        m_isTokensOk = true;
    }
}

void kQOAuthSingleton::onRequestReady(QByteArray request)
{
    m_image.loadFromData( request );
    m_isReplyOk = true;
}

void kQOAuthSingleton::initTokens()
{

    m_request->initRequest( KQOAuthRequest::TemporaryCredentials, s_requestTokenURL );
    m_request->setConsumerKey( s_consumerKey );
    m_request->setConsumerSecretKey( s_consumerSecretKey );
    m_manager->setHandleUserAuthorization( true );
    m_manager->executeRequest( m_request );
}
