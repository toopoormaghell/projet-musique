#include "ongletphys.h"
#include "ui_ongletphys.h"
#include "bddafficherphys.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddphys.h"
#include "bddaffichermp3.h"
#include "modifieralbumdialog.h"
#include <QDebug>

OngletPhys::OngletPhys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletPhys),
    m_selection(0)
{
    ui->setupUi(this);
    vider("Artiste");
    afficherListeType();
    afficherListeArtiste();
    AfficherArtisteSelectionne();

}
void OngletPhys::on_Artistes_currentTextChanged(const QString &arg1)
{
    afficherListeAlbum();
    afficherListeCompils();
    afficherListeSingles();
    AfficherArtisteSelectionne();
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
void OngletPhys::afficherListeSingles()
{
    ui->Singles->clear();

    //Choix de l'Artiste des Albums à afficher
    QString Artiste=choixArtiste();


    //Affichage des albums
    QList<int> singles=m_bddInterface.listeSingles(Artiste);

    for (int cpt=0;cpt<singles.count();cpt++) {

        BDDAlbum* album= BDDAlbum::RecupererAlbum(singles[cpt]);


        if (album->m_id>0)
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );

            item->setIcon( QIcon( scaled ) );


            //On s'occupe du nom de l'album
            item->setData( Qt::UserRole, singles[cpt] );
            item->setText( QString::number(album->m_annee)+" - "+album->m_nom );

            ui->Singles->addItem( item );


        }
        delete album;

    }
}

void OngletPhys::AfficherArtisteSelectionne()
{
    QString id_artiste= choixArtiste();
    BDDArtiste* artiste = BDDArtiste::RecupererArtiste( id_artiste.toInt() );

    ui->Artiste->setText(artiste->m_nom);
}

void OngletPhys::afficherListeCompils()
{
    ui->Compil->clear();

    //Choix de l'Artiste des Albums à afficher
    QString Artiste=choixArtiste();


    //Affichage des albums
    QList<int> albums=m_bddInterface.listeCompils(Artiste);

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

            ui->Compil->addItem( item );

        }
        delete album;
    }
}

void OngletPhys::AfficherInfosAlbum(int Type)
{
    QString id;
    switch (Type)
    {
    case 1: id= choixAlbum();break;
    case 2: id = choixSingle();break;
    case 3: id=choixCompil();break;

    }
    m_selection=id.toInt();
    BDDPhys* phys= BDDPhys::RecupererPhys(m_selection);
    ui->Annee->setText( QString::number(phys->m_album->m_annee));
    ui->NomAlbum->setText(phys->m_album->m_nom);
    QPixmap scaled( QPixmap::fromImage( phys->m_album->m_pochette->m_image  ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap(scaled);

    QPixmap mp3physoui(":/Autres/Vrai");
    QPixmap mp3physnon(":/Autres/Faux");
    for(int i=0;i<phys->m_titres.count();i++)
    {
        QListWidgetItem* item=new QListWidgetItem;

        QString temp;
        temp = QString::number(phys->m_titres[i]->m_num_piste).rightJustified(2,'0') + " - "+ phys->m_titres[i]->m_nom+"("+phys->m_titres[i]->m_duree+")";
        item->setText(temp);
        if (phys->m_titres[i]->m_mp3etphys)
        {
            item->setIcon(QIcon(mp3physoui));
        } else
        {
            item->setIcon(QIcon(mp3physnon));
        }

        ui->Titres->addItem(item);

    }
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
QString OngletPhys::choixSingle()
{
    QListWidgetItem *item=ui->Singles->currentItem();
    if (item==NULL)
    {
        item=ui->Singles->item(1);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}
QString OngletPhys::choixCompil()
{
    QListWidgetItem *item=ui->Compil->currentItem();
    if (item==NULL)
    {
        item=ui->Compil->item(1);
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
void OngletPhys::on_Albums_itemPressed(QListWidgetItem *item)
{
    ui->Compil->clearSelection();
    ui->Singles->clearSelection();
    vider("Infos");
    AfficherInfosAlbum(1);
    AfficherArtisteSelectionne();
}

void OngletPhys::on_Compil_itemPressed(QListWidgetItem *item)
{
    ui->Albums->clearSelection();
    ui->Singles->clearSelection();
    vider("Infos");
    AfficherInfosAlbum(3);
    AfficherArtisteSelectionne();
}
void OngletPhys::afficherListeType()
{
    ui->Categories->clear();

    QStringList types;
    types << "Tout" << "0";
    BDDAfficherMp3 temp;

    types <<temp.RecupererListeTypes("Phys") ;

    QImage image("./Pochettes/def.jpg");
    for(int cpt=0;cpt<types.count();cpt=cpt+2)
    {
        QPixmap scaled( QPixmap::fromImage( image ) );
        scaled = scaled.scaled( 150, 150 );
        QListWidgetItem* item = new QListWidgetItem;
        item->setIcon( QIcon( scaled ) );
        item->setData(Qt::UserRole,types[cpt+1]);
        item->setText(types[cpt]);

        ui->Categories->addItem(item);
    }
    ui->Categories->setCurrentRow(1);
}

void OngletPhys::on_Singles_itemPressed(QListWidgetItem *item)
{
    ui->Albums->clearSelection();
    ui->Compil->clearSelection();
    vider("Infos");
    AfficherInfosAlbum(2);
    AfficherArtisteSelectionne();
}

void OngletPhys::on_Modifier_clicked()
{
    ModifierAlbumDialog modif(m_selection,this);
    modif.exec();

}
