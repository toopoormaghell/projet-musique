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

    QList<int> liste = appelBDD->ListeArtiste();

    for ( int i = 0; i<liste.count(); i++ )
    {
        BDDArtiste* art = BDDArtiste::recupererBDD( liste[i] );

        ui->ListeArtiste->addItem( art->m_nom,QVariant( art->id() ) );
    }
}

void OngletArtiste::on_ChangerNom_clicked()
{
    m_artiste =  ui->ListeArtiste->currentData(Qt::UserRole).toString();
    AfficherListeTitresDistincts();
    AfficherInfosArtiste();
    AfficherAlbums();
}
void OngletArtiste::AfficherInfosArtiste()
{
    //On affiche le nom de l'artiste
    BDDArtiste* art = BDDArtiste::recupererBDD( m_artiste.toInt());

    //On s'occupe de sa pochette
    QPixmap scaled( QPixmap::fromImage( art->m_pochette->m_image ) );
    scaled = scaled.scaled( 150, 150 );
    ui->PochArtiste->setPixmap( scaled );


}
void OngletArtiste::AfficherListeTitresDistincts()
{
    QString temp = "" ;int compteur = 0;
    ui->TitresDistincts->clear();
    QList<int> result = appelBDD->TitresPourArt( m_artiste );



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
    QList<int> result= appelBDD->AlbumsPourArt( m_artiste );

    for ( int i = 0; i < result.count(); i++ )
    {
        BDDAlbum* alb = BDDAlbum::recupererBDD( result[i] );

        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->m_nom );
        item->setData( Qt::UserRole, alb->id() );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
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
