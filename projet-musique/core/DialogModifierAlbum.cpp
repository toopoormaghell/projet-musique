#include "DialogModifierAlbum.h"
#include "ui_DialogModifierAlbum.h"
#include "util.h"
#include <QListWidgetItem>
#include "bddgestionphys.h"
#include "bddafficherphys.h"
#include "bddalbum.h"
#include "bddtype.h"
#include "dialogchoixpochette.h"
#include "bddpoch.h"
#include <QAbstractButton>
#include "bddphys.h"
#include "bddtype.h"
#include "bddsupport.h"


DialogModifierAlbum::DialogModifierAlbum( int selection, QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::DialogModifierAlbum ),
    m_selection( selection )
{
    ui->setupUi( this );
    RecupererListeType();
    //On récupère l'album à afficher
    m_album = BDDAlbum::RecupAlbumEntite( m_selection );
    AfficherAlbum();
}

DialogModifierAlbum::~DialogModifierAlbum()
{
    delete ui;
}

void DialogModifierAlbum::AfficherAlbum()
{

    //On met le nom, l'artiste, l'année
    ui->Album->setText( m_album.Album );
    ui->Annee->setText( QString::number( m_album.Annee ) );
    ui->Artiste->setText( m_album.Artiste );

    //On affiche la pochette
    QPixmap scaled( QPixmap::fromImage( m_album.Poch ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );

    //On affiche le type de l'album
    ui->Type->setCurrentText( BDDType::RecupererType( m_album.Type )->m_type );

    //On affiche les supports de l'album
    int SupportPhys = BDDSupport::RecupererSupportAlb ( m_album.Id_Album, "Phys" );
    int SupportMp3 = BDDSupport::RecupererSupportAlb ( m_album.Id_Album,"MP3" );

    if ( SupportMp3 == -1 )
    {
        ui->SupportMP3->setVisible( false );
        ui->LabelSupMp3->setVisible( false );
    } else
    {
        ui->SupportMP3->addItem( BDDSupport::RecupererSupport( SupportMp3 ) ->m_support );
    }

    if ( SupportPhys == -1 )
    {
        ui->SupportPhys->setVisible( false );
        ui->LabelSupPhys->setVisible( false );
    } else
    {

        ui->SupportPhys->setCurrentText( BDDSupport::RecupererSupport( SupportPhys ) ->m_support );
    }

    if ( SupportPhys == 2 )
    {
        ui->ArtistesTitres->setVisible( true );
    } else
    {
        ui->ArtistesTitres->setVisible( false );
    }
    //On affiche les titres
    ui->Titres->clear();
    ui->Duree->clear();
    ui->ArtistesTitres->clear();
    for ( int comp = 0; comp < m_album.titres.count(); comp++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( m_album.titres[comp].Titre );
        item->setFlags( item->flags() | Qt::ItemIsEditable );
        item->setData( Qt::UserRole, m_album.titres[comp].MP3  );
        ui->Titres->addItem( item );
        ui->Duree->addItem( m_album.titres[comp].Duree );

        if ( SupportPhys == 2 )
        {
            QListWidgetItem* art = new QListWidgetItem;
            art->setText( m_album.titres[comp].Artiste );
            art->setFlags( item->flags() | Qt::ItemIsEditable );

            ui->ArtistesTitres->addItem( art );
        }
    }
    ListeNumeros();
    //On va chercher les commentaires sur l'album physique
    BDDPhys* phys = BDDPhys::RecupererPhys( m_album.Id_Album );
    ui->Commentaires->setText( phys->m_commentaires );
    delete phys;
}
void DialogModifierAlbum::ListeNumeros()
{
    ui->Num_Pistes->clear();
    for ( int i = 1; i < ui->Titres->count() + 1; i++ )
    {
        ui->Num_Pistes->addItem( new QListWidgetItem( QString::number( i ).rightJustified( 2, '0' ) + " - " ) );
    }
}
void DialogModifierAlbum::RecupererListeType()
{
    QList<int> types = BDDType::NbCategories();

    for (int i = 0; i < types.count() ; i++)
    {
        BDDType* temp = BDDType::RecupererType( types[i] );

        ui->Type->addItem( temp->m_type,QVariant( types[i] ) );
    }
}

void DialogModifierAlbum::EnregistrerAlbum()
{

    m_album.Album = ui->Album->text();

    m_album.Artiste = ui->Artiste->text();
    m_album.Annee = ui->Annee->text().toInt();
    m_album.Type = ui->Type->currentIndex() + 1;

    m_album.titres.clear();
    //On récupère les titres
    for ( int i = 0; i < ui->Titres->count(); i++ )
    {
        TitresPhys titre;
        titre.Titre = ui->Titres->item( i )->text();
        titre.Duree = ui->Duree->item( i )->text();
        titre.Num_Piste = i + 1;
        titre.MP3 = ui->Titres->item (i )->data( Qt::UserRole).toBool() ;
        if ( m_album.Type == 2 )
        {
            //A faire l'edition de compilation
        }

        m_album.titres << titre;
    }

}
void DialogModifierAlbum::Supprimer_Titre()
{
    QList<QListWidgetItem*> fileSelected = ui->Titres->selectedItems();
    if ( fileSelected.size() )
    {
        for ( int i = ui->Titres->count() - 1 ; i >= 0 ; i-- )
        {
            if ( ui->Titres->item( i )->isSelected() )
            {
                QListWidgetItem* item = ui->Titres->takeItem( i );
                ui->Titres->removeItemWidget( item );
                ui->Duree->takeItem( i);
                ui->Duree->removeItemWidget( item );
            }
        }
    }
    ListeNumeros();
}

void DialogModifierAlbum::on_buttonBox_accepted()
{
    EnregistrerAlbum();
    BDDGestionPhys m_bddinterface;

    m_bddinterface.modifierAlbum(  m_album.Album, m_album.Artiste, QString::number( m_album.Id_Release ), m_album.Annee, m_album.titres, m_album.Type, m_album.Id_Poch, m_album.Id_Album, ui->Commentaires->text(), m_album.Support );


    this->close();

}

void DialogModifierAlbum::on_Parcourir_clicked()
{
    DialogChoixPochette dial(m_album.Artiste);
    dial.exec();
    if ( dial.m_selection != -1 )
    {
        BDDPoch* pochtemp = BDDPoch::recupererBDD(dial.m_selection);
        m_album.Poch = pochtemp->m_image;
        m_album.Id_Poch = pochtemp->id();
        delete pochtemp;
    }
    AfficherAlbum();
}

void DialogModifierAlbum::on_Supprimer_clicked()
{
    Supprimer_Titre();
}
