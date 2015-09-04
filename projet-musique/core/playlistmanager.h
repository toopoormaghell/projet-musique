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

    void setTitre( QString const& titre );



private:
    // Objet Qt gerant une playlist
    QScopedPointer<QMediaPlaylist> m_playlist;
    // Titre selectionné
    QString m_titre;
};



#endif // PLAYLISTMANAGER_H
