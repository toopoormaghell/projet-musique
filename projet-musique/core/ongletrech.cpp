#include "ongletrech.h"
#include "ui_ongletrech.h"

#include <QFileInfo>
#include <QDir>
#include <QFile>

#include "meta_album.h"
#include "meta_artiste.h"
#include "meta_titre.h"


OngletRech::OngletRech( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::OngletRech )
{
    ui->setupUi( this );
    m_rech = "";
    AffichageResGroup( 0);
    connect( ui->Rech,SIGNAL( returnPressed() ),this, SLOT ( on_pushButton_clicked() ) );

    connect( ui->AlbResult,SIGNAL( activated( QModelIndex ) ) ,this, SLOT ( on_AlbResult_clicked (QModelIndex ) ) ) ;
    connect ( ui->ArtResult, SIGNAL( activated( QModelIndex ) ),this,SLOT( on_ArtResult_clicked( QModelIndex ) ) );
    connect ( ui->TitResult,SIGNAL( activated( QModelIndex ) ),this,SLOT( on_TitResult_clicked( QModelIndex ) ) );
    connect( ui->AlbumspourArt,SIGNAL(activated(QModelIndex)),this,SLOT(on_AlbumspourArt_clicked(QModelIndex)));
    connect( ui->TitresResultats,SIGNAL(activated(QModelIndex)),this,SLOT(on_TitresResultats_clicked(QModelIndex)));
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
        Meta_Titre* relation = Meta_Titre::RecupererBDD( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( relation->getnom_titre() );
        item->setData( Qt::UserRole, relation->getid_relation() );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( relation->getpoch() ) );
        item->setIcon( QIcon( scaled ) );

        ui->TitResult->addItem( item );
        delete relation;


    }
}
void OngletRech::affichageAlbums()
{
    //On s'occupe d'afficher les albums
    ui->AlbResult->clear();
    QList<int> result = appelBDD->RechAlb( m_rech );

    for ( int i = 0; i < result.count(); i++ )
    {
        Meta_Album* alb = Meta_Album::RecupererBDD( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->getnom_album() );
        item->setData( Qt::UserRole, alb->getid_alb() );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->getPoch() ) );
        item->setIcon( QIcon( scaled ) );
        ui->AlbResult->addItem( item );
        delete alb;
    }

}
void OngletRech::affichageArtistes()
{
    //On s'occupe d'afficher les artistes
    ui->ArtResult->clear();
    QList<int> result = appelBDD->RechArt( m_rech );

    for ( int i = 0; i < result.count(); i++ )
    {
        Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( artiste->getNom_Artiste() );
        item->setData( Qt::UserRole, artiste->get_id_artiste() );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( artiste->getPoch() ) );
        item->setIcon( QIcon( scaled ) );
        ui->ArtResult->addItem( item );
        delete artiste;
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

    //On affiche le nom de l'artiste
    Meta_Artiste* art = Meta_Artiste::RecupererBDD( m_artiste.toInt() );
    ui->Artiste_Albums->setText( art->getNom_Artiste().toUpper() );
    //On s'occupe d'afficher les albums
    QList<int> result= appelBDD->AlbumsPourArt( QString::number( art->get_id_artiste() ) );
    ui->Artiste_Albums->setText( art->getNom_Artiste().toUpper() + "( "+ QString::number(result.count() )+ " albums)" );

    for ( int i = 0; i < result.count(); i++ )
    {
        Meta_Album* alb = Meta_Album::RecupererBDD( result[i] );

        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->getnom_album() );
        item->setData( Qt::UserRole, alb->getid_alb() );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->getPoch() ) );
        item->setIcon( QIcon( scaled ) );
        ui->AlbumspourArt->addItem( item );
        delete alb;
    }
    delete art;

    affichageTitresParArtiste();
}


void OngletRech::affichageTitresParArtiste()
{

    ui->TitresResultats->clear();
    QStringList result = appelBDD->TitresPourArt( m_artiste );

    for ( int i = 0; i < result.count(); i++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( result[i] );
        ui->TitresResultats->addItem( item );

    }

    ui->Album_Titre->setText("TITRES DE L'ARTISTE ("+ QString::number( result.count() ) +" DISTINCTS )");
}

