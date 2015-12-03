#ifndef BDDAFFICHERMP3_H
#define BDDAFFICHERMP3_H

#include <QObject>
#include "bddsingleton.h"
#include "util.h"

class BDDAfficherMp3 : public QObject
{
    Q_OBJECT

public:
    explicit BDDAfficherMp3(QObject *parent = 0);
    QList<int> ListeArtiste(QString type);
    QStringList listeTitresAlbumMp3(QString Album, QString Categorie);
    QStringList MP3Artiste(QString id_artiste);
    QList<int> listeAlbums(QString Id_Artiste, QString Categorie);
    QStringList RecupererListeTypes(const QString categorie);
    AlbumPhys RecupererAlbumMp3(QString id_album);
private:
    QString AnneesSwitch(QString annee);

};

#endif // BDDAFFICHERMP3_H
