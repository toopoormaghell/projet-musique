#ifndef DISCOGS_H
#define DISCOGS_H

#include <QObject>
#include "util.h"

class Discogs : public QObject
{
    Q_OBJECT
public:
    explicit Discogs(QObject *parent = 0);

    QString RequeteAlbums(QString rech);
    AlbumGestion *RequeteInfosAlbum(QString chemin);
    QString accents(QString nom);
signals:

};

#endif // DISCOGS_H
