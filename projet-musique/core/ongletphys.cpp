#include "ongletphys.h"
#include "ui_ongletphys.h"
#include "bddafficherphys.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddphys.h"
#include "DialogModifierAlbum.h"
#include "bddgestionphys.h"
#include "DialogModifierArtiste.h"
#include <QDebug>
#include "bddrelation.h"


OngletPhys::OngletPhys( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::OngletPhys )

{
    m_selection = 0;
    ui->setupUi( this );

    vider( "Artiste" );
    actualiserOnglet();

    //Connexion entre les différents listwidget et le signal "Entrée"
    connect (ui->Albums,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(on_Albums_itemPressed(QListWidgetItem*)));
    connect (ui->Artistes,SIGNAL(activated(QModelIndex)),this,SLOT(on_Artistes_clicked(QModelIndex)));
    connect (ui->Compil,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(on_Compil_itemPressed(QListWidgetItem*)));
    connect (ui->Singles,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(on_Singles_itemPressed(QListWidgetItem*)));
    // connect (ui->Modifier,SIGNAL(pressed()),this,SLOT(on_Modifier_clicked()));
    //    connect (ui->SupprimerAlbum,SIGNAL(pressed()),this,SLOT(on_SupprimerAlbum_clicked()));
}

OngletPhys::~OngletPhys()
{
    delete ui;
}
void OngletPhys::actualiserOnglet()
{
    afficherListeArtiste();
    afficherListeCds();
    AfficherInfosAlbum( 1 );

}

void OngletPhys::afficherListeArtiste()
{
    vider("Artiste");

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
        delete artiste;
    }
    if (ui->Artistes->count() > 0)
    {
        ui->Artistes->setCurrentRow( 1 );
    } else
    {
        ui->Artistes->setCurrentRow( 0 );
    }
    m_artiste = ui->Artistes->currentIndex().data(Qt::UserRole).toString();
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
    m_selection = ui->Albums->currentIndex().data( Qt::UserRole ).toInt();

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
    vider("Infos");

    BDDPhys* phys = BDDPhys::RecupererPhys( m_selection );
    int nbtitresmp3 = 0;
    if ( m_selection != 0  )
    {
        //On affiche l'année et le nom de l'album
        ui->Annee->setText( QString::number( phys->m_album->m_annee ) );
        ui->NomAlbum->setText( phys->m_album->m_nom );

        //On affiche la pochette
        QPixmap scaled( QPixmap::fromImage( phys->m_album->m_pochette->m_image ) );
        scaled = scaled.scaled( 150, 150 );
        ui->Pochette->setPixmap( scaled );

        QPixmap mp3( ":/Autres/Mp3" );
        QPixmap nonmp3 (":/Autres/Faux");
        //On affiche les titres
        for ( int i = 0; i < phys->m_relations.count(); i++ )
        {
            BDDTitre* titre = BDDTitre::RecupererTitre( phys->m_relations[i]->m_titre->m_id );
            QListWidgetItem* item = new QListWidgetItem;

            QString temp;
            temp = QString::number( phys->m_relations[i]->m_num_piste ).rightJustified( 2, '0' ) + " - " + titre->m_nom + "(" + phys->m_relations[i]->m_duree + ")";
            //Si c'est une compil, on ajoute les artistes derrière
            if ( Type == 3 )
            {
                BDDArtiste* art = BDDArtiste::RecupererArtiste( phys->m_relations[i]->m_artiste->m_id );
                if ( m_artiste.toInt() == art->m_id )
                {
                    //On Ajoute une couleur pour le titre où l'artiste est le bon
                    QBrush m_brush;
                    m_brush.setColor( Qt::blue );
                     item->setForeground( m_brush );

                }
                temp = temp + " - " + art->m_nom;
                delete art;
            }
            item->setText( temp );
            //On affiche l'icone si le mp3 existe aussi
            if ( phys->m_relations[i]->m_mp3  )
            {
                nbtitresmp3++;
                item->setIcon( QIcon( mp3 ) );
            } else
            {
                item->setIcon( QIcon ( nonmp3 ) );
            }
            ui->Titres->addItem( item );
            delete titre;

        }
        ui->NbTitresAlb->setText(QString::number( phys->m_relations.count() ) );
        ui->NbTitresMP3Alb->setText(QString::number( nbtitresmp3 ));
        if ( phys->m_relations.count()!=0)
            ui->PourcentageAlb->setText( QString::number( nbtitresmp3*100/phys->m_relations.count() ) +" %" );
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
    DialogModifierAlbum modif( m_selection, this );
    modif.exec();
}
void OngletPhys::on_SupprimerAlbum_clicked()
{
    BDDGestionPhys temp;
    temp.SupprimerenBDDPhys( m_selection );

    actualiserOnglet();
}

void OngletPhys::on_Artistes_doubleClicked( const QModelIndex& index )
{

    int choix = index.data( Qt::UserRole ).toInt();
    BDDArtiste* artiste = BDDArtiste::RecupererArtiste( choix );
    DialogModifierArtiste temp( artiste, this );
    temp.exec();
    vider( "Artiste" );
    afficherListeArtiste();
    delete artiste;
}
void OngletPhys::afficherListeCds()
{
    afficherListeAlbum();
    afficherListeSingles();
    AfficherArtisteSelectionne();
    afficherListeCompils();
    remplirStats();

    //Si on est sur "l'artiste" Compil
    if ( m_artiste == "-1" )
    {
        ui->Singles->setHidden( true );
        ui->label_2->setHidden( true );
        ui->Albums->setHidden( true );
        ui->label->setHidden( true );
        ui->Compil->setFixedHeight( 450);
        ui->label_3->setFixedHeight( 450);
        ui->Compil->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

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
        ui->Compil->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


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

void OngletPhys::on_Artistes_clicked( const QModelIndex& index )
{
    m_artiste = index.data( Qt::UserRole ).toString();
    afficherListeCds();
}
void OngletPhys::remplirStats()
{
    ui->NbAlb->setText( QString::number( m_Albums ) );
    ui->NbCompil->setText( QString::number( m_Compils ) );
    ui->NbSingle->setText( QString::number( m_Singles ) );
    ui->NbCD->setText( QString::number( m_Albums + m_Compils + m_Singles ));

    QList <int> titres = m_bddInterface.TitresParArtistes( m_artiste );
    ui->NbTitres->setText( QString::number( titres[0] ) );
    ui->NbTitresMP3->setText( QString::number( titres[1] ) );
    int Pourcentage = titres[1]*100/titres[0];
    ui->Pourcentage->setText(QString::number( Pourcentage )+" %");

    afficherListeAlbSansMP3();

}
void OngletPhys::afficherListeAlbSansMP3()
{
    ui->AlbSansMP3->clear();

    //Affichage des albums
    QList<int> albums = m_bddInterface.AlbSansMP3( m_artiste );

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

            ui->AlbSansMP3->addItem( item );

        }
        delete album;
    }

}
