#ifndef BDDREL_PLAYLIST_H
#define BDDREL_PLAYLIST_H

#include <QObject>
#include "bddsingleton.h"

class BDDRel_Playlist: public QObject
{
    Q_OBJECT
public:
    explicit BDDRel_Playlist(QObject* parent = nullptr);

    void AjoutRel_Playlist(int id_playlist, int id_relation);
void AjouterAlbumEnPlaylist(int id_playlist, int id_album);

};

#endif // BDDREL_PLAYLIST_H
