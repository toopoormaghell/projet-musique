#include "ongletphys.h"
#include "ui_ongletphys.h"
#include "bddafficherphys.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddphys.h"
#include "modifieralbumdialog.h"
#include "bddgestionphys.h"
#include "modificationartistedialog.h"
#include <QDebug>

OngletPhys::OngletPhys( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::OngletPhys )

{
    m_selection = 0;
    ui->setupUi( this );

    vider( "Artiste" );
    afficherListeArtiste();
}

OngletPhys::~OngletPhys()
{
    delete ui;
}
void OngletPhys::afficherListeArtiste()
{
    //Affichage des artistes
    QList<int> artistes = m_bddInterface.ListeArtiste();

    //Ajout de l'artiste " Compils"
    QListWidgetItem* item = new QListWidgetItem;
    QImage image( "./Pochettes/def.jpg" );
    QPixmap scaled( QPixmap::fromImage( image ) );
    scaled = scaled.scaled( 150, 150 );
    item->setIcon( QIcon( scaled ) );
    item->setData( Qt::UserRole, -1 );
    item->setText( "Compils" );
    ui->Artistes->addItem( item );

    for ( int cpt = 0; cpt < artistes.count(); cpt++ )
    {
        BDDArtiste* artiste = BDDArtiste::RecupererArtiste( artistes[cpt] );

        if ( artiste->m_id > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( artiste->m_pochette->m_image ) );
            scaled = scaled.scaled( 150, 150 );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'artiste
            item->setData( Qt::UserRole, artistes[cpt] );
            item->setText( artiste->m_nom );
            ui->Artistes->addItem( item );
        }
        artiste->deleteArtiste();
    }
    ui->Artistes->setCurrentRow( 1 );
}
void OngletPhys::afficherListeAlbum()
{
    ui->Albums->clear();

    //Affichage des albums
    QList<int> albums = m_bddInterface.listeAlbums( m_artiste );
    m_Albums = 0;
    m_Albums = albums.count();

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {

        BDDAlbum* album = BDDAlbum::RecupererAlbum( albums[cpt] );

        if ( album->m_id > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, albums[cpt] );
            item->setText( QString::number( album->m_annee ) + " - " + album->m_nom );

            ui->Albums->addItem( item );
        }
        delete album;
    }
    ui->Albums->setCurrentRow( 0 );

}
void OngletPhys::afficherListeSingles()
{
    ui->Singles->clear();

    //Affichage des albums
    QList<int> singles = m_bddInterface.listeSingles( m_artiste );
    m_Singles = 0;
    m_Singles = singles.count();

    for ( int cpt = 0; cpt < singles.count(); cpt++ )
    {

        BDDAlbum* album = BDDAlbum::RecupererAlbum( singles[cpt] );

        if ( album->m_id > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, singles[cpt] );
            item->setText( QString::number( album->m_annee ) + " - " + album->m_nom );

            ui->Singles->addItem( item );
        }
        delete album;
    }

}
void OngletPhys::AfficherArtisteSelectionne()
{
    if ( m_artiste == "-1" )
    {
        ui->Artiste->setText( "Compils" );
    }
    else
    {
        BDDArtiste* artiste = BDDArtiste::RecupererArtiste( m_artiste.toInt() );
        ui->Artiste->setText( artiste->m_nom );
        delete artiste;
    }

}

