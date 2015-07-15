#include "ongletmp3.h"
#include "ui_ongletmp3.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddmp3.h"
#include "QDebug"
#include <QStandardItemModel>
#include <algorithm>


OngletMP3::OngletMP3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletMP3),
    m_albumtitres(new QStandardItemModel),
    m_lignestitres(0),
    m_artistes(new QStandardItemModel)
{
    ui->setupUi(this);
    afficherListeType();
    ui->ArtistesAnnees->setModel(&m_artistes);
    affichageartistes();
    ui->AlbumsTitres->setModel(&m_albumtitres);

    afficheralbumsettitres();

}
OngletMP3::~OngletMP3()
{
    delete ui;
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
    QModelIndex index = ui->ArtistesAnnees->currentIndex();

    return index.data(Qt::UserRole).toString();

}
QString OngletMP3::choixMp3()
{
    QModelIndex index= ui->AlbumsTitres->currentIndex();

    return  index.data(Qt::UserRole).toString();
}

void OngletMP3::on_ArtistesAnnees_clicked(const QModelIndex &index)
{
    afficheralbumsettitres();
}
void OngletMP3::on_AlbumsTitres_clicked(const QModelIndex &index)
{
    vider ("Titres");
    afficherInfosTitre();
}
void OngletMP3::on_Categories_currentRowChanged(int currentRow)
{
    affichageartistes();
}

void OngletMP3::vider(QString Type)
{
    if (Type=="Categories")
    {
        ui->Categories->clear();
    }
    if (Type=="Titres")
    {
        ui->Piste->clear();
        ui->Titre->clear();
        ui->NomAlbum->clear();
        ui->NomArtiste->clear();
        ui->Pochette->clear();
        ui->Similaires->clear();
    }
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

void OngletMP3::afficheralbumsettitres()
{
    //Création du modèle pour le QTableView
    m_lignestitres=0;
    m_albumtitres.clear();
    //Choix de l'Artiste des Albums à afficher
    QString Artiste=choixArtiste();
    QString Cate=choixCategories();
    //Récupération de la liste des albums
    QList<int> albums=m_bddInterface.listeAlbums(Artiste,Cate);
    m_albumtitres.setRowCount(albums.count()*6);
    m_albumtitres.setColumnCount(1);

    for (int cpt=0;cpt<albums.count();cpt++) {
        //Pour chaque album...
        BDDAlbum* album= BDDAlbum::RecupererAlbum(albums[cpt]);

        if (album->m_id>0)
        {
            QStandardItem* item= new QStandardItem;
            //on affiche la pochette
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );

            item->setIcon( QIcon( scaled ) );
            item->setTextAlignment(Qt::AlignCenter | Qt::AlignBottom);
            m_albumtitres.setItem(m_lignestitres,0,item);
            ui->AlbumsTitres->setSpan(m_lignestitres,0,4,1);

            item= new QStandardItem;
            //On s'occupe d'afficher le nom du titre de l'album
            item->setData( Qt::UserRole, albums[cpt] );
            item->setText( QString::number(album->m_annee)+" - "+album->m_nom );
            item->setFlags(  Qt::ItemIsEnabled );
            item->setTextAlignment(Qt::AlignLeft | Qt::AlignTop);
            m_albumtitres.setItem(m_lignestitres+4,0,item);
            //On appelle la fonction chargée d'afficher les titres
            afficherTitresAlbum(QString::number(album->m_id),Cate,m_lignestitres);
        }
        delete album;

    }
    //On retaille tout à la fin
    m_albumtitres.setRowCount(m_lignestitres);

}
void OngletMP3::afficherTitresAlbum(QString Album,QString Cate,int row)
{
    int col=1;int ligne=0;

    QStringList titres=m_bddInterface.listeTitresAlbumMp3(Album,Cate);

    int temp= titres.count()/2;
    int maxcol=std::max(2,(temp+6-1)/6);

    int maxlignes=temp/maxcol+(temp%maxcol==0?0:1);
    m_lignestitres=std::max(row+5,row+maxlignes);
    m_albumtitres.setColumnCount(std::max(m_albumtitres.columnCount(),maxcol));

    for (int cpt=0;cpt<titres.count();cpt=cpt+2)
    {
        QStandardItem* item= new QStandardItem;
        item->setData(titres[cpt+1],Qt::UserRole);
        item->setText(titres[cpt]);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignBottom);
        m_albumtitres.setItem(row+ligne,col,item);
        ligne++;
        if (ligne==maxlignes)
        {
            ligne=0;col++;
        }
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

        if(mp3->m_titre->m_mp3etphys)
            ui->Mp3Phys->setText("Existe en MP3 et Phys");

        QPixmap scaled( QPixmap::fromImage( mp3->m_album->m_pochette->m_image  ) );
        scaled = scaled.scaled( 150, 150 );
        ui->Pochette->setPixmap(scaled);

        Similaires(mp3->m_titre->m_id);
        delete mp3;
    } else
    {
        vider("Titre");
    }
}
void OngletMP3::Similaires(const int id)
{
    //On récupère les titres similaires du titre sélectionné
    BDDTitre* titre = BDDTitre::RecupererTitre(id);
    QList<int> Simi = titre->Similaires( id);
    //On affiche chaque titre similaire
    for (int i =0;i<Simi.count();i++)
    {
        //On récupère les infos du titre similaire
        BDDMp3* mp3 = BDDMp3::RecupererMp3( Simi[i] );

        //On affiche les infos du titre dans un item
        QListWidgetItem* item = new QListWidgetItem;
        item->setData( Qt::UserRole, mp3->m_id );
        item->setText( QString::number(mp3->m_album->m_annee)+" - "+mp3->m_titre->m_nom );
        item->setToolTip(mp3->m_titre->m_nom);
        item->setFlags(  Qt::ItemIsEnabled );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( mp3->m_album->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );

        ui->Similaires->addItem(item);
        delete mp3;
    }
}


