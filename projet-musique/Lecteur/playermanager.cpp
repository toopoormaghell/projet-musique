#include "playermanager.h"
#include "ui_playermanager.h"
#include <QStringList>
#include "dialogcontroles.h"
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QList>
#include <QFile>
PlayerManager::PlayerManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerManager),player()
  , playlist( new QMediaPlaylist ),
    m_aleatoire ( false )
{
    ui->setupUi(this);
    playlist->setPlaybackMode( QMediaPlaylist::Loop);
            ui->ListePlaylist->setVisible( false );
}

PlayerManager::~PlayerManager()
{
    delete ui;
}

void PlayerManager::setDialogControles(DialogControles* dialogControles)
{
    m_controles = dialogControles;
    player =  m_controles->player;

    connect (this,SIGNAL(changerMp3(QString)),m_controles,SLOT(ChangerMP3(QString)));
    connect ( this, SIGNAL(PremierMP3(QString)), m_controles,SLOT(Changer(QString)));
}

void PlayerManager::setPlaylist(QStringList temp)
{
    for (int cpt=0;cpt<temp.count();cpt++)
    {
        QMediaContent media(QUrl::fromLocalFile(temp[cpt]));

        playlist->addMedia(media);
    }
    playlist->setCurrentIndex(0);
    emit PremierMP3(playlist->currentMedia().canonicalUrl().toString());

    afficherPlaylist();
}

void PlayerManager::on_Precedent_clicked()
{

    playlist->previous();

    emit changerMp3(playlist->currentMedia().canonicalUrl().toString());
}

void PlayerManager::on_Suivant_clicked()
{
    playlist->next();

    emit changerMp3(playlist->currentMedia().canonicalUrl().toString());
}


void PlayerManager::on_Aleatoire_clicked()
{
    m_aleatoire = !m_aleatoire;

    if ( m_aleatoire)
    {
        QPixmap icone (":/Icones/alea");
        ui->Aleatoire->setIcon( QIcon ( icone ) );
        playlist->setPlaybackMode( QMediaPlaylist::Random);

    } else
    {
        QPixmap icone (":/Icones/aleag");
        playlist->setPlaybackMode( QMediaPlaylist::Loop);
        ui->Aleatoire->setIcon( QIcon ( icone ) );

    }

}
void PlayerManager::afficherPlaylist()
{
    ui->Playlist->clear();
    for (int cpt = 0; cpt < playlist->mediaCount(); cpt ++)
    {

        QListWidgetItem* item = new QListWidgetItem;

        item->setText(  ExtraireInfosMp3( playlist->media( cpt ).canonicalUrl().toString() ) );
        item->setData(Qt::UserRole, cpt);
        ui->Playlist->addItem( item );
    }
}
QString PlayerManager::ExtraireInfosMp3(QString mp3)
{
    //Première étape, on extrait les données nécessaires par Taglib
    QString temp = mp3.mid(8);

    // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
    QByteArray arrFileName = QFile::encodeName( temp );
    const char* encodedName = arrFileName.constData();
    TagLib::FileRef f( encodedName );

    //On récupère l'artiste, l'album, le titre et le numéro de piste
    TagLib::String artist = f.tag()->artist();
    TagLib::String title =  f.tag()->title();
    TagLib::uint track = f.tag() -> track();

    return QString::number(track).rightJustified(2,'0') + " - " + TStringToQString( title ) + " / " + TStringToQString( artist ) ;

}

void PlayerManager::on_Dossiers_clicked()
{
    if ((ui->ListePlaylist->isVisible()) )
    {
        ui->ListePlaylist->setVisible( false );
    }
    else
    {
        ui->ListePlaylist->setVisible( true );
    }

}

void PlayerManager::on_Suppression_clicked()
{
    QList<QListWidgetItem *> selection = ui->Playlist->selectedItems();

    for (int cpt = 0; cpt < selection.count() ; cpt++ )
    {
        QListWidgetItem* item = selection[cpt];

        playlist->removeMedia( item->data(Qt::UserRole).toInt() );

    }

afficherPlaylist();
}