void OngletPhys::afficherListeCompils()
{
    ui->Compil->clear();

    //Affichage des albums
    QList<int> albums = m_bddInterface.listeCompils( m_artiste );
    m_Compils = 0;
    m_Compils = albums.count();

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {

        BDDAlbum* album = BDDAlbum::RecupererAlbum( albums[cpt] );

        if ( album->m_id > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );

            item->setIcon( QIcon( scaled ) );


            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, albums[cpt] );
            item->setText( QString::number( album->m_annee ) + " - " + album->m_nom );

            ui->Compil->addItem( item );

        }
        delete album;
    }

}
void OngletPhys::AfficherInfosAlbum( int Type )
{
    BDDPhys* phys = BDDPhys::RecupererPhys( m_selection );

    //On affiche l'année et le nom de l'album
    ui->Annee->setText( QString::number( phys->m_album->m_annee ) );
    ui->NomAlbum->setText( phys->m_album->m_nom );

    //On affiche la pochette
    QPixmap scaled( QPixmap::fromImage( phys->m_album->m_pochette->m_image ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );

    QPixmap mp3physoui( ":/Autres/Vrai" );
    QPixmap mp3physnon( ":/Autres/Faux" );
    //On affiche les titres
    for ( int i = 0; i < phys->m_titres.count(); i++ )
    {
        QListWidgetItem* item = new QListWidgetItem;

        QString temp;
        temp = QString::number( phys->m_titres[i]->m_num_piste ).rightJustified( 2, '0' ) + " - " + phys->m_titres[i]->m_nom + "(" + phys->m_titres[i]->m_duree + ")";
        //Si c'est une compil, on ajoute les artistes derrière
        if ( Type == 3 )
        {
            if ( m_artiste.toInt() == phys->m_titres[i]->m_artiste->m_id )
            {
                //On Ajoute une couleur pour le titre où l'artiste est le bon
                QBrush m_brush;
                m_brush.setColor( Qt::blue );
                item->setForeground( m_brush );
            }
            temp = temp + " - " + phys->m_titres[i]->m_artiste->m_nom;
        }
        item->setText( temp );
        //On affiche l'icone si le mp3 existe aussi
        if ( phys->m_titres[i]->m_mp3 && phys->m_titres[i]->m_phys )
        {
            item->setIcon( QIcon( mp3physoui ) );
        }
        else
        {
            item->setIcon( QIcon( mp3physnon ) );
        }

        ui->Titres->addItem( item );

    }

    delete phys;
}

void OngletPhys::vider( QString type )
{
    if ( type == "Artiste" )
    {
        ui->Artistes->clear();
    }

    if ( type == "Albums" )
    {
        ui->Albums->clear();

    }
    if ( type == "Infos" )
    {
        ui->Annee->clear();
        ui->Artiste->clear();
        ui->NomAlbum->clear();
        ui->Pochette->clear();
        ui->Titres->clear();
    }
}
void OngletPhys::on_Albums_itemPressed( QListWidgetItem* item )
{
    m_selection = item->data( Qt::UserRole ).toInt();
    ui->Compil->clearSelection();
    ui->Singles->clearSelection();
    vider( "Infos" );
    AfficherInfosAlbum( 1 );
    AfficherArtisteSelectionne();
}

void OngletPhys::on_Compil_itemPressed( QListWidgetItem* item )
{
    m_selection = item->data( Qt::UserRole ).toInt();
    ui->Albums->clearSelection();
    ui->Singles->clearSelection();
    vider( "Infos" );
    AfficherInfosAlbum( 3 );
    AfficherArtisteSelectionne();
}

void OngletPhys::on_Singles_itemPressed( QListWidgetItem* item )
{
    m_selection = item->data( Qt::UserRole ).toInt();
    ui->Albums->clearSelection();
    ui->Compil->clearSelection();
    vider( "Infos" );
    AfficherInfosAlbum( 2 );
    AfficherArtisteSelectionne();
}

void OngletPhys::on_Modifier_clicked()
{
    ModifierAlbumDialog modif( m_selection, this );
    modif.exec();
}
void OngletPhys::on_SupprimerAlbum_clicked()
{
    BDDGestionPhys temp;
    temp.SupprimerenBDDPhys( m_selection );
}

void OngletPhys::on_Artistes_doubleClicked( const QModelIndex& index )
{

    int choix = index.data( Qt::UserRole ).toInt();
    BDDArtiste* artiste = BDDArtiste::RecupererArtiste( choix );
    ModificationArtisteDialog temp( artiste, this );
    temp.exec();
    vider( "Artiste" );
    afficherListeArtiste();
}

void OngletPhys::on_Artistes_clicked( const QModelIndex& index )
{
    m_artiste = index.data( Qt::UserRole ).toString();
    afficherListeAlbum();
    afficherListeSingles();
    AfficherArtisteSelectionne();
    afficherListeCompils();

    //Si on est sur "l'artiste" Compil
    if ( m_artiste == "-1" )
    {
        ui->Singles->setHidden( true );
        ui->label_2->setHidden( true );
        ui->Albums->setHidden( true );
        ui->label->setHidden( true );
        ui->Compil->setFixedHeight( 450 );
        ui->label_3->setFixedHeight( 450 );
    }
    //Sinon, on vérifie le nombre d'albums pour en afficher le plus possible
    else
    {

        ui->Singles->setHidden( false );
        ui->label_2->setHidden( false );
        ui->Albums->setHidden( false );
        ui->label->setHidden( false );
        ui->Compil->setHidden( false );
        ui->label_3->setHidden( false );
        ui->Compil->setFixedHeight( 150 );
        ui->label_3->setFixedHeight( 150 );
        ui->Albums->setFixedHeight( 150 );
        ui->label->setFixedHeight( 150 );

        if ( ( m_Singles == 0 || m_Compils == 0 ) && m_Albums > 12 )

        {
            int RubriquesCachees = 0;

            if ( m_Singles == 0 )
            {
                ui->Singles->setHidden( true );
                ui->label_2->setHidden( true );
                RubriquesCachees ++;
            }
            else
            {
                ui->label_2->setHidden( false );
                ui->Singles->setHidden( false );
            }

            if ( m_Compils == 0 )
            {
                ui->Compil->setHidden( true );
                ui->label_3->setHidden( true );
                RubriquesCachees ++;
            }
            else
            {
                ui->label_3->setHidden( false );
                ui->Compil->setHidden( false );
            }
            ui->Albums->setFixedHeight( 150 * ( RubriquesCachees + 1 ) );
            ui->label->setFixedHeight( 150 * ( RubriquesCachees + 1 ) );
        }
    }
}
