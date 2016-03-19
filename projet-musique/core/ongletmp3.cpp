#include "ongletmp3.h"
#include "ui_ongletmp3.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddmp3.h"
#include "bddtype.h"
#include <algorithm>
#include <QDebug>
#include "modificationartistedialog.h"
#include <time.h>
#include <QFile>
#include <QFileInfo>
#include "dialogajouterphys.h"
#include "bddaffichermp3.h"
#include "util.h"
#include "modifieralbumdialog.h"

OngletMP3::OngletMP3( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::OngletMP3 ),
    m_lignestitres( 0 ),
    m_colonnetitre( 0 )

{
    ui->setupUi( this );
    ActualiserOnglet();

}
OngletMP3::~OngletMP3()
{
    delete ui;
}
void OngletMP3::ActualiserOnglet()
{
    afficherListeType();
    affichageartistes();
    afficheralbumsettitres();
    afficherMP3ouAlbum( "MP3" );
    afficherInfosTitre();
    ui->buttonBox->addButton( "Modifier", QDialogButtonBox::ActionRole );

    connect(ui->ArtistesAnnees,SIGNAL(activated(QModelIndex)),this,SLOT(on_ArtistesAnnees_clicked(QModelIndex)));
    connect(ui->Categories,SIGNAL(activated(QModelIndex)),this,SLOT(on_Categories_clicked(QModelIndex)));
    connect(ui->AlbumsTitres,SIGNAL(activated(QModelIndex)),this,SLOT(on_AlbumsTitres_clicked(QModelIndex)));
}

