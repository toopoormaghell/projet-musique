#include "ongletartiste.h"
#include "ui_ongletartiste.h"

#include <QCompleter>
#include <QStringList>
#include <QPainter>

#include "bddafficherartiste.h"



#include "meta_album.h"
#include "meta_artiste.h"
#include "meta_titre.h"

OngletArtiste::OngletArtiste(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletArtiste)
{
    ui->setupUi(this);
    ActualiserOnglet();
}

OngletArtiste::~OngletArtiste()
{
    delete ui;
}
void OngletArtiste::ActualiserOnglet()
{

    QStringList listeArt = appelBDD->ListeArtiste();

    QCompleter* completer = new QCompleter ( listeArt );
    completer->setCaseSensitivity( Qt::CaseInsensitive );
    ui->Artistes->setCompleter( completer );
}

void OngletArtiste::on_ChangerNom_clicked()
{
    m_artiste = appelBDD->RecupererIdArtisteNom( ui->Artistes->text() );
    AfficherListeTitresDistincts();
    AfficherInfosArtiste();
    AfficherAlbums();
}
void OngletArtiste::AfficherInfosArtiste()
{
    //On affiche le nom de l'artiste
    Meta_Artiste* art = Meta_Artiste::RecupererBDD( m_artiste );

    //On s'occupe de sa pochette
    QPixmap scaled( QPixmap::fromImage( art->getPoch() ) );
    scaled = scaled.scaled( 150, 150 );
    ui->PochArtiste->setPixmap( scaled );

}
void OngletArtiste::AfficherListeTitresDistincts()
{
    ui->TitresDistincts->clear();
    QStringList result = appelBDD->TitresPourArt( QString::number(m_artiste) );

    for ( int i = 0; i < result.count(); i++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( result[i] );
        ui->TitresDistincts->addItem( item );
    }


    ui->TitresDistinctsLabel->setText("TITRES DE L'ARTISTE ("+ QString::number( result.count() ) +" DISTINCTS )");

}
void OngletArtiste::AfficherAlbums()
{
    ui->Albums->clear();
    ui->Compil->clear();
    ui->Singles->clear();

    QPixmap mp3phys( ":/Autres/MP3Phys" );
    mp3phys = mp3phys.scaled( 50,50 );
    QPixmap mp3( ":/Autres/Mp3" );
    mp3 = mp3.scaled( 50,50);
    QPixmap phys( ":/Autres/Phys" );
    phys = phys.scaled( 50 , 50 );

    //On s'occupe d'afficher les albums
    QList<int> result= appelBDD->AlbumsPourArt( QString::number(m_artiste) );

    for ( int i = 0; i < result.count(); i++ )
    {
        Meta_Album* alb = Meta_Album::RecupererBDD( result[i] );

        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->getnom_album() );
        item->setData( Qt::UserRole, alb->getid_alb() );

        QPixmap top( QPixmap::fromImage( alb->getPoch() ) );
        top = top.scaled(150,150);

        // both images are opaque because JPEG has no alpha channel
        QPainter p( &top );


        if ( alb->getid_support_m() == 4 )
        {
            if ( alb->getid_support_p() == -1 )
            {
                p.drawPixmap( 0, 100, mp3 );
            } else
            {
                p.drawPixmap( 0, 100, mp3phys );  // drawn as-is
            }
        } else
        {
            if ( alb->getid_support_p() != -1 )
            {
                p.drawPixmap( 0, 100, phys );
            }
        }


        item->setIcon( top );

        switch ( alb->getid_type() )
        {
        case 1: ui->Albums->addItem( item );break;
        case 2: ui->Compil->addItem( item );break;
        case 11: ui->Singles->addItem( item );break;
        default : ui->Albums->addItem( item );
        }

        delete alb;
    }
    CacherRubriques();
}
void OngletArtiste::InfosAlbum()
{
    ui->Annee->clear();
    ui->Titres->clear();
    ui->NomAlbum->clear();

    Meta_Album* alb = Meta_Album::RecupererBDD( m_album );

    ui->Annee->setText( QString::number( alb->getannee() ) );
    ui->NomAlbum->setText( alb->getnom_album() );

    for (int i = 0; i < alb->gettitres().count() ; i++ )
    {
        Meta_Titre* rel = alb->gettitres()[i];

        QListWidgetItem* item = new QListWidgetItem;
        if ( alb->getid_support_p() == 2 )
        {
            if ( m_artiste == rel->getid_art() )
            {
                QFont m_police( "Monotype Corsiva", 11, 75 );
                item->setTextColor( Qt::blue );
                item->setFont( m_police );
            }

            item->setText( QString::number( rel->getnum_piste() ).rightJustified( 2, '0' ) + " - " + rel->getnom_titre() + "(" + rel->getduree() + ") - " + rel->getnom_artiste() );


        } else {

            item->setText( QString::number( rel->getnum_piste() ).rightJustified( 2, '0' ) + " - " + rel->getnom_titre() + "(" + rel->getduree() + ")" );
        }
        ui->Titres->addItem( item );
    }

    //On s'occupe de sa pochette
    QPixmap scaled( QPixmap::fromImage( alb->getPoch() ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );
}

void OngletArtiste::on_Albums_clicked(const QModelIndex &index)
{
    m_album = index.data(Qt::UserRole).toInt();
    InfosAlbum();
}

void OngletArtiste::on_Singles_clicked(const QModelIndex &index)
{
    m_album = index.data(Qt::UserRole).toInt();
    InfosAlbum();
}

void OngletArtiste::on_Compil_clicked(const QModelIndex &index)
{
    m_album = index.data(Qt::UserRole).toInt();
    InfosAlbum();
}
void OngletArtiste::CacherRubriques()
{
    int nbalbums = ui->Albums->count();
    int nbsingles = ui->Singles->count();
    int nbcompils = ui->Compil->count();

    if ( ( nbsingles == 0 || nbcompils == 0 ) && nbalbums > 12 )

    {
        int RubriquesCachees = 0;

        if ( nbsingles == 0 )
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

        if ( nbcompils == 0 )
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
