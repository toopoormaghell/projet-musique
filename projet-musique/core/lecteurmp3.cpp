#include "lecteurmp3.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <lecteurmp3gui.h>



LecteurMP3::LecteurMP3( LecteurMP3Gui* const gui, QObject* parent ) :
    QObject(parent),
    m_player( new QMediaPlayer ),
    m_playlist( new QMediaPlaylist ),
    m_lecteurGui( gui )
{
    QObject::connect( m_lecteurGui, SIGNAL( playPauseClicked() ), this, SLOT( on_playPause_clicked() ) );
}



LecteurMP3::~LecteurMP3()
{
}



void LecteurMP3::on_playPause_clicked()
{
    m_player->play();
}
