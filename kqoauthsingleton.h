#ifndef KQOAUTHSINGLETON_H
#define KQOAUTHSINGLETON_H



class QUrl;
class KQOAuthManager;
class KQOAuthRequest;
class QSettings;
#include <QObject>
#include <QPointer>
#include <QImage>



// To validate a new application or if the current validation is revoked,
// we need:
// 1) change s_defaultIsTokensOk to false
// 2) start the program in debug and watch the console
// 3) connect with a web browser to the adress:
//    http://www.discogs.com/oauth/authorize?oauth_token=<temporary token>
// 4) change s_validatedToken and s_validatedSecretToken to their new values
// 5) reset s_defaultIsTokensOk to true
// 6) it should work
class kQOAuthSingleton : public QObject
{
    Q_OBJECT

public:
    // Destructeur
    ~kQOAuthSingleton();
    // Retourne une référence sur l'unique objet de ce type
    static kQOAuthSingleton& getInstance();
    // Retourne une QImage dont l'adresse est passée en paramètre
    QImage getPochette( const QUrl& url );




private slots:
    // Appelé quand le token temporaire est reçu
    void onTemporaryTokenReceived( QString temporaryToken, QString temporaryTokenSecret );
    // Appelé quand l'utilisateur a autorisé la connexion
    void onAuthorizationReceived( QString token, QString verifier );
    // Appelé quand le token permanent est reçu
    void onAccessTokenReceived( QString token, QString tokenSecret );
    // Appelé quand une réponse à une requête est reçue
    void onRequestReady( QByteArray request );



private:
    // Constructeur privé : singleton
    kQOAuthSingleton( QObject* parent = NULL );
    // Volontairement non implémenté
    kQOAuthSingleton( const kQOAuthSingleton& other );
    // Volontairement non implémenté
    kQOAuthSingleton& operator=( const kQOAuthSingleton& rhs );

    // Démarre le processus permettant d'obtenir les tokens
    void initTokens();

    // Indique si les requêtes peuvent être lancées
    bool m_isTokensOk;
    bool m_isReplyOk;
    QImage m_image;

    QPointer<KQOAuthManager> m_manager;
    QPointer<KQOAuthRequest> m_request;
    QPointer<QSettings> m_settings;
};

#define theOAuthSingleton (kQOAuthSingleton::getInstance())

#endif // KQOAUTHSINGLETON_H
