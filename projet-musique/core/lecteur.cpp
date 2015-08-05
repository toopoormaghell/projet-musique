#include "lecteur.h"
#include "ui_lecteur.h"
#include <QMediaPlayer>
#include <QFile>
#include <QAudioDeviceInfo>
#include "ongletmp3.h"
#include "bddmp3.h"

Lecteur::Lecteur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lecteur),
    m_player(new QMediaPlayer)
{
    ui->setupUi(this);
    QList<QAudioDeviceInfo> devices= QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

    QObject::connect(m_player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
}

Lecteur::~Lecteur()
{
    delete ui;
}
void Lecteur::Lecture()
{
    BDDMp3* mp3 = BDDMp3::RecupererMp3( m_parentTab->titreLecteur());
    m_player->setMedia(QUrl::fromLocalFile(mp3->m_chemin));
    m_player->setVolume(100);
    m_player->play();
    positionChanged(m_player->position());

}
void Lecteur::Stop()
{
    m_player->stop();
}

void Lecteur::setParentTab(const OngletMP3 &parentTab)
{
    m_parentTab = &parentTab;
}

void Lecteur::on_Lecture_clicked()
{
    Lecture();
}
void Lecteur::on_Stop_clicked()
{
    Stop();
}
void Lecteur::positionChanged(qint64 time)
{
    const qint64 totalTime= m_player->duration();
    ui->LectureEnCours->setSliderPosition( (int)((float)time/(float)totalTime*100.0f) );
}
void Lecteur::on_LectureEnCours_sliderMoved(int position)
{
    const qint64 totalTime = m_player->duration();
    const qint64 timeToSet = (float)position / 100.0f * totalTime;
    m_player->setPosition(timeToSet);
}
