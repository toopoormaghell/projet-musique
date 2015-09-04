#include "playlistmanager.h"
#include <QMediaPlaylist>



PlaylistManager::PlaylistManager() :
    QObject()
  , m_playlist( new QMediaPlaylist )
  , m_titre()
{
}



PlaylistManager::~PlaylistManager()
{
}



void PlaylistManager::setTitre( QString const& titre )
{
    m_titre = titre;
    qDebug() << "PlaylistManager::setTitre( " << titre << " );";
}
