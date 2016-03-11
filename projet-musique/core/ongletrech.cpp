#include "ongletrech.h"
#include "ui_ongletrech.h"
#include "bddrech.h"
#include "bddtitre.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddpoch.h"
#include <QDebug>
#include "bddmp3.h"

OngletRech::OngletRech( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::OngletRech )
{
    ui->setupUi( this );
    m_rech = "";
    AffichageResGroup( 0);
}

OngletRech::~OngletRech()
{
    delete ui;
}

void OngletRech::on_pushButton_clicked()
{
    m_rech = ui->Rech->text();
    affichageResultats();
}
void OngletRech::affichageResultats()
{
    affichageTitres();
    affichageAlbums();
    affichageArtistes();
}
void OngletRech::affichageTitres()
{
    //On s'occupe d'afficher les titres
    ui->TitResult->clear();
    QList<int> result = appelBDD->RechTitres( m_rech );

    for ( int i = 0; i < result.count(); i++ )
    {
        BDDTitre* titre = BDDTitre::RecupererTitre( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( titre->m_nom );
        item->setData( Qt::UserRole, titre->m_id );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( titre->m_album->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->TitResult->addItem( item );
    }
}
void OngletRech::affichageAlbums()
{
    //On s'occupe d'afficher les albums
    ui->AlbResult->clear();
    QList<int> result = appelBDD->RechAlb( m_rech );

    for ( int i = 0; i < result.count(); i++ )
    {
        BDDAlbum* alb = BDDAlbum::RecupererAlbum( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->m_nom );
        item->setData( Qt::UserRole, alb->m_id );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->AlbResult->addItem( item );
    }

}
void OngletRech::affichageArtistes()
{
    //On s'occupe d'afficher les artistes
    ui->ArtResult->clear();
    QList<int> result = appelBDD->RechArt( m_rech );

    for ( int i = 0; i < result.count(); i++ )
    {
        BDDArtiste* artiste = BDDArtiste::RecupererArtiste( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( artiste->m_nom );
        item->setData( Qt::UserRole, artiste->m_id );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( artiste->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->ArtResult->addItem( item );
    }
}
void OngletRech::on_ArtResult_clicked( const QModelIndex& index )
{
    AffichageResGroup( 0 );
    m_artiste =  index.data( Qt::UserRole ).toString();
    affichageResultatspourArtiste();
}
void OngletRech::on_AlbResult_clicked(const QModelIndex &index)
{
    AffichageResGroup( 1 );
    m_album =  index.data( Qt::UserRole ).toString();
    affichageTitresParAlbum();
}
void OngletRech::on_TitResult_clicked( const QModelIndex& index )
{
    AffichageResGroup( 2 );
    m_titre =  index.data( Qt::UserRole ).toString();
    AffichInfosTitres();
}

void OngletRech::AffichageResGroup( int Type )
{
    ui->ResSimi->setVisible( false );
    switch (Type)
    {
    case 0:
        ui->ResAlb->setVisible( true );
        ui->ResArt->setVisible( true );
        ui->ResTitre->setVisible( true );
        ui->AlbResult->clearSelection();
        ui->TitResult->clearSelection();
        break;
    case 1 :
        ui->ResAlb->setVisible( true );
        ui->ResArt->setVisible( false );
        ui->ResTitre->setVisible( true );
        ui->AlbResult->clearSelection();
        ui->ArtResult->clearSelection();
        break;
    case 2:
        ui->ResAlb->setVisible( false );
        ui->ResArt->setVisible( false );
        ui->ResTitre->setVisible( true );
        ui->TitResult->clearSelection();
        ui->ArtResult->clearSelection();
        break;
    }
}

void OngletRech::affichageResultatspourArtiste()
{
    ui->AlbumspourArt->clear();

    //On s'occupe d'afficher les albums
    QList<int> result= appelBDD->AlbumsPourArt( m_artiste );
    for ( int i = 0; i < result.count(); i++ )
    {
        BDDAlbum* alb = BDDAlbum::RecupererAlbum( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->m_nom );
        item->setData( Qt::UserRole, alb->m_id );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->AlbumspourArt->addItem( item );
    }
}
void OngletRech::affichageTitresParAlbum()
{
    //On s'occupe d'afficher les titres
    ui->TitresResultats->clear();
    QList<int>  result = appelBDD->TitresPourAlb( m_album );

    QPixmap mp3( ":/Autres/Mp3" );
    QPixmap phys( ":/Autres/Phys" );

    for ( int i = 0; i < result.count(); i++ )
    {
        BDDTitre* titre = BDDTitre::RecupererTitre( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( titre->m_nom );
        item->setData( Qt::UserRole, titre->m_id );
        //On s'occupe d'afficher si c'est le titre existe en MP3 et Phys
        if ( titre->m_mp3 )
        {
            item->setIcon( QIcon( mp3 ) );
        }
        if ( titre->m_phys)
        {
            item->setIcon( QIcon( phys ) );
        }
        ui->TitresResultats->addItem( item );
    }
}


void OngletRech::on_AlbumspourArt_clicked(const QModelIndex &index)
{
    m_album =  index.data( Qt::UserRole ).toString();
    affichageTitresParAlbum();
}

void OngletRech::on_TitresResultats_clicked(const QModelIndex &index)
{
    m_titre =  index.data( Qt::UserRole ).toString();
    AffichInfosTitres();
}
void OngletRech::AffichInfosTitres()
{
    BDDTitre* titre = BDDTitre::RecupererTitre(m_titre.toInt());
    m_album = appelBDD->AlbPourTitre( m_titre);
    AlbumPhys alb = BDDAlbum::RecupAlbumEntite( m_album.toInt());
    BDDArtiste* art = BDDArtiste::RecupererArtparNom( alb.Artiste );
    m_artiste = QString::number(art->m_id);

    //On affiche la pochette
    QPixmap scaled ( QPixmap::fromImage( alb.Poch ) );
    scaled = scaled.scaled( 150, 150 );
    ui->PochTitre->setPixmap( scaled );

    //On affiche le nom du titre
    ui->NomTitre->setText(QString::number( titre->m_num_piste ).rightJustified( 2, '0' ) + " - " + titre->m_nom );
    //On affiche le nom de l'album
    ui->NomAlbum->setText(alb.Album+"("+QString::number ( alb.Annee ) +")");
    //On affiche le nom de l'artiste
    ui->NomArtiste->setText(alb.Artiste);
    //On affiche la durée
    ui->Duree->setText(titre->m_duree);

    //On ajoute un bouton ou non
    if ( titre->m_mp3 )
    {
        ui->OuvrirDossier->setVisible( true);
    } else
    {
        ui->OuvrirDossier->setVisible( false );
    }
}

void OngletRech::on_voirAlbum_clicked()
{
    AffichageResGroup( 1 );
    affichageTitresParAlbum();
}

void OngletRech::on_VoirArtiste_clicked()
{
    AffichageResGroup( 0 );
    affichageResultatspourArtiste();
}

void OngletRech::on_Similaires_clicked()
{
    ui->ResSimi->setVisible( true );
    ui->ListeSimilaires->clear();
    BDDTitre* titre = BDDTitre::RecupererTitre( m_titre.toInt() );
    QList<int> Simi = titre->Similaires( m_titre.toInt() );
    //On affiche chaque titre similaire
    for ( int i = 0; i < Simi.count(); i++ )
    {
        //On récupère les infos du titre similaire
        BDDMp3* mp3 = BDDMp3::RecupererMp3( Simi[i] );

        //On affiche les infos du titre dans un item
        QListWidgetItem* item = new QListWidgetItem;
        item->setData( Qt::UserRole, mp3->m_id );
        item->setText( QString::number( mp3->m_album->m_annee ) + " - " + mp3->m_titre->m_nom );
        item->setToolTip( mp3->m_titre->m_nom );
        item->setFlags( Qt::ItemIsEnabled );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( mp3->m_album->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );

        ui->ListeSimilaires->addItem( item );

        delete mp3;
    }

}

void OngletRech::on_OuvrirDossier_clicked()
{

}
