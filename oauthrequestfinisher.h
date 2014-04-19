#ifndef OAUTHREQUESTFINISHER_H
#define OAUTHREQUESTFINISHER_H



#include <QString>



class OAuthRequestFinisher
{
public:
    ~OAuthRequestFinisher();

    static QString getFinishedRequest( const QString& initialRequest );

private:
    OAuthRequestFinisher();
    OAuthRequestFinisher( const OAuthRequestFinisher& rhs );
    OAuthRequestFinisher& operator=( const OAuthRequestFinisher& other );

    static QString hmac_sha1(const QString &message, const QString &key);
};

#endif // OAUTHREQUESTFINISHER_H
