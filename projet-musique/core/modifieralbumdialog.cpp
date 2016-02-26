#include "modifieralbumdialog.h"
#include "ui_modifieralbumdialog.h"
#include "util.h"
#include <QListWidgetItem>
#include "bddgestionphys.h"
#include <QDebug>
#include "bddafficherphys.h"
#include "bddalbum.h"


ModifierAlbumDialog::ModifierAlbumDialog( int selection, QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::ModifierAlbumDialog ),
    m_selection( selection )
{
    ui->setupUi( this );
    AfficherAlbum();
}

ModifierAlbumDialog::~ModifierAlbumDialog()
{
    delete ui;
}

void ModifierAlbumDialog::AfficherAlbum()
{


    //On récupère l'album à afficher
    m_album = BDDAlbum::RecupAlbumEntite( m_selection );

    //On met le nom, l'artiste, l'année
    ui->Album->setText( m_album.Album );
    ui->Annee->setText( QString::number( m_album.Annee ) );
    ui->Artiste->setText( m_album.Artiste );

    //On affiche la pochette
    QPixmap scaled( QPixmap::fromImage( m_album.Poch ) );
    scaled = scaled.scaled( 100, 100 );
    ui->Pochette->setPixmap( scaled );

    //On affiche les titres
    for ( int comp = 0; comp < m_album.titres.count(); comp++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( m_album.titres[comp].Titre );
        item->setFlags ( item->flags () | Qt::ItemIsEditable );
        ui->Titres->addItem( item );
        ui->Duree->addItem( m_album.titres[comp].Duree );
        ListeNumeros();
    }
    //On affiche le type de l'album

    ui->Type->setCurrentText( m_album.Type_Str );
}
void ModifierAlbumDialog::ListeNumeros()
{
    ui->Num_Pistes->clear();
    for ( int i = 1; i < ui->Titres->count() + 1; i++ )
    {
        ui->Num_Pistes->addItem( new QListWidgetItem( QString::number( i ).rightJustified( 2, '0' ) + " - " ) );
    }
}

void ModifierAlbumDialog::EnregistrerAlbum()
{

    m_album.Album = ui->Album->text();
    m_album.Artiste = ui->Artiste->text();
    m_album.Annee = ui->Annee->text().toInt();
    m_album.Type = ui->Type->currentIndex() + 1;

    //On récupère la pochette
    const QPixmap* pixmap = ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    m_album.Poch = image;

    //On récupère les titres
    for ( int i = 0; i < ui->Titres->count(); i++ )
    {
        TitresPhys titre;
        titre.Titre = ui->Titres->item( i )->text();
        titre.Duree = ui->Duree->item( i )->text();
        titre.Num_Piste = i + 1;

        if ( m_album.Type == 2 )
        {
            //A faire l'edition de compilation
        }

        m_album.titres << titre;
    }

}
void ModifierAlbumDialog::Supprimer_Titre()
{
    QList<QListWidgetItem *> fileSelected = ui->Titres->selectedItems();
    if ( fileSelected.size() )
    {
        for ( int i = ui->Titres->count() - 1 ; i >= 0 ; i-- )
        {
            if ( ui->Titres->item( i )->isSelected() )
            {
                QListWidgetItem * item = ui->Titres->takeItem( i );
                ui->Titres->removeItemWidget( item );
            }
        }
    }
    ListeNumeros();
}

void ModifierAlbumDialog::on_buttonBox_accepted()
{

    EnregistrerAlbum();

    BDDGestionPhys m_bddinterface;
    m_bddinterface.SupprimerenBDDPhys( m_album.Id_Album );
    m_bddinterface.ajouterAlbum( m_album.Poch, m_album.Album, m_album.Artiste, QString::number( m_album.Id_Release ), m_album.Annee, m_album.titres, m_album.Type );

}
