#include "playlistmanager.h"
#include <QMediaPlaylist>



PlaylistManager::PlaylistManager() :
    QObject()
  , m_playlist( new QMediaPlaylist )
{
}



PlaylistManager::~PlaylistManager()
{
}
