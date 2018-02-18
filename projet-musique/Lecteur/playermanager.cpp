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
    afficherIcones();
    playlist->setPlaybackMode( QMediaPlaylist::Loop);
    ui->ListePlaylist->setVisible( false );
    ui->ListePlaylist->setWindowFlags( Qt::Popup );
}

PlayerManager::~PlayerManager()
{
    delete ui;
}

void PlayerManager::setDialogControles(DialogControles* dialogControles)
{
    m_controles = dialogControles;
    player =  m_controles->player;

    connect ( this,SIGNAL ( changerMp3 ( QMediaContent ) ) , m_controles,SLOT ( ChangerMP3 ( QMediaContent ) ) );

}

void PlayerManager::setPlaylist(QStringList temp)
{
    if ( !temp.isEmpty() )
    {
        m_listechemins = temp;
        playlist->clear();
        for (int cpt=0;cpt<temp.count();cpt++)
        {
            QFile fichier(temp[cpt]);


            if(fichier.exists() )

            {
                QMediaContent media ( QUrl::fromLocalFile ( temp[cpt] ) ) ;

                playlist->addMedia ( media ) ;

            }
        }
        afficherPlaylist();
        playlist->setCurrentIndex(0);

        emit changerMp3 ( playlist->currentMedia() );



    }
}

void PlayerManager::on_Precedent_clicked()
{

    playlist->previous();
    ui->Nb->setText(QString::number(playlist->currentIndex()+1 ) +"/"+ QString::number( playlist->mediaCount() ) );
    emit changerMp3 ( playlist->currentMedia() );
}

void PlayerManager::on_Suivant_clicked()
{
    playlist->next();
    ui->Nb->setText(QString::number(playlist->currentIndex()+1 ) +"/"+ QString::number( playlist->mediaCount() ) );
    emit changerMp3 ( playlist->currentMedia() );
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
void PlayerManager::afficherIcones()
{
    QPixmap icone (":/Icones/aleag");
    ui->Aleatoire->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/dossiers");
    ui->Dossiers->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/precedent");
    ui->Precedent->setIcon( QIcon ( icone ) );

    icone.load( ":/Icones/suivant");
    ui->Suivant->setIcon( QIcon ( icone ) );

    ui->Suppression->setObjectName( "suppression");

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
    ui->Nb->setText(QString::number(playlist->currentIndex()+1 ) +"/"+ QString::number( playlist->mediaCount() ) );
}
QString PlayerManager::ExtraireInfosMp3(QString mp3)
{
    //Première étape, on extrait les données nécessaires par Taglib
    QString temp = mp3.mid(8);

    // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
    QByteArray arrFileName = QFile::encodeName( temp );
    const char* encodedName = arrFileName.constData();
    TagLib::FileRef f( encodedName );

    if ( !f.isNull() )
    {
        //On récupère l'artiste, l'album, le titre et le numéro de piste
        TagLib::String artist = f.tag()->artist();
        TagLib::String title =  f.tag()->title();
        TagLib::uint track = f.tag() -> track();

        return QString::number(track).rightJustified(2,'0') + " - " + TStringToQString( title ) + " / " + TStringToQString( artist ) ;
    } else
    {
        return "pas de mp3.";
    }
}

void PlayerManager::on_Dossiers_clicked()
{
    ui->ListePlaylist->setVisible( true );
    ui->ListePlaylist->move( QCursor::pos().x() - ui->ListePlaylist->frameGeometry().width(), QCursor::pos().y() );
}

void PlayerManager::on_Suppression_clicked()
{
    QList<QListWidgetItem *> selection = ui->Playlist->selectedItems();

    for (int cpt = 0; cpt < selection.count() ; cpt++ )
    {
        QListWidgetItem* item = selection[cpt];

        playlist->removeMedia( item->data(Qt::UserRole).toInt() );
        m_listechemins.removeAt( item->data(Qt::UserRole).toInt() );

    }

    afficherPlaylist();
    emit SupprimerdansPlaylist( m_listechemins );
}

void PlayerManager::on_Playlist_clicked(const QModelIndex &index)
{
    playlist->setCurrentIndex( index.row() );
    ui->Nb->setText(QString::number(playlist->currentIndex()+1 ) +"/"+ QString::number( playlist->mediaCount() ) );
    emit changerMp3( playlist->currentMedia() );
}

void PlayerManager::FinMP3()
{
    playlist->next();
    ui->Nb->setText(QString::number(playlist->currentIndex()+1 ) +"/"+ QString::number( playlist->mediaCount() ) );
    emit changerMp3( playlist->currentMedia() );
}