void OngletRech::affichageTitresParAlbum()
{
    //On affiche le nom de l'album
    Meta_Album* alb = Meta_Album::RecupererBDD( m_album.toInt() );
    ui->Album_Titre->setText( alb->getnom_album().toUpper() );

    //On s'occupe d'afficher les titres
    ui->TitresResultats->clear();
    QList<Meta_Titre *>  result = alb->gettitres();

    QPixmap mp3( ":/Autres/Mp3" );
    QPixmap phys( ":/Autres/Phys" );

    for ( int i = 0; i < result.count(); i++ )
    {

        Meta_Titre* rel =  result[i] ;
        QListWidgetItem* item = new QListWidgetItem;
        item->setData( Qt::UserRole, rel->getid_relation() );

        QString temp = QString::number( rel->getnum_piste() ).rightJustified( 2, '0' )+" - "+rel->getnom_titre();

        if (alb->getid_support_p() == 2)
        {
            temp += " - " + rel->getnom_artiste();
        }

        item->setText( temp );

        //On s'occupe d'afficher si c'est le titre existe en MP3 et Phys
        if ( rel->getid_support_m() != -1 )
        {
            item->setIcon( QIcon( mp3 ) );
        }
        if ( rel->getid_support_p() != -1 )
        {
            item->setIcon( QIcon( phys ) );
        }

        if ( alb->getid_support_p() != 2 )
        {
            ui->TitresResultats->addItem( item );
        } else
        {
            if ( m_artiste == QString::number ( rel->getid_art() ))
            {
                ui->TitresResultats->addItem( item );
            }
        }



    }

    //On affiche les infos de l'album
    ui->label_7->setText("INFORMATIONS ALBUM");
    ui->NomArtiste->setText( alb->getnom_artiste().toUpper() );
    ui->NomAlbum->setText( alb->getnom_album().toUpper() );
    ui->NomTitre->setText( QString::number( alb->getannee() ) );
    ui->Duree->setText( QString::number (result.count() ) + " titres");
    QPixmap scaled ( QPixmap::fromImage( alb->getPoch() ) );
    scaled = scaled.scaled( 150, 150 );
    ui->PochTitre->setPixmap( scaled );

    delete alb;
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
    ui->label_7->setText("INFORMATIONS TITRE");
    Meta_Titre* rel = Meta_Titre::RecupererBDD( m_titre.toInt() );

    //On affiche la pochette
    QPixmap scaled ( QPixmap::fromImage( rel->getpoch() ) );
    scaled = scaled.scaled( 150, 150 );
    ui->PochTitre->setPixmap( scaled );

    //On affiche le nom du titre
    ui->NomTitre->setText( QString::number( rel->getnum_piste() ).rightJustified( 2, '0' ) + " - " + rel->getnom_titre() );
    //On affiche le nom de l'album
    ui->NomAlbum->setText( rel->getnom_album() +"("+QString::number ( rel->getannee() ) +")");
    //On affiche le nom de l'artiste
    ui->NomArtiste->setText( rel->getnom_artiste() );
    //On affiche la durée
    ui->Duree->setText( rel->getduree() );

    //On ajoute un bouton ou non
    if ( rel->getid_support_m() != -1 )
    {
        ui->OuvrirDossier->setVisible( true);
    } else
    {
        ui->OuvrirDossier->setVisible( false );
    }
    delete rel;

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
    /*   ui->ResSimi->setVisible( true );
    ui->ListeSimilaires->clear();
    Handle<BDDTitre> titre = BDDTitre::RecupererTitre( m_titre.toInt() );
    QList<int> Simi = titre->Similaires( m_titre.toInt() );
    //On affiche chaque titre similaire
    for ( int i = 0; i < Simi.count(); i++ )
    {
        //On récupère les infos du titre similaire
        Handle<BDDMp3> mp3 = BDDMp3::RecupererMp3( Simi[i] );

        //On affiche les infos du titre dans un item
        QListWidgetItem* item = new QListWidgetItem;
        item->setData( Qt::UserRole, mp3->id() );
        item->setText( QString::number( mp3->m_relation->m_album->m_annee ) + " - " + mp3->m_relation->m_titre->m_nom );
        item->setToolTip( mp3->m_relation->m_titre->m_nom );
        item->setFlags( Qt::ItemIsEnabled );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( mp3->m_relation->m_album->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );

        ui->ListeSimilaires->addItem( item );
    }

    */
}

void OngletRech::on_CopierDansDossier_clicked()
{

    /* Meta_Titre* rel = BDDRelation::RecupererRelationParTitre( m_titre.toInt() );
    if ( rel->m_mp3 )
    {
        Handle<BDDMp3> mp3 = BDDMp3::RecupererMP3ParTitre( m_titre.toInt() );

        QFileInfo fich( mp3->m_chemin );
        QString doss = ("C:/Users/Alex/Desktop/Musique/");

        if (  mp3->m_relation->m_artiste->m_nomFormate == "indochine" )
        {
            doss +=  mp3->m_relation->m_artiste->m_nom;
        }
        QDir dir( doss );
        dir.mkpath(doss);
        QString nouvelemplacementchemin =  doss + "/" + fich.fileName();
        QFile::copy( mp3->m_chemin, nouvelemplacementchemin );
    }
    delete rel;

    */
}
