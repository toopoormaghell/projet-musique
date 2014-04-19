#ifndef DISCOGS_H
#define DISCOGS_H

#include <QObject>
#include "util.h"

class Discogs : public QObject
{
    Q_OBJECT
public:
    explicit Discogs(QObject *parent = 0);

    AlbumGestion RequeteAlbums(QString rech);
    AlbumGestion LectureXMLSearch(QByteArray fich);
    QString LectureXMLArtiste(QByteArray fich);
    QImage LectureXMLPochette(QByteArray fich);
    QImage RecupererPochette(QString lien);
    QList<TitreGestion> LectureXMLTitres(QByteArray fich);
    int LectureXMLPages(QByteArray fich);
signals:

};

#endif // DISCOGS_H
