#ifndef RECHERCHEURL_H
#define RECHERCHEURL_H

#include <QObject>

class RechercheURL : public QObject
{
    Q_OBJECT
public:
    RechercheURL(QObject *parent=0);

    void RequeteAlbums(QString rech);
};

#endif // RECHERCHEURL_H
