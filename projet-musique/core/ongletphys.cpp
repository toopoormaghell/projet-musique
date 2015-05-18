#include "ongletphys.h"
#include "ui_ongletphys.h"
#include <QDebug>
#include "affichagecommun.h"
#include "QMessageBox"
#include "dialogmodifieralbum.h"
#include "dialogchangerpochette.h"

OngletPhys::OngletPhys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletPhys)
{


    ui->setupUi(this);
    ui->label->setText("A\nL\nB\nU\nM");
    ui->label_2->setText("S\nI\nN\nG\nL\nE");
    ui->label_3->setText("C\nO\nM\nP\nI\nL");
    ui->label_4->setText("S\nT\nA\nT\nS");
    afficherListeCategories();
    if (ui->Categories->count()>1)
    {
        ui->Artistes->clear();
        afficherListeArtiste();
        afficherListeAlbum();

    }
}
OngletPhys::~OngletPhys()
{
    delete ui;
}
void OngletPhys::afficherListeArtiste()
{
    ui->Artistes->clear();
    AffichageCommun temp;
    QString Categorie=choixCategorie();
    //Affichage des artistes
    QStringList artistes=m_bddInterface.listeArtistesPhys(Categorie);
    if(artistes.size()==0)
    {
        ui->Artistes->addItem(new QListWidgetItem("Pas d'Albums Physiques Enregistrés"));
    } else {


        for (int cpt=0;cpt<artistes.count();cpt=cpt+2) {
            //On s'occupe de la pochette
            QImage image=m_bddInterface.afficherPochette(artistes[cpt+1],"Artiste");
            QListWidgetItem *mediaCell = temp.afficherPochetteList(image);
            //On s'occupe du nom de l'artiste et de son Id caché
            mediaCell->setData(Qt::UserRole,artistes[cpt+1]);
            mediaCell->setText(artistes[cpt]);
            //On affiche le tout
            ui->Artistes->addItem(mediaCell);
        }
    }
    ui->Artistes->item(0)->setSelected(true);
}
void OngletPhys::afficherListeCategories()
{
    ui->Categories->clear();
    AffichageCommun temp;
    //Categorie "Tout"
    QImage* image=new QImage("./Pochettes/def.jpg");
    QListWidgetItem* mediaCell=temp.afficherPochetteList(*image);
    //On s'occupe du nom de l'artiste
    mediaCell->setText("Tout");
    ui->Categories->addItem(mediaCell);
    //On s'occupe des autres catégories
    QStringList categories=m_bddInterface.listeCategoriesPhys();
    for (int cpt=0;cpt<categories.count();cpt++) {
        mediaCell=temp.afficherPochetteList(*image);
        //On s'occupe du nom de l'artiste
        mediaCell->setText(categories[cpt]);
        ui->Categories->addItem(mediaCell);
    }
    //On sélectionne la première catégorie
    ui->Categories->item(0)->setSelected(true);
}

QString OngletPhys::choixCategorie()
{
    QListWidgetItem *item=ui->Categories->currentItem();
    if (item==NULL)
    {
        item=ui->Categories->item(0);
    }
    return item->text();
}
QString OngletPhys::choixArtiste()
{
    QListWidgetItem *item=ui->Artistes->currentItem();
    if (item==NULL)
    {
        item=ui->Artistes->item(0);
    }
    QString Categorie=choixCategorie();

    if (Categorie=="Compil")
    {
        return item->text();
    } else {
        return item->data(Qt::UserRole).toString();
    }
}

QString OngletPhys::choixAlbum()
{
QListWidgetItem *item=ui->Albums->currentItem();
if (item==NULL)
{
    item=ui->Albums->item(0);
}

    return item->data(Qt::UserRole).toString();
}




void OngletPhys::afficherNomArtiste()
{
    QListWidgetItem *item=ui->Artistes->currentItem();
    if (item==NULL)
    {
        item=ui->Artistes->item(0);
    }

    ui->Artiste->setText(item->text());
}

void OngletPhys::afficherListeAlbum()
{

    QString Artiste=choixArtiste();

    afficherNomArtiste();
    QString Categorie=choixCategorie();
    ui->Albums->clear();
    ui->Singles->clear();
    ui->Compil->clear();

    //Affichage des albums
    QStringList albums = m_bddInterface.listeAlbumsPhys( Artiste, Categorie );
    for ( int compteurAlbums = 0; compteurAlbums < albums.count(); compteurAlbums++ )
    {
        AlbumGestion album = m_bddInterface.InfosAlbumPhys( albums[compteurAlbums] );

        //On s'occupe de la pochette
        QListWidgetItem *mediaCell=temp.afficherPochetteList(album.Pochette);
        //On s'occupe du nom de l'album
        mediaCell->setFlags(Qt::ItemIsEnabled );
        mediaCell->setText(album.Album);
        mediaCell->setData(Qt::UserRole,albums[compteurAlbums]);


        if (album.Type=="Album")
        {
            ui->Albums->addItem(mediaCell);

        } else if (album.Type=="Single"){

            ui->Singles->addItem(mediaCell);
        } else if (album.Type=="Compil")
        {
            ui->Compil->addItem(mediaCell);
        }

    }
    //On sélectionne la première catégorie
    ui->Albums->item(0)->setSelected(true);
afficherInfosAlbum(ui->Albums->item(0));

}
void OngletPhys::afficherListeCompil()
{



}

