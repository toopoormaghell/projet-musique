#ifndef BDDLISTEPLAYLIST_H
#define BDDLISTEPLAYLIST_H

#include <QObject>
#include "bddsingleton.h"
class BDDListePlaylist : public QObject
{
      Q_OBJECT
public:
  explicit  BDDListePlaylist( QObject* parent = nullptr  );

    void EnregistrerPlaylist(QString nom_playlist);
    void SupprimerPlaylist(int id_playlist);
    QStringList listePlaylist();

    QList<int> listeMp3(int id_Playlist, int Ordre);
    QString NbMp3(int id_Playlist);
    QString OrderBy(int Ordre);
};

#endif // BDDLISTEPLAYLIST_H
