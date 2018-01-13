#include "dialogalbumssmp3.h"
#include "ui_dialogalbumssmp3.h"
#include "bddalbum.h"
#include "bddpoch.h"

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

        BDDAlbum* album = BDDAlbum::recupererBDD( albums[cpt] );

        if ( album->id() > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );

            item->setIcon( QIcon( scaled ) );


            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, albums[cpt] );
            item->setText( QString::number( album->m_annee ) + " - " + album->m_nom );

            ui->ListeAlbums->addItem( item );

        }
        delete album;
    }

}
