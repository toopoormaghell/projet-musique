#include "ongletmp3.h"
#include "ui_ongletmp3.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddmp3.h"
#include "QDebug"

OngletMP3::OngletMP3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletMP3)
{
    ui->setupUi(this);
    afficherListeType();
}

OngletMP3::~OngletMP3()
{
    delete ui;
}

void OngletMP3::afficherListeType()
{
    ui->Categories->clear();

    QStringList types;
    types << "Tout" << "0";
    types <<m_bddInterface.RecupererListeTypes("MP3") ;

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

void OngletMP3::afficherListeArtiste()
{

    QString cat= choixCategories();

    //Affichage des artistes
    QList<int> artistes=m_bddInterface.ListeArtiste(cat);
    vider("Artiste");
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
void OngletMP3::afficherListeAlbum()
{
    //Choix de l'Artiste des Albums à afficher
    QString Artiste=choixArtiste();
    QString Cate=choixCategories();
    //Affichage des albums
    QList<int> albums=m_bddInterface.listeAlbums(Artiste,Cate);

    for (int cpt=0;cpt<albums.count();cpt++) {

        BDDAlbum* album= BDDAlbum::RecupererAlbum(albums[cpt]);
        //  BDDPoch const* pochette= album->m_pochette;

        if (album->m_id>0)
        {
            QListWidgetItem* item = new QListWidgetItem;
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );

            item->setIcon( QIcon( scaled ) );


            //On s'occupe du nom de l'artiste
            item->setData( Qt::UserRole, albums[cpt] );
            item->setText( QString::number(album->m_annee)+" - "+album->m_nom );
            item->setFlags(  Qt::ItemIsEnabled );
            ui->Albums->addItem( item );

            afficherTitresAlbum(QString::number(album->m_id),Cate);
        }
        delete album;

    }

    ui->Albums->setCurrentRow(1);
}
QString OngletMP3::choixCategories()
{
    QListWidgetItem *item=ui->Categories->currentItem();
    if (item==NULL)
    {
        item=ui->Categories->item(0);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}

QString OngletMP3::choixArtiste()
{
    QListWidgetItem *item=ui->Artistes->currentItem();
    if (item==NULL)
    {
        item=ui->Artistes->item(0);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}
void OngletMP3::on_Artistes_currentTextChanged(const QString &arg1)
{
    vider("Albums");
    afficherListeAlbum();
}
void OngletMP3::on_Albums_currentRowChanged(int currentRow)
{
    vider ("Titres");
    afficherInfosTitre();
}

void OngletMP3::vider(QString Type)
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
    if (Type=="Titres")
    {
        ui->Piste->clear();
        ui->Titre->clear();
        ui->NomAlbum->clear();
        ui->NomArtiste->clear();
        ui->Pochette->clear();
    }
}
void OngletMP3::afficherTitresAlbum(QString Album,QString Cate)
{
    QStringList titres=m_bddInterface.listeTitresAlbumMp3(Album,Cate);

    for (int cpt=0;cpt<titres.count();cpt=cpt+2)
    {
        QListWidgetItem *item=new QListWidgetItem();
        item->setData(Qt::UserRole,titres[cpt+1]);
        item->setText(titres[cpt]);
        ui->Albums->addItem(item);
    }

}
void OngletMP3::afficherInfosTitre()
{
    vider("Titre");
    if (choixMp3()!= NULL)
    {
        BDDMp3* mp3 = BDDMp3::RecupererMp3( choixMp3().toInt() );

        ui->Piste->setText(QString::number(mp3->m_titre->m_num_piste).rightJustified(2,'0')+" - ");
        QString temp=mp3->m_titre->m_nom.toUpper()+"("+mp3->m_titre->m_duree+")";
        ui->Titre->setText(temp);

        ui->NomAlbum->setText(mp3->m_album->m_nom);
        ui->NomArtiste->setText(mp3->m_artiste->m_nom);


        QPixmap scaled( QPixmap::fromImage( mp3->m_album->m_pochette->m_image  ) );
        scaled = scaled.scaled( 150, 150 );
        ui->Pochette->setPixmap(scaled);

        delete mp3;
    } else
    {
        vider("Titre");
    }

}
QString OngletMP3::choixMp3()
{
    QListWidgetItem *item=ui->Albums->currentItem();
    if (item==NULL)
    {
        item=ui->Albums->item(1);
    }

    return  item != NULL ? item->data(Qt::UserRole).toString() : QString();
}



void OngletMP3::on_Categories_currentRowChanged(int currentRow)
{
    vider("Artiste");
    afficherListeArtiste();
}
