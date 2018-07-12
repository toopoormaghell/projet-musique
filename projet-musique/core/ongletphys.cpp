#include "ongletphys.h"
#include "ui_ongletphys.h"

#include "bddafficherphys.h"
#include "meta_album.h"
#include "meta_titre.h"
#include "meta_artiste.h"

#include "DialogModifierAlbum.h"
#include "DialogModifierArtiste.h"


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
    connect (ui->Modifier,SIGNAL(pressed()),this,SLOT(on_Modifier_clicked()));
    //    connect (ui->SupprimerAlbum,SIGNAL(pressed()),this,SLOT(on_SupprimerAlbum_clicked()));
}

OngletPhys::~OngletPhys()
{
    delete ui;
}
void OngletPhys::actualiserOnglet()
{

    AfficherCategories();
    afficherListeCds();
    AfficherInfosAlbum( m_categorie );
}

void OngletPhys::AfficherCategories()
{
    ui->Categories->clear();
    QStringList types;

    types << m_bddInterface.RecupererListeTypes();

    QImage image( "./Pochettes/def.jpg" );

    for ( int cpt = 0; cpt < types.count(); cpt = cpt + 2 )
    {
        QPixmap scaled( QPixmap::fromImage( image ) );
        scaled = scaled.scaled( 150, 150 );
        QListWidgetItem* item = new QListWidgetItem;
        item->setIcon( QIcon( scaled ) );
        item->setData( Qt::UserRole, types[cpt + 1] );
        item->setText( types[cpt] );

        ui->Categories->addItem( item );
    }
    ui->Categories->setCurrentRow( 1 );
    m_categorie = 1;

    afficherListeArtiste();

}

void OngletPhys::afficherListeArtiste()
{
    vider("Artiste");

    //Affichage des artistes
    QList<int> artistes = m_bddInterface.ListeArtiste( m_categorie );

    for ( int cpt = 0; cpt < artistes.count(); cpt++ )
    {

        Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( artistes[cpt] );

        if ( artiste->get_id_artiste() > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( artiste->getPoch() ) );
            scaled = scaled.scaled( 150, 150 );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'artiste
            item->setData( Qt::UserRole, artiste->get_id_artiste() );
            item->setText( artiste->getNom_Artiste() );
            ui->Artistes->addItem( item );
        }
        delete artiste;
    }

    ui->Artistes->setCurrentRow( 0 );

    m_artiste = ui->Artistes->currentIndex().data( Qt::UserRole ).toString();

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

        Meta_Album* album = Meta_Album::RecupererBDD( albums[cpt] );

        if ( album->getid_alb() > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, album->getid_alb() );
            item->setText( QString::number( album->getannee() ) + " - " + album->getnom_album() );

            ui->Albums->addItem( item );
        }
        delete album;
    }
    ui->Albums->setCurrentRow( 0, QItemSelectionModel::Select );
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

        Meta_Album* album = Meta_Album::RecupererBDD( singles[cpt] );

        if ( album->getid_alb() > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, album->getid_alb() );
            item->setText( QString::number( album->getannee() ) + " - " + album->getnom_album() );

            ui->Singles->addItem( item );
        }

        delete album;
    }

}
void OngletPhys::AfficherArtisteSelectionne()
{
    switch ( m_categorie )
    {
    case ( 2 ) : ui->Artiste->setText( "Compils" ); break;
    case ( 4 ) : ui->Artiste->setText( "BOF" ); break;
    case ( 5 ) : ui->Artiste->setText( "Spectacle Musical" ); break;
    case ( 6 ) : ui->Artiste->setText( "Télé-Réalités" ); break;
    case ( 7 ) : ui->Artiste->setText( "New-Age" ); break;
    case ( 8 ) : ui->Artiste->setText( "Classique" ); break;
    case ( 9 ) : ui->Artiste->setText( "Associatif" ); break;
    case ( 10 ) : ui->Artiste->setText( "Reprises" ); break;
    default :  Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( m_artiste.toInt() ); ui->Artiste->setText( artiste->getNom_Artiste() ); delete artiste;
    }

}

