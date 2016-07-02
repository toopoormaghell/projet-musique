#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QAudioDeviceInfo>
#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), player (new QMediaPlayer(this)), titre("F:\\Albums\\Farmer Mylene\\2015 - Interstellaires\\06 - Love Song.mp3")
{
    ui->setupUi(this);
    AfficherIcones();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::AfficherIcones()
{
    QPixmap icone (":/Icones/play");
    ui->Lecture->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/stop");
    ui->Arret->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/dossiers");
    ui->Aleatoire->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/precedent");
    ui->Precedent->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/avance");
    ui->Dossiers->setIcon( QIcon ( icone ) );

    icone.load(":/Icones/suivant");
    ui->Suivant->setIcon( QIcon ( icone ) );

    ui->Volume->setSliderPosition(100);

}

void MainWindow::on_Lecture_clicked()
{
    QPixmap icone( ":/Icones/pause" );

    switch (player->state())
    {
    case ( QMediaPlayer::StoppedState ):  ui->Lecture->setIcon( QIcon ( icone ) );  player->setMedia(QUrl::fromLocalFile(titre)); player->play(); break;
    case ( QMediaPlayer::PlayingState ):   icone.load(":/Icones/play"); ui->Lecture->setIcon( QIcon ( icone ) ); player->pause();break;
    case ( QMediaPlayer::PausedState ): ui->Lecture->setIcon( QIcon ( icone ) );  player->play();break;
    default :  ui->Lecture->setIcon( QIcon ( icone ) ); player->setMedia(QUrl::fromLocalFile(titre)); player->play(); break;
    }

}

void MainWindow::on_Arret_clicked()
{
    player->stop();
}

void MainWindow::on_Volume_sliderMoved(int position)
{
   player->setVolume(position);
}
