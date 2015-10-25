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
#include "lecteur.h"
#include <time.h>
#include <QFile>
#include <QFileInfo>

OngletMP3::OngletMP3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletMP3),
    m_albumtitres(new QStandardItemModel),
    m_lignestitres(0),
    m_artistes(new QStandardItemModel),
    m_colonnetitre(0),
    m_player(new Lecteur)
{
    ui->setupUi(this);
    afficherListeType();
    ui->ArtistesAnnees->setModel(&m_artistes);
    affichageartistes();
    ui->AlbumsTitres->setModel(&m_albumtitres);
    afficheralbumsettitres();
    afficherInfosTitre();
    ui->widget->setParentTab(*this);

    connect(ui->ArtistesAnnees->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(on_ArtistesAnnees_clicked(QModelIndex)));
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
    Q_UNUSED(index);
    afficheralbumsettitres();
}
void OngletMP3::on_AlbumsTitres_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    vider ("Titres");
    afficherInfosTitre();
}
void OngletMP3::on_Categories_currentRowChanged(int currentRow)
{
    Q_UNUSED(currentRow);
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
        ui->Mp3Phys->clear();
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
//Affiche les albums selon l'artiste (ou les années) et la catégorie
void OngletMP3::afficheralbumsettitres()
{
    //Création du modèle pour le QTableView
    m_lignestitres=0;
    m_albumtitres.clear();
    m_colonnetitre=0;
    //Choix de l'Artiste des Albums à afficher
    QString Artiste=choixArtiste();
    QString Cate=choixCategories();
    //Récupération de la liste des albums
    QList<int> albums=m_bddInterface.listeAlbums(Artiste,Cate);
    m_albumtitres.setRowCount(albums.count()*6);
    m_albumtitres.setColumnCount(1);

    for (int cpt=0;cpt<albums.count();cpt++)
    {
        //Pour chaque album...
        BDDAlbum* album= BDDAlbum::RecupererAlbum(albums[cpt]);

        if (album->m_id>0)
        {
            if ( (Cate.toInt()!=2 && cpt > 0) || ( Cate.toInt()==2 && cpt%2==0 && cpt > 0 ) )
            {

                // Ajout d'une ligne de séparation
                QStandardItem* item= new QStandardItem;
                item->setBackground( Qt::black );
                m_albumtitres.setItem(m_lignestitres,0,item);
                ui->AlbumsTitres->setSpan(m_lignestitres,m_colonnetitre,1,6);
                ui->AlbumsTitres->setRowHeight( m_lignestitres, 1 );
                m_lignestitres++;

            }

            QStandardItem* item= new QStandardItem;
            //on affiche la pochette
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );
            item->setIcon( QIcon( scaled ) );
            item->setTextAlignment(Qt::AlignCenter | Qt::AlignBottom);

            m_albumtitres.setItem(m_lignestitres,m_colonnetitre,item);
            ui->AlbumsTitres->setSpan(m_lignestitres,m_colonnetitre,4,1);

            item= new QStandardItem;
            //On s'occupe d'afficher le nom du titre de l'album
            item->setData( Qt::UserRole, albums[cpt] );
            item->setTextAlignment(Qt::AlignLeft);
            item->setText( QString::number(album->m_annee)+" - "+album->m_nom );
            item->setFlags(  Qt::ItemIsEnabled );
            m_albumtitres.setItem(m_lignestitres+4,m_colonnetitre,item);
            //On appelle la fonction chargée d'afficher les titres
            afficherTitresAlbum(QString::number(album->m_id),Cate,m_lignestitres);
            if (Cate.toInt()==2 )
            {
                if(cpt%2==1 && cpt>0)
                {
                    m_colonnetitre=0;
                    m_lignestitres += 6;
                }
                else
                {
                    m_colonnetitre=3;
                }
            }
        }
        delete album;


    }
    if (Cate.toInt()==2)
    {
        m_albumtitres.setColumnCount(6);
    }
    //On retaille tout à la fin
    m_albumtitres.setRowCount(m_lignestitres);
    ui->AlbumsTitres->setCurrentIndex(m_albumtitres.index(0,1));
    on_AlbumsTitres_clicked(m_albumtitres.index(0,1));

}
void OngletMP3::afficherTitresAlbum(QString Album,QString Cate,int row)
{
    int col=1;int ligne=0;

    QStringList titres=m_bddInterface.listeTitresAlbumMp3(Album,Cate);

    int temp= titres.count()/2;
    int maxcol=std::max(2,(temp+6-1)/6);

    int maxlignes=temp/maxcol+(temp%maxcol==0?0:1);

    m_albumtitres.setColumnCount(std::max(m_albumtitres.columnCount()+m_colonnetitre,maxcol+m_colonnetitre));

    for (int cpt=0;cpt<titres.count();cpt=cpt+2)
    {
        QStandardItem* item= new QStandardItem;
        item->setData(titres[cpt+1],Qt::UserRole);
        item->setText(titres[cpt]);
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignBottom);
        m_albumtitres.setItem(row+ligne,m_colonnetitre+col,item);
        ligne++;
        if (ligne==maxlignes)
        {
            ligne=0;
            col++;
        }
    }
    if (Cate.toInt()!=2/*||m_colonnetitre!=3*/)
    {
        m_lignestitres=std::max(row+5,row+maxlignes);
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
    int aleatoire=0;
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
        srand(time(NULL));

        aleatoire= (rand() % (artistes.count() - 0 + 1)) + 0;
    } else
    {
        afficherListeAnnees();

    }
    ui->ArtistesAnnees->setCurrentIndex(m_artistes.index(aleatoire,0));
}
void OngletMP3::afficherListeAnnees()
{
    BDDPoch* poch= BDDPoch::recupererBDD(1);

    QStringList ListeAnnees;
    ListeAnnees << "Avant 1980" <<"1980-1989"<< "1990-1999" << "2000-2004" << "2005-2009" << "2010-2014" <<"2015-2019";
    for (int cpt=0;cpt<ListeAnnees.count();cpt++) {

        QStandardItem* item= new QStandardItem;

        QPixmap scaled( QPixmap::fromImage( poch->m_image ) );
        scaled = scaled.scaled( 100, 100 );
        item->setIcon( QIcon( scaled ) );

        //On s'occupe d'afficher la liste de l'année en cours
        item->setData(ListeAnnees[cpt],Qt::UserRole);
        item->setText(ListeAnnees[cpt]);

        m_artistes.setItem(cpt,item);
    }
}
int OngletMP3::titreLecteur() const
{

    QModelIndex index= ui->AlbumsTitres->currentIndex();

    return index.data(Qt::UserRole).toInt();


}
QString OngletMP3::artisteLecteur() const
{
    QModelIndex index = ui->ArtistesAnnees->currentIndex();

    return index.data(Qt::UserRole).toString();
}

void OngletMP3::on_AlbumsTitres_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    BDDMp3* mp3 = BDDMp3::RecupererMp3( choixMp3().toInt() );
    QFileInfo fich(mp3->m_chemin);
    QString nouvelemplacementchemin= "C:\\Users\\Nico\\Desktop\\Nouveau Dossier\\"+fich.fileName();
    QFile::copy(mp3->m_chemin,nouvelemplacementchemin);
}

