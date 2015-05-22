#ifndef KQOAUTHSINGLETON_H
#define KQOAUTHSINGLETON_H



class QUrl;
class KQOAuthManager;
class KQOAuthRequest;
class QSettings;
#include <QByteArray>
#include <QObject>
#include <QPointer>



class kQOAuthSingleton : public QObject
{
    Q_OBJECT

public:
    // Destructeur
    ~kQOAuthSingleton();
    // Retourne une référence sur l'unique objet de ce type
    static kQOAuthSingleton& getInstance();
    // Retourne une QImage dont l'adresse est passée en paramètre
    void makeRequest(const QString& category, const QString &paramKey, const QString &paramValue);

    QByteArray getResponse() const;

    void makeRequest(const QString &category);
signals:
    void finished( QByteArray response );

private slots:
    void onRequestReady( QByteArray response );
    void onAuthorizedRequestDone();


private:
    // Constructeur privé : singleton
    kQOAuthSingleton( QObject* parent = NULL );
    // Volontairement non implémenté
    kQOAuthSingleton( const kQOAuthSingleton& other );
    // Volontairement non implémenté
    kQOAuthSingleton& operator=( const kQOAuthSingleton& rhs );

    QPointer<KQOAuthManager> m_manager;
    QPointer<KQOAuthRequest> m_request;
    QPointer<QSettings> m_settings;
    QByteArray m_reponse;
};



#define theOAuthSingleton (kQOAuthSingleton::getInstance())



#endif // KQOAUTHSINGLETON_H