void OngletMP3::vider( QString Type )
{
    if ( Type == "Categories" )
    {
        ui->Categories->clear();
    }
    if ( Type == "Titre" )
    {
        ui->Piste->clear();
        ui->Titre->clear();
        ui->NomAlbum->clear();
        ui->NomArtiste->clear();
        ui->Pochette->clear();
        ui->Similaires->clear();
        ui->Mp3Phys->clear();
    }
    if ( Type == "Artiste" )
    {
        ui->ArtistesAnnees->clear();
    }
    if ( Type == "AlbMP3" )
    {
        ui->AlbumsTitres->clearSpans();
        ui->AlbumsTitres->clear();
        ui->Mp3Phys->clear();
    }
}
void OngletMP3::afficherListeType()
{
    ui->Categories->clear();
    QStringList types;
    types << "Tout" << "0";
    types << m_bddInterface.RecupererListeTypes( "MP3" ) ;

    QImage image( "./Pochettes/def.jpg" );

    for ( int cpt = 0; cpt < types.count(); cpt = cpt + 2 )
    {
        QPixmap scaled( QPixmap::fromImage( image ) );
        scaled = scaled.scaled( 150, 150 );
        QListWidgetItem* item = new QListWidgetItem;
        item->setIcon( QIcon( scaled ) );
        item->setData( Qt::UserRole, types[cpt + 1] );
        item->setText( types[cpt] );

        ui->Categories->addItem( item );
    }
    ui->Categories->setCurrentRow( 1 );
    m_categorie = 1;
}
//Affiche les albums selon l'artiste (ou les années) et la catégorie
void OngletMP3::afficheralbumsettitres()
{

    //Création du modèle pour le QTableView
    m_lignestitres = 0;
    m_colonnetitre = 0;

    //Récupération de la liste des albums
    QList<int> albums = m_bddInterface.listeAlbums( QString::number( m_artiste ), QString::number( m_categorie ) );
    ui->AlbumsTitres->setRowCount( albums.count() * 8 );
    ui->AlbumsTitres->setColumnCount( ( albums.count() == 0 ) ? 1 : ( ( albums.count() == 1 ) ? 3 : 4 ) );

    for ( int cpt = 0; cpt < albums.count(); cpt++ )
    {
        m_ajoutlignes = 1;
        //Pour chaque album...
        BDDAlbum* album = BDDAlbum::RecupererAlbum( albums[cpt] );

        if ( album->m_id > 0 )
        {
            if ( ( m_categorie != 2 && cpt > 0 ) || ( m_categorie == 2 && cpt % 2 == 0  && cpt > 0 ) )
            {

                // Ajout d'une ligne de séparation
                QTableWidgetItem* item = new  QTableWidgetItem;
                item->setBackground( Qt::black );
                ui->AlbumsTitres->setItem( m_lignestitres, 0, item );
                ui->AlbumsTitres->setSpan( m_lignestitres, m_colonnetitre, 1, 6 );
                ui->AlbumsTitres->setRowHeight( m_lignestitres, 1 );
                m_lignestitres++;

            }

            QTableWidgetItem* item = new QTableWidgetItem;
            //on affiche la pochette
            QPixmap scaled( QPixmap::fromImage( album->m_pochette->m_image ) );
            item->setIcon( QIcon( scaled ) );
            item->setTextAlignment( Qt::AlignCenter | Qt::AlignBottom );
            item->setData( Qt::UserRole, album->m_id );
            ui->AlbumsTitres->setSpan( m_lignestitres, m_colonnetitre, 5, 1 );
            ui->AlbumsTitres->setItem( m_lignestitres, m_colonnetitre, item );

            item = new QTableWidgetItem;
            //On s'occupe d'afficher le nom du titre de l'album
            item->setData( Qt::UserRole, album->m_id );
            item->setTextAlignment( Qt::AlignLeft );
            item->setText( QString::number( album->m_annee ) + " - " + album->m_nom );
            item->setFlags( Qt::ItemIsEnabled );
            ui->AlbumsTitres->setItem( m_lignestitres + 5, m_colonnetitre, item );
            //On appelle la fonction chargée d'afficher les titres
            afficherTitresAlbum( QString::number( album->m_id ), m_categorie, m_lignestitres );

            if ( m_categorie == 2 )
            {
                if ( cpt % 2 == 1 )
                {
                    m_colonnetitre = 0;
                    m_lignestitres += 7;
                }
                else
                {
                    m_colonnetitre = 2;
                }
            }
        }
        delete album;
        if ( cpt + 1 < albums.count() && m_categorie != 2 )
        {
            m_lignestitres += m_ajoutlignes;
        }
    }
    if ( m_categorie == 2 )
    {
        ui->AlbumsTitres->setColumnCount( 4 );
    }
    //On retaille tout à la fin
    ui->AlbumsTitres->setRowCount( m_lignestitres );
    ui->AlbumsTitres->setCurrentCell( 0, 1, QItemSelectionModel::Select );
    m_mp3 = 0;
    if ( ui->AlbumsTitres->currentItem() != NULL )
        m_mp3 = ui->AlbumsTitres->currentItem()->data( Qt::UserRole ).toInt();
}

void OngletMP3::afficherAlbumSelectionne()
{
    AlbumPhys alb = BDDAlbum::RecupAlbumEntite( m_album );

    ui->Titre->setText( alb.Album );
    ui->NomArtiste->setText( alb.Artiste );
    ui->NomAlbum->setText( QString::number( alb.Annee ) );

    QPixmap scaled( QPixmap::fromImage( alb.Poch ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );

    ui->Titres->clear();
    QPixmap mp3physoui( ":/Autres/Vrai" );
    QPixmap mp3physnon( ":/Autres/Faux" );

    //Affichage des Titres selon l'album
    if ( alb.titres.count() == 0 )
    {
        ui->Titres->addItem( "Pas d'album physique existant" );
    }

    for ( int i = 0; i < alb.titres.count(); i++ )
    {
        QListWidgetItem* item = new QListWidgetItem;
        TitresPhys titre = alb.titres[i];
        QString temp;
        temp = QString::number( titre.Num_Piste ).rightJustified( 2, '0' ) + " - " + titre.Titre + "(" + titre.Duree + ")";
        item->setText( temp );
        //On affiche l'icone si le mp3 existe aussi
        if ( titre.MP3Phys )
        {
            item->setIcon( QIcon( mp3physoui ) );

        }
        else
        {
            item->setIcon( QIcon( mp3physnon ) );
            item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsUserCheckable );
        }
        ui->Titres->addItem( item );
    }
}

