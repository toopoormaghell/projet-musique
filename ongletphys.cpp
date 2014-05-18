#include "ongletphys.h"
#include "ui_ongletphys.h"
#include <QDebug>
#include "affichagecommun.h"
#include "QMessageBox"
OngletPhys::OngletPhys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletPhys)
{
    ui->setupUi(this);
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
    for (int cpt=0;cpt<artistes.count();cpt=cpt+2) {
        //On s'occupe de la pochette
        QImage image=m_bddInterface.afficherPochette(artistes[cpt+1],"Artiste");
        QListWidgetItem *mediaCell = temp.afficherPochetteList(&image);
        //On s'occupe du nom de l'artiste et de son Id caché
        mediaCell->setData(Qt::UserRole,artistes[cpt+1]);
        mediaCell->setText(artistes[cpt]);
        //On affiche le tout
        ui->Artistes->addItem(mediaCell);
    }
    ui->Artistes->item(0)->setSelected(true);
}
void OngletPhys::afficherListeCategories()
{
    //   ui->Categories->clear();
    AffichageCommun temp;
    //Categorie "Tout"
    QImage* image=new QImage("./Pochettes/def.jpg");
    QListWidgetItem* mediaCell=temp.afficherPochetteList(image);
    //On s'occupe du nom de l'artiste
    mediaCell->setText("Tout");
    ui->Categories->addItem(mediaCell);
    //On s'occupe des autres catégories
    QStringList categories=m_bddInterface.listeCategoriesPhys();
    for (int cpt=0;cpt<categories.count();cpt++) {
        mediaCell=temp.afficherPochetteList(image);
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
    return item->data(Qt::UserRole).toString();
}
void OngletPhys::afficherListeAlbum()
{
    ui->Albums->clear();
    QString Artiste=choixArtiste();
    QString Categorie=choixCategorie();
    const int Nb_Colonnes = 8;

    //on déclare un compteur
    int Ligne=0;
    int MaxLignes=0;
    int Colonne=0;
    QString categorieCourante;

    //Affichage des albums
    QStringList albums = m_bddInterface.listeAlbumsPhys( Artiste, Categorie );
    for ( int compteurAlbums = 0; compteurAlbums < albums.count(); compteurAlbums++ )
    {
        AlbumGestion album = m_bddInterface.InfosAlbumPhys( albums[compteurAlbums] );
        album.Id_Album = albums[compteurAlbums].toInt();
        if ( categorieCourante != album.Type )
        {
            Ligne = MaxLignes;
            ui->Albums->setRowCount(MaxLignes+1);

            QTableWidgetItem* Cell= new QTableWidgetItem;
            if ( album.Type == "Album" )
            {
                Cell->setText("ALBUMS");
            }
            else
            {
                Cell->setText("SINGLES");
            }
            Cell->setTextAlignment(Qt::AlignCenter);
            ui->Albums->setItem(Ligne, 0, Cell);
            ui->Albums->setSpan(Ligne, 0, 1, 8);

            categorieCourante = album.Type;
            Ligne++;
            Colonne=0;
        }

        if ( ( compteurAlbums / Nb_Colonnes > 0 ) && ( compteurAlbums % Nb_Colonnes == 0 ) )
        {
            Ligne = MaxLignes;
            Colonne = 0;
        }
        if ( MaxLignes < album.titres.count() + Ligne )
        {
            MaxLignes = album.titres.count() + 2 + Ligne;
            ui->Albums->setRowCount( MaxLignes );
        }
        AfficherAlbum( album, Colonne, Ligne );
        Colonne++;
    }
    //On redimensionne pour que les pochettes s'affichent correctement
    ui->Albums->resizeColumnsToContents();
    ui->Albums->resizeRowsToContents();

}
int OngletPhys::AfficherAlbum(AlbumGestion album, int Colonne, int Ligne)
{
    AffichageCommun temp;
    //Première chose à afficher: la pochette
    QTableWidgetItem *mediaCell=temp.afficherPochetteTable(&album.Pochette);
    mediaCell->setData(Qt::UserRole,album.Id_Album);
    ui->Albums->setItem(Ligne,Colonne,mediaCell);
    //On affiche le nom de l'album (en majuscule)
    QTableWidgetItem *cell=new QTableWidgetItem();
    cell->setData(Qt::UserRole,album.Id_Album);
    cell->setText(album.Album.toUpper());
    ui->Albums->setItem(Ligne+1,Colonne,cell);

    //On affiche les titres
    for(int i=0;i<album.titres.count();i++)
    {
        TitreGestion Titre=album.titres[i];
        QString temp=QString::number(Titre.Num_Piste).rightJustified(2,'0')+ " - " + Titre.Titre+ "(" +Titre.Duree+ ")";
        QTableWidgetItem *CellTitre=new QTableWidgetItem();
        CellTitre->setText(temp);
        CellTitre->setData(Qt::UserRole,album.Id_Album);
        ui->Albums->setItem(Ligne+2+i,Colonne,CellTitre);
    }
    return album.titres.count()+2+Ligne;
}

void OngletPhys::on_Artistes_currentTextChanged(const QString &arg1)
{
    afficherListeAlbum();
}

void OngletPhys::on_Categories_currentTextChanged(const QString &currentText)
{
    if (ui->Categories->count()>1)
    {
        ui->Artistes->clear();
        afficherListeArtiste();
        afficherListeAlbum();
    }
}

void OngletPhys::on_Albums_itemDoubleClicked(QTableWidgetItem *item)
{
    QString Id_Album = item->data(Qt::UserRole).toString();
    AlbumGestion album = m_bddInterface.InfosAlbumPhys(Id_Album);
    QMessageBox::StandardButton clickedButton = QMessageBox::information(0,"Confirmation","Etes-vous sûr de vouloir supprimer cet album:\n  "+album.Album.toUpper()+" de  "+album.Artiste+" ?",QMessageBox::Ok | QMessageBox::Cancel);
    if (clickedButton == QMessageBox::Ok)
    {
        m_bddInterface.SupprimerAlbumPhys(Id_Album);
    }
    afficherListeArtiste();
}

