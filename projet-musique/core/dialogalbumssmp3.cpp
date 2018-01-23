#include "dialogalbumssmp3.h"
#include "ui_dialogalbumssmp3.h"
#include "meta_album.h"

DialogAlbumSSMP3::DialogAlbumSSMP3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAlbumSSMP3)
{
    ui->setupUi(this);
    AjouterAlbums();
}

DialogAlbumSSMP3::~DialogAlbumSSMP3()
{
    delete ui;
}
void DialogAlbumSSMP3::AjouterAlbums()
{
    ui->ListeAlbums->clear();

    //Affichage des albums
    QList<int> albums = m_bddInterface.AlbSansMP3( "-1", -1 );

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {

        if ( albums[cpt] > 0 )
        {
            Meta_Album* album = Meta_Album::RecupererBDD( albums[cpt] );
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );

            item->setIcon( QIcon( scaled ) );


            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, album->getid_alb() );
            item->setText( QString::number( album->getannee() ) + " - " + album->getnom_album() );

            ui->ListeAlbums->addItem( item );

            delete album;
        }

    }

}
