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
    // Retourne une r�f�rence sur l'unique objet de ce type
    static kQOAuthSingleton& getInstance();
    // Retourne une QImage dont l'adresse est pass�e en param�tre
    void makeRequest(const QString& category, const QString &paramKey, const QString &paramValue);

    QByteArray getResponse() const;

    void makeRequest(const QString &category);
signals:
    void finished( QByteArray response );

private slots:
    void onRequestReady( QByteArray response );
    void onAuthorizedRequestDone();


private:
    // Constructeur priv� : singleton
    kQOAuthSingleton( QObject* parent = NULL );
    // Volontairement non impl�ment�
    kQOAuthSingleton( const kQOAuthSingleton& other );
    // Volontairement non impl�ment�
    kQOAuthSingleton& operator=( const kQOAuthSingleton& rhs );

    QPointer<KQOAuthManager> m_manager;
    QPointer<KQOAuthRequest> m_request;
    QPointer<QSettings> m_settings;
    QByteArray m_reponse;
};



#define theOAuthSingleton (kQOAuthSingleton::getInstance())



#endif // KQOAUTHSINGLETON_H