void OngletPhys::on_Artistes_currentTextChanged(const QString &arg1)
{
    QString Categorie = choixCategorie();

    if (Categorie=="Compil")
    {
        afficherListeCompil();
    } else
    {
        afficherListeAlbum();
    }

}


void OngletPhys::on_Categories_currentTextChanged(const QString &currentText)
{
    if (ui->Categories->count()>1)
    {
        ui->Artistes->clear();
        QString Categorie = choixCategorie();

        if (Categorie=="Compil")
        {
            afficherListeAnnees();
            afficherListeCompil();
        } else {
            afficherListeArtiste();
            afficherListeAlbum();
        }

    }
}
void OngletPhys::afficherListeAnnees()
{
    AffichageCommun temp;
    //Categorie "Tout"
    QImage* image=new QImage("./Pochettes/def.jpg");
    QListWidgetItem* mediaCell=temp.afficherPochetteList(*image);
    //On s'occupe du nom de l'artiste
    mediaCell->setText("2013");
    ui->Artistes->addItem(mediaCell);
}

void OngletPhys::vider(QString Type)
{
    if (Type=="Artiste")
    {
        ui->Artistes->clear();
    }
    if (Type=="Categories")
    {
        ui->Categories->clear();
    }
    if (Type=="Albums")
    {
        ui->Albums->clear();
    }
}

void OngletPhys::afficherInfosAlbum(QListWidgetItem *item)
{
    QString Id_Album = item->data(Qt::UserRole).toString();

    AlbumGestion album = m_bddInterface.InfosAlbumPhys( Id_Album );

    ui->Annee->setText(album.Annee);
    ui->NomAlbum->setText(album.Album);
    ui->Pochette->setPixmap(temp.afficherPochetteLabel(album.Pochette));

  ui->Titres->clear();

    for (int cpt=0;cpt<album.titres.count();cpt++)
    {


 QString text = QString::number(album.titres[cpt].Num_Piste).rightJustified(2,'0')+" - "+album.titres[cpt].Titre.toUpper()+"("+album.titres[cpt].Duree+")";


        QListWidgetItem* mediaCell=new QListWidgetItem();
        mediaCell->setText(text);


     mediaCell->setFlags(Qt::ItemIsSelectable |  Qt::ItemIsEnabled);

     if (album.titres[cpt].TitreenMp3etPhys)
     {
        mediaCell->setCheckState(Qt::Checked);
     } else {
      mediaCell->setCheckState(Qt::Unchecked);

     }


    ui->Titres->addItem(mediaCell);


    }
}

void OngletPhys::on_Albums_itemClicked(QListWidgetItem *item)
{
   afficherInfosAlbum(item);
}

void OngletPhys::on_Singles_itemClicked(QListWidgetItem *item)
{
   afficherInfosAlbum(item);
}

void OngletPhys::on_Modifier_clicked()
{

    QString Categorie = choixCategorie();
    QString Id_Album = choixAlbum();
    AlbumGestion album = m_bddInterface.InfosAlbumPhys(Id_Album);
    album.Id_Album= Id_Album.toInt();
    QMessageBox clickedButton;
    clickedButton.setInformativeText("Voulez-vous supprimer ou modifier l'album?");
    clickedButton.setText("L'album "+album.Album.toUpper()+" de  "+album.Artiste+" a été sélectionné.");
    clickedButton.addButton("Modifier",QMessageBox::DestructiveRole);
    clickedButton.addButton("Supprimer",QMessageBox::AcceptRole);

    int ret = clickedButton.exec();

    switch (ret)
    {
    case 1 :
        //On supprime
        if (Categorie=="Compil")
        {
            m_bddInterface.SupprimerCompilPhys(Id_Album);

        } else
        {
            m_bddInterface.SupprimerAlbumPhys(Id_Album);

        }
           break;
    case 0 :
        DialogModifierAlbum temp(album,this);
        temp.exec();
       afficherListeAlbum();
        break;
    }

}

void OngletPhys::on_Artistes_itemDoubleClicked(QListWidgetItem *item)
{
    QString Art=choixArtiste();
    DialogChangerPochette dcp(Art.toInt(),this);
    dcp.exec();
m_bddInterface.ModifierPochArt(dcp.getId(),Art);
    afficherListeArtiste();
}
