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
    explicit PlaylistManager( QObject* parent = NULL );
    virtual ~PlaylistManager();

    void setCategorie( QString const& categorie );
    void setArtiste( QString const& artiste );
    void setAlbum( QString const& album );
    void setTitre( QString const& titre );



private:
    // Objet Qt gerant une playlist
    QScopedPointer<QMediaPlaylist> m_playlist;
    // Catégorie selectionnée
    QString m_categorie;
    // Artiste selectionné
    QString m_artiste;
    // Album selectionné
    QString m_album;
    // Titre selectionné
    QString m_titre;
};



#endif // PLAYLISTMANAGER_H
