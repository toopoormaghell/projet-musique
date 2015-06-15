#ifndef RECHERCHEURL_H
#define RECHERCHEURL_H

#include <QObject>
#include <QMap>
#include "util.h"


class RechercheURL : public QObject
{
    Q_OBJECT
public:
    RechercheURL(QObject *parent=0);

    AlbumPhys RequeteAlbums(QString rech, int Type);
    QString m_interaction;
signals:
    void test();

private:
    QMap<QString, QString> LectureXML(QByteArray fichier);
    AlbumPhys m_album;
    int m_pages;
    QMap<QString, QString> Requete(QStringList attributs);
    void RequeteTitres(QStringList attributs);
    void LectureXMLTitres(QByteArray fichier);
    void RecupererPoch(QString lien);
    QStringList RequeteReleases(QStringList attributs);
    QStringList LectureXMLReleases(QByteArray fichier);

};

#endif // RECHERCHEURL_H
