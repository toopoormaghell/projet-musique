#include "kqoauthsingleton.h"
#include <QImage>
#include <QSettings>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QEventLoop>
#include <QDesktopServices>
// #include <kqoauthmanager.h>
#include <kqoauthrequest.h>



static const QString s_consumerKey   ( "cb4749e720e30206b488fe891ec416330d87fe5c" );
static const QString s_consumerSecret( "ab8dddb10182ae33a9d0066e013b06ee082fba17" );
static const QString s_accessToken   ( "db164a3be49ecebf981c7475614d9ddd1c88ad8e" );
static const QString s_tokenSecret   ( "b503630eb7c0ad630a16dc6ff643213acedde4b7" );
static const QString s_baseAdress( "http://api.music-story.com" );



kQOAuthSingleton::kQOAuthSingleton( QObject* parent ):
    QObject( parent ),
    m_manager(),
    m_request(),
    m_settings()
{
 /*   m_manager = new KQOAuthManager( this );
    m_request = new KQOAuthRequest( this );
    m_settings = new QSettings( this );
    */
}

kQOAuthSingleton::~kQOAuthSingleton()
{
}

kQOAuthSingleton &kQOAuthSingleton::getInstance()
{
    static kQOAuthSingleton s_singleton;
    return s_singleton;
}

void kQOAuthSingleton::makeRequest( const QString& category, const QString& paramKey, const QString& paramValue )
{
  /*  disconnect( m_manager, SIGNAL( requestReady( QByteArray ) ),
        this, SLOT( onRequestReady( QByteArray ) ) );

    m_request->setEnableDebugOutput(true);
    m_request->initRequest( KQOAuthRequest::AuthorizedRequest, s_baseAdress + "/" + category );
    m_request->setHttpMethod( KQOAuthRequest::GET );
    m_request->setConsumerKey( s_consumerKey );
    m_request->setConsumerSecretKey( s_consumerSecret );
    m_request->setToken( s_accessToken );
    m_request->setTokenSecret( s_tokenSecret );

    KQOAuthParameters parameters;
    parameters.insert( paramKey, paramValue );
    m_request->setAdditionalParameters( parameters );

    connect( m_manager, SIGNAL( requestReady( QByteArray ) ),
       this, SLOT( onRequestReady( QByteArray ) ) );

    m_manager->executeRequest( m_request );
    */
}
void kQOAuthSingleton::makeRequest( const QString& category )
{
  /*  disconnect( m_manager, SIGNAL( requestReady( QByteArray ) ),
        this, SLOT( onRequestReady( QByteArray ) ) );

    m_request->setEnableDebugOutput(true);
    m_request->initRequest( KQOAuthRequest::AuthorizedRequest, s_baseAdress + "/" + category );
    m_request->setHttpMethod( KQOAuthRequest::GET );
    m_request->setConsumerKey( s_consumerKey );
    m_request->setConsumerSecretKey( s_consumerSecret );
    m_request->setToken( s_accessToken );
    m_request->setTokenSecret( s_tokenSecret );

   connect( m_manager, SIGNAL( requestReady( QByteArray ) ),
       this, SLOT( onRequestReady( QByteArray ) ) );

    m_manager->executeRequest( m_request );
    */
}

QByteArray kQOAuthSingleton::getResponse() const
{
    return m_reponse;
}

void kQOAuthSingleton::onRequestReady(QByteArray response)
{
    qDebug() << "Response from the service: " << response;
    m_reponse = response;
    emit finished( response );
}

void kQOAuthSingleton::onAuthorizedRequestDone()
{
    qDebug() << "Request done!";
}
