#ifndef AUTORISATIONDISCOGS_H
#define AUTORISATIONDISCOGS_H

#include <QObject>
#include <QSettings>
#include <kqoauthmanager.h>

class KQOAuthManager;
class KQOAuthRequest;
class AutorisationDiscogs: public QObject
{
    Q_OBJECT
public:
    explicit AutorisationDiscogs( QObject* parent = NULL );
    ~AutorisationDiscogs();
    void getAccess();
     void xauth();
     void sendTweet(QString tweet);


 private slots:
     void onTemporaryTokenReceived(QString temporaryToken, QString temporaryTokenSecret);
     void onAuthorizationReceived(QString token, QString verifier);
     void onAccessTokenReceived(QString token, QString tokenSecret);
     void onAuthorizedRequestDone();
     void onRequestReady(QByteArray);

 private:
     KQOAuthManager *oauthManager;
     KQOAuthRequest *oauthRequest;
     QSettings oauthSettings;
 };



#endif // AUTORISATIONDISCOGS_H