void OngletPhys::afficherListeCompils()
{
    ui->Compil->clear();

    //Affichage des albums
    QList<int> albums = m_bddInterface.listeCompils( m_artiste, m_categorie );
    m_Compils = 0;
    m_Compils = albums.count();

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {
        Meta_Album* album = Meta_Album::RecupererBDD( albums[cpt] );

        if ( album->getid_alb() > 0 )
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, album->getid_alb() );
            item->setText( QString::number( album->getannee() ) + " - " + album->getnom_album() );

            ui->Compil->addItem( item );
        }

        delete album;
    }

}
void OngletPhys::AfficherInfosAlbum( int Type )
{
    vider("Infos");
    Meta_Album* phys = Meta_Album::RecupererBDD( m_selection );

    int nbtitresmp3 = 0;
    if ( m_selection != 0  )
    {
        //On affiche l'année et le nom de l'album
        ui->Annee->setText( QString::number( phys->getannee() ) );
        ui->NomAlbum->setText( phys->getnom_album() );

        //On affiche la pochette
        QPixmap scaled( QPixmap::fromImage( phys->getPoch() ) );
        scaled = scaled.scaled( 150, 150 );
        ui->Pochette->setPixmap( scaled );

        QPixmap mp3( ":/Autres/Vrai" );
        QPixmap nonmp3 (":/Autres/Faux");


        for ( int i = 0; i < phys->gettitres().count(); i++ )
        {
            Meta_Titre* titre = phys->gettitres()[i];

            QListWidgetItem* item = new QListWidgetItem;

            QString temp;
            temp = QString::number( titre->getnum_piste() ).rightJustified( 2, '0' ) + " - " + titre->getnom_titre() + "(" + titre->getduree() + ")";

            //Si c'est une compil, on ajoute le nom de l'artiste
            if (Type == 3 )
            {
                if ( m_artiste.toInt() == titre->getid_art() )
                {
                    QFont m_police( "Monotype Corsiva", 11, 75 );
                    item->setTextColor( Qt::blue );
                    item->setFont( m_police );
                }

                temp = temp + " - " + titre->getnom_artiste();

            }
            item->setText( temp );
            if ( titre->getsupportmp3() != "Aucun" )
            {
                nbtitresmp3++;
                item->setIcon( QIcon( mp3 ) );
            } else
            {
                item->setIcon( QIcon ( nonmp3 ) );
            }

            ui->Titres->addItem( item );

        }

        ui->NbTitresAlb->setText(QString::number( phys->gettitres().count() ) );
        ui->NbTitresMP3Alb->setText(QString::number( nbtitresmp3 ));
        if ( phys->gettitres().count() !=0 )
            ui->PourcentageAlb->setText( QString::number( nbtitresmp3*100/phys->gettitres().count() ) +" %" );

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
    Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( choix );
    DialogModifierArtiste temp( artiste, this );
    temp.exec();
    delete artiste;
    actualiserOnglet();

}
void OngletPhys::afficherListeCds()
{

    afficherListeAlbum();
    afficherListeSingles();
    AfficherArtisteSelectionne();
    afficherListeCompils();
    remplirStats();

    //Si on est sur le type Compil
    if ( m_categorie == 2 )
    {
        ui->Singles->setHidden( true );
        ui->label_2->setHidden( true );
        ui->Albums->setHidden( true );
        ui->label->setHidden( true );
        ui->Compil->setFixedHeight( 450);
        ui->label_3->setFixedHeight( 450);


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

void OngletPhys::on_Artistes_clicked( const QModelIndex& index )
{
    Q_UNUSED ( index );
    m_artiste = ui->Artistes->currentIndex().data( Qt::UserRole ).toString();
    afficherListeCds();
}

void OngletPhys::remplirStats()
{
    ui->NbAlb->setText( QString::number( m_Albums ) );
    ui->NbCompil->setText( QString::number( m_Compils ) );
    ui->NbSingle->setText( QString::number( m_Singles ) );
    ui->NbCD->setText( QString::number( m_Albums + m_Compils + m_Singles ));

    QList <int> titres = m_bddInterface.TitresParArtistes( m_artiste );
    int Pourcentage = 0;
    if (titres.count() !=0 )
    {
        ui->NbTitres->setText( QString::number( titres[0] ) );
        ui->NbTitresMP3->setText( QString::number( titres[1] ) );
        Pourcentage = titres[1]*100/titres[0];
    }
    ui->Pourcentage->setText(QString::number( Pourcentage )+" %");

   afficherListeAlbSansMP3();

}

void OngletPhys::afficherListeAlbSansMP3()
{
    ui->AlbSansMP3->clear();

    //Affichage des albums
    QList<int> albums = m_bddInterface.AlbSansMP3( m_artiste, m_categorie );

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {

        if ( albums[cpt] > 0 )
        {
            Meta_Album* album = Meta_Album::RecupererBDD( albums[cpt] );


            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );
            item->setIcon( QIcon( scaled ) );

            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, albums[cpt] );
            item->setText( QString::number( album->getannee() ) + " - " + album->getnom_album() );

            ui->AlbSansMP3->addItem( item );

            delete album;
        }

    }

}

void OngletPhys::on_AlbSansMP3_pressed(const QModelIndex &index)
{
    m_selection = index.data( Qt::UserRole ).toInt();

    vider( "Infos" );
    if ( m_artiste !="-1" )
    {
        ui->Compil->clearSelection();
        ui->Singles->clearSelection();
        AfficherInfosAlbum( 1 );
    } else
    {
        ui->Albums->clearSelection();
        ui->Singles->clearSelection();
        AfficherInfosAlbum( 2 );
    }

    AfficherArtisteSelectionne();
}

void OngletPhys::on_Categories_clicked(const QModelIndex &index)
{
    m_categorie = index.data( Qt::UserRole ).toInt();
    afficherListeArtiste();

}

void OngletPhys::on_ModifArtiste_clicked()
{

    Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( m_artiste.toInt() );
    DialogModifierArtiste temp( artiste, this );
    temp.exec();
    delete artiste;
    actualiserOnglet();
}
