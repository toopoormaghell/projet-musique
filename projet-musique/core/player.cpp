#include "player.h"
#include "ui_player.h"
#include "ongletmp3.h"
#include "bddinterface.h"
#include <QDebug>


Player::Player(QWidget *parent) :
    QWidget(parent),
    m_mediaObject( this ),
    m_mediaAudioOutput( Phonon::MusicCategory, this ),
    ui(new Ui::Player)
{
    Phonon::createPath( &m_mediaObject, &m_mediaAudioOutput );
    ui->setupUi(this);

    QObject::connect( &m_mediaObject, SIGNAL( tick( qint64 ) ), this, SLOT( updateTime( qint64 ) ) );
}

Player::~Player()
{
    delete ui;
}

void Player::setParentTab(const OngletMp3 &parentTab)
{
    m_parentTab = &parentTab;
}

void Player::on_m_playPause_clicked()
{
    BDDInterface tmp;
    QString selectedId = m_parentTab->getSelectedTitleId();
    if ( !selectedId.isEmpty() )
    {
        QString filePath = tmp.getPathFromIdMp3( selectedId );
        if ( !filePath.isEmpty() )
        {
            m_mediaObject.stop();
            updateTime( 0 );
            updateSlider( 0 );
            m_mediaObject.setCurrentSource( filePath );
            m_mediaObject.play();
            m_mediaObject.setTickInterval( 1000 );
        }
    }
}

void Player::on_m_stopButton_clicked()
{
    m_mediaObject.stop();
    m_mediaObject.setTickInterval( 0 );
}

void Player::updateTime(qint64 time)
{
    const qint64 nbSec = time / 1000;
    const qint64 nbMin = nbSec / 60;
    const qint64 remainingSec = nbSec - nbMin * 60;
    ui->m_time->setText( QString::number( nbMin ).rightJustified( 2, '0' ) + ":" + QString::number( remainingSec ).rightJustified( 2, '0' ) );
}

void Player::updateSlider(qint64 time)
{
    const qint64 totalTime = m_mediaObject.totalTime();
    ui->m_songSlider->setSliderPosition( (int)( (float)time / (float)totalTime * 100.0f ) );
}

void Player::on_m_songSlider_sliderMoved(int position)
{
    if ( !ui->m_songSlider->isSliderDown() )
    {
        const qint64 totalTime = m_mediaObject.totalTime();
        const qint64 timeToSet = (float)position / 100.0f * totalTime;
        m_mediaObject.seek( timeToSet );
    }
}

void Player::on_m_songSlider_valueChanged(int value)
{
    const qint64 totalTime = m_mediaObject.totalTime();
    m_mediaObject.seek( (qint64)( (float)value / 100.0f * totalTime ) );
}
