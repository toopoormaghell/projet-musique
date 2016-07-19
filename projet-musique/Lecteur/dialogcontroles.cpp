#include "dialogcontroles.h"
#include "ui_dialogcontroles.h"
#include <QMediaPlayer>
#include <QAudioDeviceInfo>
#include <QDir>
#include <QFile>


DialogControles::DialogControles( QWidget *parent) :
    QWidget(parent),player (new QMediaPlayer(this)),
    ui(new Ui::DialogControles),  mp3(  )
{
    ui->setupUi(this);

    AfficherIcones();

    connect( player,SIGNAL( positionChanged(qint64)), this, SLOT(avancerSlider( qint64 )));
    connect( player,SIGNAL(durationChanged(qint64)),this,SLOT(changerduree(qint64)));

}

DialogControles::~DialogControles()
{
    delete ui;
}

void DialogControles::ChangerMP3(QString temp)
{
    player->stop();

    mp3= temp;
    ChargerMp3();
    AfficherInfos();
}

void DialogControles::Changer(QString temp)
{
    mp3 = temp;
    player->setMedia(QUrl::fromLocalFile(mp3));
    AfficherInfos();
}
void DialogControles::AfficherIcones()
{
    QPixmap icone (":/Icones/play");
    ui->Lecture->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/stop");
    ui->Arret->setIcon( QIcon ( icone ) );

    ui->Volume->setSliderPosition(100);

}
void DialogControles::AfficherInfos()
{
    if (!mp3.isEmpty())
    {
        QString temp = mp3.mid(8);

        // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
        QByteArray arrFileName = QFile::encodeName( temp );
        const char* encodedName = arrFileName.constData();
        TagLib::FileRef f( encodedName );

        //On récupère l'artiste, l'album, le titre et le numéro de piste
        TagLib::String artist = f.tag()->artist();
        TagLib::String album =  f.tag()->album();
        TagLib::uint date = f.tag()->year();
        TagLib::String title =  f.tag()->title();
        TagLib::uint track = f.tag() -> track();

        ui->Album->setText( QString::number( date ) + " - " +TStringToQString( album ) );
        ui->Titre->setText( QString::number(track).rightJustified(2,'0') + " - " + TStringToQString( title ) );
        ui->Artiste->setText( TStringToQString( artist ) );

        //On s'occupe de la pochette
        ui->Pochette->setPixmap( ImageAlbum ( f ) );
    }
}
QPixmap DialogControles::ImageAlbum ( const TagLib::FileRef& f )
{
    //On s'occupe de la pochette de l'album qu'on enregistre
    QImage Image;
    TagLib::ID3v2::Tag Tag( f.file(), 0 );
    TagLib::ID3v2::FrameList Liste = Tag.frameListMap()["APIC"];
    TagLib::ID3v2::AttachedPictureFrame* Pic = static_cast<TagLib::ID3v2::AttachedPictureFrame*>( Liste.front() );

    if ( ( Pic == NULL ) || Pic->picture().isEmpty() )
    {
        Image.fromData( "./Pochettes/def.jpg" );

    }
    else
    {
        Image.loadFromData( ( const uchar* ) Pic->picture().data(), Pic->picture().size() );
    }
    QPixmap scaled( QPixmap::fromImage( Image ) );
    scaled = scaled.scaled( 75, 75 );

    return scaled;
}

void DialogControles::on_Lecture_clicked()
{
    QPixmap icone( ":/Icones/pause" );

    switch (player->state())
    {
    case ( QMediaPlayer::StoppedState ):  ui->Lecture->setIcon( QIcon ( icone ) );  ChargerMp3(); player->play();  break;
    case ( QMediaPlayer::PlayingState ):   icone.load(":/Icones/play"); ui->Lecture->setIcon( QIcon ( icone ) ); player->pause();break;
    case ( QMediaPlayer::PausedState ): ui->Lecture->setIcon( QIcon ( icone ) );  player->play();break;
    }

}

void DialogControles::ChargerMp3()
{
    player->setMedia(QUrl::fromLocalFile(mp3));
    QPixmap icone( ":/Icones/pause" );
     ui->Lecture->setIcon( QIcon ( icone ) );
    player->play();
}

void DialogControles::on_Arret_clicked()
{
    player->stop();
    QPixmap icone( ":/Icones/play" );
    ui->Lecture->setIcon( QIcon ( icone ) );
}

void DialogControles::on_Volume_sliderMoved(int position)
{
    player->setVolume(position);
}

void DialogControles::avancerSlider(qint64 pos)
{
    ui->Position->setValue(pos);

}

void DialogControles::changerduree(qint64 dur)
{
    ui->Position->setMaximum( dur );
}
void DialogControles::on_Position_sliderReleased()
{
    player->setPosition( ui->Position->value() );
}
