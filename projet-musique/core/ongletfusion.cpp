#include "ongletfusion.h"
#include "ui_ongletfusion.h"
#include "bddartiste.h"
#include "bddpoch.h"
#include "bddalbum.h"
#include <QDebug>
#include "util.h"
#include "MyQLabel.h"
#include "bddfusion.h"

OngletFusion::OngletFusion(QWidget *parent) :
    QWidget(parent),
    nb_passage( 0),
    ui(new Ui::OngletFusion)
{
    ui->setupUi(this);
    InitialiserWidget();

}

OngletFusion::~OngletFusion()
{
    delete ui;
}

void OngletFusion::on_Ok_clicked()
{
    m_donnee = ui->Donnee->text();
    nb_passage=0;
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
        item->setData( Qt::UserRole, artiste->id() );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( artiste->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->ChoixFusions->addItem( item );
        delete artiste;
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
        item->setData( Qt::UserRole, alb->id() );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );
        ui->ChoixFusions->addItem( item );
        delete alb;
    }
    nb_passage++;
}
void OngletFusion::Choix(QString id)
{
    if ( nb_passage%2==0)
    {
        m_choix2 = id;
        AfficherChoix2();
    } else
    {
        m_choix1 = id;
        AfficherChoix1();
    }
    nb_passage ++;

}
void OngletFusion::InitialiserWidget()
{
    ui->Choix1->setEnabled( true );

    connect( ui->Choix2_Pochette,SIGNAL( clic() ),this,SLOT( Pochette2() ) );
    connect( ui->Choix1_Pochette,SIGNAL( clic() ),this,SLOT( Pochette1() ) ) ;
    connect( ui->Choix1_Album,SIGNAL( clic() ),this,SLOT( Album1() ) ) ;
    connect( ui->Choix2_Album,SIGNAL( clic() ),this,SLOT( Album2() ) ) ;
    connect( ui->Choix1_Annee,SIGNAL( clic() ),this,SLOT( Annee1() ) ) ;
    connect( ui->Choix2_Annee,SIGNAL( clic() ),this,SLOT( Annee2() ) ) ;


}
void OngletFusion::Pochette1()
{
    QPixmap scaled( QPixmap::fromImage( Choix1_Pochette.first ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Choix_Pochette->setPixmap( scaled );

    ChoixFusion_Pochette = 1;
}
void OngletFusion::Album1()
{
    ui->Choix_Album->setText( Choix1_Album.first );

    ChoixFusion_Album = 1;
}
void OngletFusion::Album2()
{
    ui->Choix_Album->setText( Choix2_Album.first );

    ChoixFusion_Album = 2;
}
void OngletFusion::Annee1()
{
    ui->Choix_Annee->setText( Choix1_Annee );

    ChoixFusion_Annee = Choix1_Annee.toInt();

}
void OngletFusion::Annee2()
{
    ui->Choix_Annee->setText( Choix2_Annee );

    ChoixFusion_Annee = Choix2_Annee.toInt() ;

}
void OngletFusion::AfficherChoix1()
{
    //On affiche le premier choix
    AlbumPhys alb = BDDAlbum::RecupAlbumEntite( m_choix1.toInt() );


    ui->Choix1_Album->setText( alb.Album );
    Choix1_Album.first=alb.Album;
    Choix1_Album.second = QString::number( alb.Id_Album );
    ui->Choix1_Annee->setText( QString::number ( alb.Annee ) );
    Choix1_Annee = QString::number( alb.Annee );

    QPixmap scaled( QPixmap::fromImage( alb.Poch ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Choix1_Pochette->setPixmap( scaled );
    Choix1_Pochette.first = alb.Poch;
    Choix1_Pochette.second = QString::number( alb.Id_Poch );

    ui->Choix1_Titres->clear();

    QPixmap mp3 (":/Autres/Mp3");
    mp3.scaled( 50,50);
    QPixmap phys (":/Autres/Phys");
    phys.scaled( 50,50);

    Choix1_Titres.clear();

    //Affichage des Titres selon l'album
    if ( alb.titres.count() == 0 )
    {
        ui->Choix1_Titres->addItem( "Pas d'album physique existant" );
    }

    for ( int i = 0; i < alb.titres.count(); i++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        TitresPhys titre = alb.titres[i];
        QString temp;
        temp =  titre.Titre + "(" + titre.Duree + ")";
        item->setText( temp );
        temp = "C1_" + QString::number( i );
        item->setData(Qt::UserRole, temp );

        Choix1_Titres << titre;

        //On affiche l'icone si le mp3 existe aussi
        if ( titre.MP3 )
        {
            ui->Choix1_Mp3Phys->setPixmap( mp3);

        }
        else if ( titre.Phys)
        {
            ui->Choix1_Mp3Phys->setPixmap( phys);

        }
        ui->Choix1_Titres->addItem( item );
    }
}
void OngletFusion::AfficherChoix2()
{
    QPixmap mp3 (":/Autres/Mp3");
    QPixmap phys (":/Autres/Phys");
    mp3.scaled(30,30);
    phys.scaled(30,30);

    Choix2_Titres.clear();
    //On affiche le deuxième choix

    AlbumPhys alb = BDDAlbum::RecupAlbumEntite( m_choix2.toInt() );

    ui->Choix2_Album->setText( alb.Album );

    Choix2_Album.first=alb.Album;
    Choix2_Album.second = QString::number( alb.Id_Album );
    ui->Choix2_Annee->setText( QString::number ( alb.Annee ) );
    Choix2_Annee = QString::number( alb.Annee );


    QPixmap scaled( QPixmap::fromImage( alb.Poch ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Choix2_Pochette->setPixmap( scaled );
    Choix2_Pochette.first = alb.Poch;
    Choix2_Pochette.second = QString::number( alb.Id_Poch );

    ui->Choix2_Titres->clear();



    //Affichage des Titres selon l'album
    if ( alb.titres.count() == 0 )
    {
        ui->Choix2_Titres->addItem( "Pas d'album physique existant" );
    }

    for ( int i = 0; i < alb.titres.count(); i++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        TitresPhys titre = alb.titres[i];
        QString temp;
        temp =  titre.Titre + "(" + titre.Duree + ")";
        item->setText( temp );
        ui->Choix2_Titres->addItem( item );
        temp = "C2_" + QString::number( i );
        item->setData(Qt::UserRole, temp );

        Choix2_Titres << titre;
        //On affiche l'icone si le mp3 existe aussi
        if ( titre.MP3 )
        {
            ui->Choix2_Mp3Phys->setPixmap( mp3);

        }
        else if ( titre.Phys)
        {
            ui->Choix2_Mp3Phys->setPixmap( phys);

        }

    }
}

void OngletFusion::Pochette2()
{
    QPixmap scaled( QPixmap::fromImage( Choix2_Pochette.first ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Choix_Pochette->setPixmap( scaled );

    ChoixFusion_Pochette = 2;
}

void OngletFusion::on_Supprimer_clicked()
{
    QList<QListWidgetItem*> fileSelected = ui->Choix_Titres->selectedItems();
    if ( fileSelected.size() )
    {
        for ( int i = ui->Choix_Titres->count() - 1 ; i >= 0 ; i-- )
        {
            if ( ui->Choix_Titres->item( i )->isSelected() )
            {
                QListWidgetItem* item = ui->Choix_Titres->takeItem( i );
                ui->Choix_Titres->removeItemWidget( item );
            }
        }
    }
    ListeNumeros();
}

void OngletFusion::on_Choix1_Titres_clicked(const QModelIndex &index)
{
    if ( !index.data(Qt::UserRole).isNull() )
    {
        QString titreatrouver = index.data(Qt::UserRole).toString();

        QStringList splittitre = titreatrouver.split("_");

        int nb=  splittitre[1].toInt();

        QListWidgetItem* item = new QListWidgetItem;
        TitresPhys titre =  Choix1_Titres[nb];
        QString temp;
        temp =  titre.Titre + "(" + titre.Duree + ")";
        item->setText( temp );
        temp = index.data(Qt::UserRole).toString();
        item->setData(Qt::UserRole, temp );
        ui->Choix_Titres->addItem( item );
    }
    ListeNumeros();

}

void OngletFusion::on_Choix2_Titres_clicked(const QModelIndex &index)
{

    if ( !index.data(Qt::UserRole).isNull() )
    {
        QString titreatrouver = index.data(Qt::UserRole).toString();

        QStringList splittitre = titreatrouver.split("_");

        int nb=  splittitre[1].toInt();

        QListWidgetItem* item = new QListWidgetItem;
        TitresPhys titre =  Choix2_Titres[nb];
        QString temp;
        temp =    titre.Titre + "(" + titre.Duree + ")";
        item->setText( temp );
        temp = index.data(Qt::UserRole).toString();
        item->setData(Qt::UserRole, temp );
        ui->Choix_Titres->addItem( item );
    }
    ListeNumeros();
}
void OngletFusion::ListeNumeros()
{
    ui->Num_Pistes->clear();
    for ( int i = 1; i < ui->Choix_Titres->count() + 1; i++ )
    {
        ui->Num_Pistes->addItem( new QListWidgetItem( QString::number( i ).rightJustified( 2, '0' ) + " - " ) );
    }

}


void OngletFusion::on_buttonBox_accepted()
{
    //On fusionne

    for ( int i=0; i< ui->Choix_Titres->count();i++ )
    {
        ChoixFusion_Titres <<  ui->Choix_Titres->item(i)->data(Qt::UserRole).toString();

    }

    BDDFusion temp(this);

    temp.fusionalbums(Choix1_Album,Choix1_Pochette,  Choix1_Titres , Choix2_Album, Choix2_Pochette,  Choix2_Titres , ChoixFusion_Annee, ChoixFusion_Album, ChoixFusion_Pochette, ChoixFusion_Titres);
}
