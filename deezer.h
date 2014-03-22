#ifndef DEEZER_H
#define DEEZER_H

#include <QObject>
#include "util.h"

class Deezer: public QObject
{
    Q_OBJECT
public:
    explicit Deezer(QObject *parent = 0);

    QStringList RequeteAlbums(QString rech);
    AlbumGestion *RequeteInfosAlbum(QString chemin, QString type);
    QString accents(QString nom);

};
#endif // DEEZER_H