void OngletMP3::affichageartistes()
{
    m_artistes.clear();
    //On récupère la catégorie
    QString cat=choixCategories();

    if (cat!="2")
    {
       //On récupère la liste des artistes
        QList<int> artistes=m_bddInterface.ListeArtiste(cat);
        for (int cpt=0;cpt<artistes.count();cpt++)
        {
            BDDArtiste* artiste = BDDArtiste::RecupererArtiste( artistes[cpt] );

            if ( artiste->m_id > 0 )
            {
                QStandardItem* item= new QStandardItem;

                QPixmap scaled( QPixmap::fromImage( artiste->m_pochette->m_image ) );
                scaled = scaled.scaled( 100, 100 );
                item->setIcon( QIcon( scaled ) );


                //On s'occupe du nom de l'artiste
                item->setData(artistes[cpt],Qt::UserRole);
                item->setText( artiste->m_nom );

                m_artistes.setItem(cpt,item);

            }
            delete artiste;
        }
    } else
    {
       afficherListeAnnees();

    }
}
void OngletMP3::afficherListeAnnees()
{
    BDDPoch* poch= BDDPoch::recupererBDD(1);

    QStringList ListeAnnees;
    ListeAnnees << "Avant 1980" <<"1980-1990"<< "1990-2000" << "2000-2005" << "2005-2010" << "2010-2014" <<"2015-2020";
    for (int cpt=0;cpt<ListeAnnees.count();cpt++) {

        QStandardItem* item= new QStandardItem;

        QPixmap scaled( QPixmap::fromImage( poch->m_image ) );
        scaled = scaled.scaled( 100, 100 );
        item->setIcon( QIcon( scaled ) );

        //On s'occupe d'afficher la liste de l'année en cours
        item->setText(ListeAnnees[cpt]);

        m_artistes.setItem(cpt,item);
    }
}
