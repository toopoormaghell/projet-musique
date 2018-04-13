#include "DialogChoixAlbumPhys.h"
#include "ui_dialogchoixalbumphys.h"
#include "bddaffichermp3.h"
#include "meta_album.h"

DialogChoixAlbumPhys::DialogChoixAlbumPhys( QString artiste, QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::ChoixAlbumPhysDialog ),
    m_artiste( artiste )
{
    ui->setupUi( this );

    AfficherAlbums();
    ui->ListeAlbums->setModel( &m_albums );
}

DialogChoixAlbumPhys::~DialogChoixAlbumPhys()
{
    delete ui;
}
void DialogChoixAlbumPhys::AfficherAlbums()
{
    //Création du modèle pour le QListView
    m_albums.clear();

    //Première chose, on récupère l'artiste
    QList<int> albums = m_bddInterface.listeAlbums( m_artiste , "0" );

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {
        //Pour chaque album...
        Meta_Album* album = Meta_Album::RecupererBDD( albums[cpt] );

        QStandardItem* item = new QStandardItem;
        //on affiche la pochette
        QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );
        item->setIcon( QIcon( scaled ) );
        item->setData( album->getid_alb(), Qt::UserRole );
        item->setText( QString::number( album->getannee() ) + " - " + album->getnom_album() );
        //On ajoute l'item dans le modèle
        m_albums.setItem( cpt, item );
        delete album;
    }

}
void DialogChoixAlbumPhys::on_buttonBox_accepted()
{
    m_selection = RecupererAlbumSelectionne();

}
int DialogChoixAlbumPhys::RecupererAlbumSelectionne()
{
    QModelIndex index = ui->ListeAlbums->currentIndex();

    return index.data( Qt::UserRole ).toInt();
}

void DialogChoixAlbumPhys::on_buttonBox_rejected()
{
    m_selection = 0;
}
