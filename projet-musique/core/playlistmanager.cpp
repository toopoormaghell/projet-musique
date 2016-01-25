#include "playlistmanager.h"
#include <QMediaPlaylist>



PlaylistManager::PlaylistManager( QObject* parent ) :
    QObject( parent )
  , m_playlist( new QMediaPlaylist )
  , m_categorie()
  , m_artiste()
  , m_album()
  , m_titre()
{
}



PlaylistManager::~PlaylistManager()
{
}



void PlaylistManager::setCategorie( QString const& categorie )
{
    m_categorie = categorie;
    qDebug() << "PlaylistManager::setCategorie( " << categorie << " );";
}



void PlaylistManager::setArtiste( QString const& artiste )
{
    m_artiste = artiste;
    qDebug() << "PlaylistManager::setArtiste( " << artiste << " );";
}



void PlaylistManager::setAlbum( QString const& album )
{
    m_album = album;
    qDebug() << "PlaylistManager::setAlbum( " << album << " );";
}



void PlaylistManager::setTitre( QString const& titre )
{
    m_titre = titre;
    qDebug() << "PlaylistManager::setTitre( " << titre << " );";
}
