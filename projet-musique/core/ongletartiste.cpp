#include "ongletartiste.h"
#include "ui_ongletartiste.h"
#include "bddafficherartiste.h"
#include <QCompleter>
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddrelation.h"
#include "bddalbum.h"
#include "bddpoch.h"
#include "bddtype.h"
#include <QStringList>
#include <QPainter>

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

    QStringList listeArt;
    QList<int> liste = appelBDD->ListeArtiste();

    for ( int i = 0; i<liste.count(); i++ )
    {
        BDDArtiste* art = BDDArtiste::recupererBDD( liste[i] );
        listeArt << art->m_nom;

        delete art;
    }

    QCompleter* completer = new QCompleter ( listeArt );
    completer->setCaseSensitivity( Qt::CaseInsensitive );
    ui->Artistes->setCompleter( completer );


}

void OngletArtiste::on_ChangerNom_clicked()
{
    m_artiste = BDDArtiste::recupererBDD( ui->Artistes->text() )->id();
    AfficherListeTitresDistincts();
    AfficherInfosArtiste();
    AfficherAlbums();
}
void OngletArtiste::AfficherInfosArtiste()
{
    //On affiche le nom de l'artiste
    BDDArtiste* art = BDDArtiste::recupererBDD( m_artiste);

    //On s'occupe de sa pochette
    QPixmap scaled( QPixmap::fromImage( art->m_pochette->m_image ) );
    scaled = scaled.scaled( 150, 150 );
    ui->PochArtiste->setPixmap( scaled );

}
void OngletArtiste::AfficherListeTitresDistincts()
{
    QString temp = "" ;int compteur = 0;
    ui->TitresDistincts->clear();
    QList<int> result = appelBDD->TitresPourArt( QString::number(m_artiste) );

    int titretemp = 0;

    for ( int i = 0; i < result.count(); i=i+2 )
    {

        if ( titretemp != result[i] )
        {
            if (titretemp != 0)
            {
                temp = temp + ")";
                QListWidgetItem* item = new QListWidgetItem;
                item->setText( temp );
                ui->TitresDistincts->addItem( item );
            }
            temp = "";
            BDDTitre* tit = BDDTitre::recupererBDD( result[i] );
            BDDRelation* rel = BDDRelation::RecupererRelation( result[i+1] );
            temp = tit->m_nom + " ( "+ rel->m_album->m_nom;

            compteur ++;
            delete tit;delete rel;
        } else
        {
            BDDRelation* rel = BDDRelation::RecupererRelation( result[i+1] );
            temp = temp +", "+rel->m_album->m_nom;

            delete rel;
        }

        titretemp = result[i];
    }
    //je finis de copier le dernier cas
    temp = temp + ")";
    QListWidgetItem* item = new QListWidgetItem;
    item->setText( temp );
    ui->TitresDistincts->addItem( item );

}
void OngletArtiste::AfficherAlbums()
{
    ui->Albums->clear();
    ui->Compil->clear();
    ui->Singles->clear();
    //On s'occupe d'afficher les albums
    QList<int> result= appelBDD->AlbumsPourArt( QString::number(m_artiste) );

    for ( int i = 0; i < result.count(); i++ )
    {
        BDDAlbum* alb = BDDAlbum::recupererBDD( result[i] );

        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->m_nom );
        item->setData( Qt::UserRole, alb->id() );


        //On s'occupe de sa pochette
        //  QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        //     item->setIcon( QIcon( scaled ) );

        QPixmap top( QPixmap::fromImage( alb->m_pochette->m_image ) );
        QPixmap bot(":/Autres/MP3Phys");
        bot =  bot.scaled(50,50);

        // both images are opaque because JPEG has no alpha channel

        QPainter p( &top );
        p.drawPixmap(0, 100, bot);         // drawn as-is

        item->setIcon( top );


        switch ( alb->m_type->id() )
        {
        case 1: ui->Albums->addItem( item );break;
        case 2:ui->Compil->addItem( item );break;
        case 11:ui->Singles->addItem( item );break;
        default : ui->Albums->addItem( item );
        }

        delete alb;
    }
}
void OngletArtiste::InfosAlbum()
{
    ui->Annee->clear();
    ui->Titres->clear();
    ui->NomAlbum->clear();

    BDDAlbum* alb = BDDAlbum::recupererBDD( m_album );

    ui->Annee->setText( QString::number( alb->m_annee ) );
    ui->NomAlbum->setText( alb->m_nom );

    QList<int> liste = appelBDD->TitresPourAlbum( m_album );

    for (int i = 0;i < liste.count() ; i++ )
    {
        BDDRelation* rel = BDDRelation::RecupererRelation( liste[i] );

        QListWidgetItem* item = new QListWidgetItem;
        if ( alb->m_type->id() == 2 )
        {
            if ( m_artiste == rel->m_artiste->id() )
            {
                QFont m_police( "Monotype Corsiva", 11, 75 );
                item->setTextColor( Qt::blue );
                item->setFont( m_police );
            }

            item->setText( QString::number( rel->m_num_piste ).rightJustified( 2, '0' ) + " - " + rel->m_titre->m_nom + "(" + rel->m_duree + ") - " + rel->m_artiste->m_nom);


        } else {

            item->setText( QString::number( rel->m_num_piste ).rightJustified( 2, '0' ) + " - " + rel->m_titre->m_nom + "(" + rel->m_duree + ")" );
        }
        ui->Titres->addItem( item );
    }

    //On s'occupe de sa pochette
    QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
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
