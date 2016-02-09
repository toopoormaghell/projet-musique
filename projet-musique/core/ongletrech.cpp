#include "ongletrech.h"
#include "ui_ongletrech.h"
#include "bddrech.h"
#include "bddtitre.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddpoch.h"

OngletRech::OngletRech(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletRech)
{
    ui->setupUi(this);
    m_rech="";

}

OngletRech::~OngletRech()
{
    delete ui;
}

void OngletRech::on_pushButton_clicked()
{
    m_rech = ui->lineEdit->text();
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
    QList<int> result = appelBDD->RechTitres(m_rech);

    for (int i=0;i<result.count();i++)
    {
        BDDTitre* titre = BDDTitre::RecupererTitre(result[i]);

        QListWidgetItem* item = new QListWidgetItem;
        item->setText(titre->m_nom);
        item->setData(Qt::UserRole, titre->m_id);
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( titre->m_album->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->TitResult->addItem(item);
    }
}
void OngletRech::affichageAlbums()
{
    //On s'occupe d'afficher les titres
    ui->AlbResult->clear();
    QList<int> result = appelBDD->RechAlb(m_rech);

    for (int i=0;i<result.count();i++)
    {
        BDDAlbum* alb = BDDAlbum::RecupererAlbum(result[i]);

        QListWidgetItem* item = new QListWidgetItem;
        item->setText(alb->m_nom);
        item->setData(Qt::UserRole, alb->m_id);
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->AlbResult->addItem(item);
    }

}
void OngletRech::affichageArtistes()
{
    //On s'occupe d'afficher les titres
    ui->ArtResult->clear();
    QList<int> result = appelBDD->RechArt(m_rech);

    for (int i=0;i<result.count();i++)
    {
        BDDArtiste* artiste = BDDArtiste::RecupererArtiste(result[i]);

        QListWidgetItem* item = new QListWidgetItem;
        item->setText(artiste->m_nom);
        item->setData(Qt::UserRole, artiste->m_id);
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( artiste->m_pochette->m_image) );
        item->setIcon( QIcon( scaled ) );
        ui->ArtResult->addItem(item);
    }
}
