#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H



#include <QObject>
#include <QScopedPointer>
class QMediaPlaylist;



class PlaylistManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( PlaylistManager )

public:
    PlaylistManager();
    virtual ~PlaylistManager();



private:
    // Objet Qt gerant une playlist
    QScopedPointer<QMediaPlaylist> m_playlist;
};



#endif // PLAYLISTMANAGER_H
