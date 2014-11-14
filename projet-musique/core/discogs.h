#ifndef DISCOGS_H
#define DISCOGS_H

#include <QObject>
#include "util.h"
#include "bddinterface.h"
class Discogs : public QObject
{
    Q_OBJECT
public:
    explicit Discogs(QObject *parent = 0);

    AlbumGestion RequeteAlbums(QString rech);
    CompilGestion LectureXMLSearchCompil(QByteArray fich);
    QString LectureXMLArtiste(QByteArray fich);
    QImage LectureXMLPochette(QByteArray fich);
    QImage RecupererPochette(QString lien);
    QList<TitreGestion> LectureXMLTitres(QByteArray fich);
    int LectureXMLPages(QByteArray fich);
    QList<TitreGestion> RecupererTitres(QString Id_Album);
    QString RecupererArtistes(QString Id_Album);

    bool LectureErreurPochette(QByteArray fich);
    QString RecupererId_Album(QString Id_Album);
    QString LectureXMLId_Album(QByteArray fich);
    QList<TitreGestion> RecupererTitresAlbums(QString Id_Album);
    QStringList LectureXMLReleases(QByteArray fich);
    QByteArray LirePochette(QString Id_Album);
    CompilGestion RequeteCompil(QString rech);
    QList<MP3Gestion> RecupererTitresCompil(QString Id_Album);
    QList<MP3Gestion> LectureXMLTitresCompil(QByteArray fich);
    AlbumGestion LectureXMLSearch(QByteArray fich);
    QString RecupererArtisteTitre(QString Id_Titre);

private:
    BDDInterface m_bddInterface;
};

#endif // DISCOGS_H
