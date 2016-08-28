#include "ongletfusion.h"
#include "ui_ongletfusion.h"
#include "bddartiste.h"
#include "bddpoch.h"
#include "bddalbum.h"
#include <QDebug>

OngletFusion::OngletFusion(QWidget *parent) :
    QWidget(parent),
    nb_passage( 0),
    ui(new Ui::OngletFusion)
{
    ui->setupUi(this);
}

OngletFusion::~OngletFusion()
{
    delete ui;
}

void OngletFusion::on_Ok_clicked()
{
    m_donnee = ui->Donnee->text();
    affichageChoixPossibles();
}
void OngletFusion::affichageChoixPossibles()
{
    //On s'occupe d'afficher les artistes
    ui->ChoixFusions->clear();
    QList<int> result = appelBDD->RechArt( m_donnee );

    for ( int i = 0; i < result.count(); i++ )
    {
        BDDArtiste* artiste = BDDArtiste::RecupererArtiste( result[i] );
        QListWidgetItem* item = new QListWidgetItem;
        item->setText( artiste->m_nom );
        item->setData( Qt::UserRole, artiste->m_id );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( artiste->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->ChoixFusions->addItem( item );
    }
}

void OngletFusion::on_ChoixFusions_clicked(const QModelIndex &index)
{
    switch (nb_passage)
    {
    case 0: AffichageFusions( index.data(Qt::UserRole).toString() );break;
    default: Choix( index.data(Qt::UserRole).toString() );
    }

}
void OngletFusion::AffichageFusions(QString id)
{
    ui->ChoixFusions->clear();

    //On s'occupe d'afficher les albums
    QList<int> result= appelBDD->AlbumsPourArt( id );
    for ( int i = 0; i < result.count(); i++ )
    {
        BDDAlbum* alb = BDDAlbum::RecupererAlbum( result[i] );

        QListWidgetItem* item = new QListWidgetItem;
        item->setText( alb->m_nom );
        item->setData( Qt::UserRole, alb->m_id );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->ChoixFusions->addItem( item );
    }
    nb_passage++;
}
void OngletFusion::Choix(QString id)
{
    if ( nb_passage%2==0)
    {
        m_choix2 = id;
    } else
    {
        m_choix1 = id;
    }
    nb_passage ++;
    qDebug() << m_choix1 << m_choix2;
}
void OngletFusion::AfficherChoix()
{

}
