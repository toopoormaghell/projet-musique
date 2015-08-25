#include "lecteurmp3gui.h"
#include "ui_lecteurmp3gui.h"
//#include <QMediaPlayer>
//#include <QFile>
//#include <QAudioDeviceInfo>
//#include "ongletmp3.h"
//#include "bddmp3.h"
//#include "bddaffichermp3.h"
//#include "bddtitre.h"
//#include <QMediaPlaylist>
//#include "bddalbum.h"
//#include "bddpoch.h"



LecteurMP3Gui::LecteurMP3Gui(QWidget *parent) :
    QWidget(parent),
    ui( new Ui::LecteurMP3Gui )/*,
    m_player(new QMediaPlayer),
    m_playlist(new QMediaPlaylist)*/
{
    ui->setupUi(this);

    QObject::connect( ui->controleLecture, SIGNAL( playPauseClicked() ), this, SIGNAL( playPauseClicked() ) );
//    QList<QAudioDeviceInfo> devices= QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

//    QObject::connect(m_player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
//    QObject::connect(m_player,SIGNAL(metaDataChanged()),this,SLOT(AfficherTag()));
}



LecteurMP3Gui::~LecteurMP3Gui()
{
    delete ui;
}



//void LecteurMP3Gui::Lecture()
//{
//    m_player->setVolume(100);
//    m_player->play();
//    positionChanged(m_player->position());
//}


//void LecteurMP3Gui::Stop()
//{
//    m_player->stop();
//}

//void LecteurMP3Gui::setParentTab(const OngletMP3 &parentTab)
//{
//    m_parentTab = &parentTab;
//}

//void LecteurMP3Gui::on_Lecture_clicked()
//{
//    BDDMp3* mp3 = BDDMp3::RecupererMp3( m_parentTab->titreLecteur());
//    m_player->setMedia(QUrl(mp3->m_chemin));
//    Lecture();
//}
//void LecteurMP3Gui::on_Stop_clicked()
//{
//    Stop();
//}
//void LecteurMP3Gui::positionChanged(qint64 time)
//{
////    const qint64 totalTime= m_player->duration();
////    ui->LectureEnCours->setSliderPosition( (int)((float)time/(float)totalTime*100.0f) );
//}
//void LecteurMP3Gui::on_LectureEnCours_sliderMoved(int position)
//{
////    const qint64 totalTime = m_player->duration();
////    const qint64 timeToSet = (float)position / 100.0f * totalTime;
////    m_player->setPosition(timeToSet);
//}

//void LecteurMP3Gui::on_AleaArtiste_clicked()
//{
//    m_player->stop();
//    m_playlist->clear();
//    BDDAfficherMp3 temp;
//    QStringList chemins = temp.MP3Artiste(m_parentTab->artisteLecteur());

//    for (int cpt=0;cpt<chemins.count();cpt++)
//    {
//        m_playlist->addMedia(QUrl(chemins[cpt].replace("$","'")));
//    }
//    m_playlist->setCurrentIndex(1);
//    m_playlist->shuffle();
//    m_player->setPlaylist(m_playlist);
//    Lecture();
//}
//void LecteurMP3Gui::AfficherTag()
//{
////    //On récupère le chemin du mp3 que nous sommes en train de lire
////    QString chemin=m_player->currentMedia().canonicalUrl().toString();
////    chemin[0]= chemin[0].toUpper();
////    //On récupère le mp3 en question
////    BDDMp3* mp3 = BDDMp3::RecupererMp3ParChemin(chemin);
////    //On affiche les infos pertinentes
////    QString temp = QString::number(mp3->m_titre->m_num_piste).rightJustified(2,'0');

////    ui->Mp3lu->setText(temp+"-"+mp3->m_titre->m_nom);
////    //On met en place la pochette
////    QPixmap scaled( QPixmap::fromImage( mp3->m_album->m_pochette->m_image  ) );
////    scaled = scaled.scaled( 50, 50 );
////    ui->Pochette->setPixmap(scaled);

//}
