#ifndef BDDPLAYLIST_H
#define BDDPLAYLIST_H

#include <QObject>
#include "util.h"
#include "bddmp3.h"


class BDDPlaylist : public BDDMp3
{
public:
    explicit BDDPlaylist(QObject *parent = 0);
    
    //Affichage des Playlists
    PlaylistGestion RecupererInfosPlaylist(QString Id);
    QList<MP3Gestion> RecupererPistesPlaylist(QString Id);
    QList<PlaylistGestion> ListesPlaylist();
    QStringList listePlaylistMP3(QString Id);

    //En rapport avec la BDD ( ajout, modification, suppression)
    QString CreerPlaylist(PlaylistGestion play);
    void AjouterMP3dansPlaylist(int IdMp3, int IdPlay);
    int NumPisteMaxPlaylist(int IdPlay);

};

#endif // BDDPLAYLIST_H