void OngletMP3::afficherTitresAlbum( QString Album, int Cate, int row )
{
    int col = 1;
    int ligne = 0;

    QStringList titres = m_bddInterface.listeTitresAlbumMp3( Album, QString::number( Cate ) );

    int temp = titres.count() / 2;
    int maxcol = std::max( 2, ( temp + 6 - 1 ) / 6 );

    int maxlignes = temp / maxcol + ( temp % maxcol == 0 ? 0 : 1 );

    int nbcol = std::max( ui->AlbumsTitres->columnCount() + m_colonnetitre, maxcol + m_colonnetitre + 1 ) ;

    ui->AlbumsTitres->setColumnCount( nbcol );

    if( maxlignes != 6)
    {
        m_ajoutlignes = 0;
    }
    for ( int cpt = 0; cpt < titres.count(); cpt = cpt + 2 )
    {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setData( Qt::UserRole, titres[cpt + 1] );
        item->setText( titres[cpt] );
        item->setTextAlignment( Qt::AlignLeft | Qt::AlignBottom );
        ui->AlbumsTitres->setItem( row + ligne, m_colonnetitre + col, item );
        ligne++;
        if ( ligne == maxlignes && Cate != 2 )
        {
            ligne = 0;
            col++;
        }
    }
    if ( Cate != 2 )
    {
        m_lignestitres = std::max( row + 6, row + maxlignes );
    }
}
void OngletMP3::afficherInfosTitre()
{
    vider( "Titre" );

    BDDMp3* mp3 = BDDMp3::RecupererMp3( m_mp3 );

    ui->Piste->setText( QString::number( mp3->m_titre->m_num_piste ).rightJustified( 2, '0' ) + " - " );
    QString temp = mp3->m_titre->m_nom.toUpper() + "(" + mp3->m_titre->m_duree + ")";
    ui->Titre->setText( temp );

    ui->NomAlbum->setText( mp3->m_album->m_nom );
    ui->NomArtiste->setText( mp3->m_artiste->m_nom );

    if ( mp3->m_titre->m_mp3 && mp3->m_titre->m_phys )
        ui->Mp3Phys->setText( "Existe en MP3 et Phys" );

    QPixmap scaled( QPixmap::fromImage( mp3->m_album->m_pochette->m_image ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );

    Similaires( mp3->m_titre->m_id );
    delete mp3;

}
void OngletMP3::Similaires( const int id )
{
    //On récupère les titres similaires du titre sélectionné
    BDDTitre* titre = BDDTitre::RecupererTitre( id );
    QList<int> Simi = titre->Similaires( id );
    //On affiche chaque titre similaire
    for ( int i = 0; i < Simi.count(); i++ )
    {
        //On récupère les infos du titre similaire
        BDDMp3* mp3 = BDDMp3::RecupererMp3( Simi[i] );

        //On affiche les infos du titre dans un item
        QListWidgetItem* item = new QListWidgetItem;
        item->setData( Qt::UserRole, mp3->m_id );
        item->setText( QString::number( mp3->m_album->m_annee ) + " - " + mp3->m_titre->m_nom );
        item->setToolTip( mp3->m_titre->m_nom );
        item->setFlags( Qt::ItemIsEnabled );
        //On s'occupe de sa pochette
        QPixmap scaled( QPixmap::fromImage( mp3->m_album->m_pochette->m_image ) );
        item->setIcon( QIcon( scaled ) );

        ui->Similaires->addItem( item );
        delete mp3;
    }
}
void OngletMP3::affichageartistes()
{
    vider( "Artiste" );
    int aleatoire = 0;
    if ( m_categorie != 2 )
    {
        //On récupère la liste des artistes
        QList<int> artistes = m_bddInterface.ListeArtiste( QString::number( m_categorie ) );
        for ( int cpt = 0; cpt < artistes.count(); cpt++ )
        {
            BDDArtiste* artiste = BDDArtiste::RecupererArtiste( artistes[cpt] );
            if ( artiste->m_id > 0 )
            {
                QListWidgetItem* item = new  QListWidgetItem;
                QPixmap scaled( QPixmap::fromImage( artiste->m_pochette->m_image ) );
                scaled = scaled.scaled( 100, 100 );
                item->setIcon( QIcon( scaled ) );
                //On s'occupe du nom de l'artiste
                item->setData( Qt::UserRole, artistes[cpt] );
                item->setText( artiste->m_nom );
                ui->ArtistesAnnees->addItem( item );
            }
            delete artiste;
        }
        srand( time( NULL ) );
        aleatoire = ( rand() % ( artistes.count() - 0 + 1 ) ) + 0;
    }
    else
    {
        afficherListeAnnees();
    }
    ui->ArtistesAnnees->setCurrentRow( aleatoire );
    m_artiste = ui->ArtistesAnnees->currentItem()->data( Qt::UserRole ).toInt();

}
void OngletMP3::afficherListeAnnees()
{
    BDDPoch* poch = BDDPoch::recupererBDD( 1 );

    QStringList ListeAnnees;
    ListeAnnees << "Avant 1980" << "1980-1989" << "1990-1999" << "2000-2004" << "2005-2009" << "2010-2014" << "2015-2019";
    for ( int cpt = 0; cpt < ListeAnnees.count(); cpt++ )
    {
        QListWidgetItem* item = new  QListWidgetItem;
        QPixmap scaled( QPixmap::fromImage( poch->m_image ) );
        scaled = scaled.scaled( 100, 100 );
        item->setIcon( QIcon( scaled ) );
        //On s'occupe d'afficher la liste de l'année en cours
        item->setData( Qt::UserRole, cpt );
        item->setText( ListeAnnees[cpt] );

        ui->ArtistesAnnees->addItem( item );
    }
    ui->ArtistesAnnees->setCurrentRow( 0 );
    m_artiste = ui->ArtistesAnnees->currentItem()->data( Qt::UserRole ).toInt();;

}
void OngletMP3::on_AlbumsTitres_doubleClicked( const QModelIndex& index )
{
    if ( !index.data(Qt::UserRole).isNull() )
    {
        m_mp3 = index.data( Qt::UserRole ).toInt();
        BDDMp3* mp3 = BDDMp3::RecupererMp3( m_mp3 );
        QFileInfo fich( mp3->m_chemin );
        QString nouvelemplacementchemin = "C:\\Users\\Nico\\Desktop\\Nouveau Dossier\\" + fich.fileName();
        QFile::copy( mp3->m_chemin, nouvelemplacementchemin );
    }
}
void OngletMP3::on_buttonBox_clicked( QAbstractButton* button )
{
    if ( button->text() == "Enregistrer" )
    {
        DialogAjouterPhys ajoutphys( m_album, this );
        ajoutphys.exec();
    }
    if ( button->text() == "Modifier" )
    {
        ModifierAlbumDialog mod( m_album, this );
        mod.exec();
    }
}

void OngletMP3::on_ArtistesAnnees_doubleClicked( const QModelIndex& index )
{
    m_artiste = index.data( Qt::UserRole ).toInt();
    BDDArtiste* artiste = BDDArtiste::RecupererArtiste( m_artiste );
    ModificationArtisteDialog temp( artiste, this );
    temp.exec();
    vider( "Artiste" );
    affichageartistes();
}
void OngletMP3::afficherMP3ouAlbum( const QString& MouA )
{
    if ( MouA == "Album" )
    {
        ui->Sur->setText( "Annee :" );
        ui->Play->setVisible( false );
        ui->Simi->setVisible( false );
        ui->TitresAlb->setVisible( true );
        ui->Piste->setText( " " );
    }
    else
    {
        ui->Sur->setText( "sur : " );
        ui->TitresAlb->setVisible( false );
        ui->Simi->setVisible( true );
        ui->Play->setVisible( true );

    }
}

void OngletMP3::on_Categories_clicked( const QModelIndex& index )
{
    m_categorie = index.data( Qt::UserRole ).toInt();
    affichageartistes();
}

void OngletMP3::on_ArtistesAnnees_clicked( const QModelIndex& index )
{
    m_artiste = index.data( Qt::UserRole ).toInt();
    vider( "AlbMP3" );
    afficheralbumsettitres();
}

void OngletMP3::on_AlbumsTitres_clicked( const QModelIndex& index )
{

    if ( index.column() != 0 )
    {
        if ( !index.data(Qt::UserRole).isNull() )
        {
            vider( "Titres" );
            m_mp3 = index.data( Qt::UserRole ).toInt();
            afficherMP3ouAlbum( "MP3" );
            afficherInfosTitre();
        }
    }
    else

    {
        m_album = index.data( Qt::UserRole ).toInt();
        afficherMP3ouAlbum( "Album" );
        afficherAlbumSelectionne();
    }

}
void OngletMP3::on_Similaires_clicked(const QModelIndex &index)
{
    BDDMp3* mp3 = BDDMp3::RecupererMp3( index.data( Qt::UserRole ).toInt() );

    //On selectionne la bonne categorie
    m_categorie = mp3->m_type->m_id;
    for (int i = 0; i<ui->Categories->count(); i++)
    {
        if ( ui->Categories->item(i)->data( Qt::UserRole).toInt() == m_categorie)
        {
            ui->Categories->setCurrentRow( i );
        }
    }
    affichageartistes();
    vider("AlbMP3");
    //On sélectionne le bon artiste/la bonne année
    if ( m_categorie != 2 )
    {
        m_artiste = mp3->m_artiste->m_id;

    } else
    {
        m_artiste = CompilsAnnees( mp3->m_album->m_annee );
    }
    for (int i = 0; i<ui->ArtistesAnnees->count(); i++)
    {
        if ( ui->ArtistesAnnees->item(i)->data( Qt::UserRole).toInt() == m_artiste)
        {
            ui->ArtistesAnnees->setCurrentRow( i );
        }
    }
    afficheralbumsettitres();

    //On sélection l'album et le titre
    m_album =  mp3->m_album->m_id;
    m_mp3 = mp3->m_titre->m_id;

    for (int row = 0; row<ui->AlbumsTitres->rowCount() ; row++)
    {
        for (int col = 1; col< ui->AlbumsTitres->columnCount(); col++ )
        {

            QTableWidgetItem* item = ui->AlbumsTitres->item(row,col);

            if ( item!= NULL)
            {
                if (item->data(Qt::UserRole).toInt() == m_mp3)
                {
                    ui->AlbumsTitres->setCurrentCell(row,col);
                }
            }
        }
    }
    vider("Titre");
    afficherInfosTitre();

}
int OngletMP3::CompilsAnnees(int annee)
{
    if ( annee < 1980 )
    {
        return 0;
    }
    if ( annee >=1980  && annee <1990)
    {
        return 1;
    }
    if ( annee >=1990 && annee <2000 )
    {
        return 2;
    }
    if ( annee >=2000 && annee < 2005 )
    {
        return 3;
    }
    if ( annee >=2005 && annee <2010)
    {
        return 5;
    }
    if ( annee >=2010 && annee<2015 )
    {
        return 6;
    }
}
