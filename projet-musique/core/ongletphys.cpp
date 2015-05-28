#include "ongletphys.h"
#include "ui_ongletphys.h"
#include "bddafficherphys.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddphys.h"


OngletPhys::OngletPhys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletPhys)
{
    ui->setupUi(this);
    afficherListeArtiste();

}
void OngletPhys::on_Artistes_currentTextChanged(const QString &arg1)
{
    afficherListeAlbum();

}

OngletPhys::~OngletPhys()
{
    delete ui;
}
void OngletPhys::afficherListeArtiste()
{


    //Affichage des artistes
    QList<int> artistes=m_bddInterface.ListeArtiste();

    for (int cpt=0;cpt<artistes.count();cpt++)
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

    ui->Artistes->setCurrentRow(0);
}
void OngletPhys::afficherListeAlbum()
{
    ui->Albums->clear();

    //Choix de l'Artiste des Albums à afficher
    QString Artiste=choixArtiste();


    //Affichage des albums
    QList<int> albums=m_bddInterface.listeAlbums(Artiste);

    for (int cpt=0;cpt<albums.count();cpt++) {

        BDDAlbum* album= BDDAlbum::RecupererAlbum(albums[cpt]);


        if (album->m_id>0)
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );

            item->setIcon( QIcon( scaled ) );


            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, albums[cpt] );
            item->setText( QString::number(album->m_annee)+" - "+album->m_nom );

            ui->Albums->addItem( item );


        }
        delete album;

    }

    ui->Albums->setCurrentRow(1);
}
void OngletPhys::AfficherInfosAlbum()
{
    QString id= choixAlbum();

    BDDPhys* phys= BDDPhys::RecupererPhys(id.toInt());
    ui->Annee->setText( QString::number(phys->m_album->m_annee));

    QPixmap scaled( QPixmap::fromImage( phys->m_album->m_pochette->m_image  ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap(scaled);

}
QString OngletPhys::choixAlbum()
{
    QListWidgetItem *item=ui->Albums->currentItem();
    if (item==NULL)
    {
        item=ui->Albums->item(1);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}

QString OngletPhys::choixArtiste()
{
    QListWidgetItem *item=ui->Artistes->currentItem();
    if (item==NULL)
    {
        item=ui->Artistes->item(0);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}


void OngletPhys::on_Albums_currentTextChanged(const QString &currentText)
{
    vider("Infos");
    AfficherInfosAlbum();
}
void OngletPhys::vider(QString type)
{
    if (type=="Artiste")
    {
        ui->Artistes->clear();
    }
    if (type=="Categories")
    {
        ui->Categories->clear();
    }
    if (type=="Albums")
    {
        ui->Albums->clear();

    }
    if (type=="Infos")
    {
        ui->Annee->clear();
        ui->Artiste->clear();
        ui->NomAlbum->clear();
        ui->Pochette->clear();
        ui->Titres->clear();


    }
}
