#include "playlistmanager.h"
#include <QMediaPlaylist>



PlaylistManager::~PlaylistManager()
{
}



PlaylistManager::PlaylistManager() :
    QObject()
  , m_playlist( new QMediaPlaylist )
{
}
