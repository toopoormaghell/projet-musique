#include "DialogChoixAlbumPhys.h"
#include "ui_choixalbumphysdialog.h"
#include "bddaffichermp3.h"
#include "bddalbum.h"
#include "bddpoch.h"
#include "bddartiste.h"

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
    BDDArtiste* art = BDDArtiste::RecupererArtparNom( m_artiste );

    QList<int> albums = m_bddInterface.listeAlbums( QString::number( art->id() ), "0" );

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {
        //Pour chaque album...
        BDDAlbum* album = BDDAlbum::RecupererAlbum( albums[cpt] );

        QStandardItem* item = new QStandardItem;
        //on affiche la pochette
        QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        item->setData( album->id(), Qt::UserRole );
        item->setText( QString::number( album->m_annee ) + " - " + album->m_nom );
        //On ajoute l'item dans le modèle
        m_albums.setItem( cpt, item );
        delete album;
    }
    delete art;
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
