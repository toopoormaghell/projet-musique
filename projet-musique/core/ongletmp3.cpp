#include "ongletmp3.h"
#include "ui_ongletmp3.h"

#include <QFile>
#include <QFileInfo>
#include <algorithm>
#include <time.h>
#include "util.h"
#include <QDir>
#include <QInputDialog>
#include <QDebug>
#include <QWidget>

#include "bddaffichermp3.h"
#include "meta_album.h"
#include "meta_titre.h"
#include "meta_artiste.h"

#include "DialogModifierArtiste.h"
#include "dialogajouterphys.h"
#include "DialogModifierAlbum.h"
#include "bddlecteur.h"
#include "dialogajoutenplaylist.h"



OngletMP3::OngletMP3(QWidget* parent ) :
    QWidget( parent ),
    m_PlaylistLecteur ( ),
    m_fichierlu ( ),
    ui( new Ui::OngletMP3 ),
    m_bddInterface(),
    m_lignestitres( 0 ),
    m_lecteur(nullptr),
    m_colonnetitre( 0 ),
    m_ajoutlignes(0),
    m_categorie(0),
    m_mp3(0),
    m_album(0),
    m_artiste(0),
    m_couleur(),
    m_listemp3()
{
    ui->setupUi( this );

}
OngletMP3::~OngletMP3()
{
    delete ui;
}
void OngletMP3::appliquerstyle( QString stylecoul )
{
    setStyleSheet( stylecoul );
    update();

    ui->Simi->setStyleSheet( stylecoul );
    ui->Simi->update();

    ui->Play->setStyleSheet( stylecoul );
    ui->Play->update();


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

    on_Mode_Playlist_clicked( false );
}

void OngletMP3::suppplaylist(QStringList temp)
{
    m_PlaylistLecteur = temp;
}

void OngletMP3::vider( QString Type )
{
    if ( Type == "Categories" )
    {
        ui->Categories->clear();
    }
    if ( Type == "Titre" )
    {

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

    types << m_bddInterface.RecupererListeTypes() ;

   for ( int cpt = 0; cpt < types.count(); cpt = cpt + 2 )
    {
        QListWidgetItem* item = new QListWidgetItem;
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
    if ( m_artiste > 0  )
    {
        Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( m_artiste );
        ui->Artiste->setText( artiste->getNom_Artiste() );
        delete artiste;

        //Création du modèle pour le QTableView
        m_lignestitres = 0;
        m_colonnetitre = 0;

        //Récupération de la liste des albums
        QList<int> albums = m_bddInterface.listeAlbums( QString::number( m_artiste ), QString::number( m_categorie ) );
        ui->AlbumsTitres->setRowCount( albums.count() * 8 );
        ui->AlbumsTitres->setColumnCount( ( albums.count() == 0 ) ? 1 : ( ( albums.count() == 1 ) ? 3 : 4 ) );
        ui->AlbumsTitres->setColumnCount( 6 );
        for ( int cpt = 0; cpt < albums.count(); cpt++ )
        {
            m_ajoutlignes = 1;
            //Pour chaque album...
            Meta_Album* album = Meta_Album::RecupererBDD( albums[cpt] );

            m_album = album->getid_alb();

            if ( album->getid_alb() > 0 )
            {
                if ( (  cpt > 0 ) )
                {

                    // Ajout d'une ligne de séparation
                    QTableWidgetItem* item = new  QTableWidgetItem;
                    item->setBackground(QColor(m_couleur));
                    ui->AlbumsTitres->setItem( m_lignestitres, 0, item );
                    ui->AlbumsTitres->setSpan( m_lignestitres, m_colonnetitre, 1, ui->AlbumsTitres->columnCount() );
                    ui->AlbumsTitres->setRowHeight( m_lignestitres, 1 );
                    m_lignestitres++;

                }

                QTableWidgetItem* item = new QTableWidgetItem;
                //on affiche la pochette
                QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );
                item->setIcon( QIcon( scaled ) );
                item->setTextAlignment( Qt::AlignCenter | Qt::AlignBottom );
                item->setData( Qt::UserRole, album->getid_alb() );
                ui->AlbumsTitres->setSpan( m_lignestitres, m_colonnetitre, 5, 1 );
                ui->AlbumsTitres->setItem( m_lignestitres, m_colonnetitre, item );

                item = new QTableWidgetItem;
                //On s'occupe d'afficher le nom du titre de l'album
                item->setData( Qt::UserRole, album->getid_alb() );
                item->setTextAlignment( Qt::AlignLeft );
                item->setText( QString::number( album->getannee() ) + " - " + album->getnom_album() );
                item->setFlags( Qt::ItemIsEnabled );
                ui->AlbumsTitres->setItem( m_lignestitres + 5, m_colonnetitre, item );
                //On appelle la fonction chargée d'afficher les titres
                afficherTitresAlbum(  album->gettitres()  , m_categorie, m_lignestitres );

                m_lignestitres += 7;


            }
            delete album;


        }
        //On retaille tout à la fin
        ui->AlbumsTitres->setRowCount( m_lignestitres );
        ui->AlbumsTitres->setCurrentCell( 0, 1, QItemSelectionModel::Select );
        m_mp3 = 0;
        if ( ui->AlbumsTitres->currentItem() != nullptr )
            m_mp3 = ui->AlbumsTitres->currentItem()->data( Qt::UserRole ).toInt();
    }
}
void OngletMP3::afficherAlbumSelectionne()
{
    ui->Titres->clear();
    QPixmap mp3physoui( ":/Autres/Vrai" );
    QPixmap mp3physnon( ":/Autres/Faux" );

    Meta_Album* album= Meta_Album::RecupererBDD( m_album );

    ui->Titre->setText( album->getnom_album() );
    ui->NomArtiste->setText( album->getnom_artiste() );
    ui->Annee->setText( QString::number( album->getannee() ) );


    QPixmap scaled( QPixmap::fromImage( album->getPoch() ) );
    scaled = scaled.scaled( 100, 100 );
    ui->Pochette->setPixmap( scaled );

    if ( album->getid_support_p() != -1 )
    {
        ui->Mp3Phys->setText( "Existe en version physique.");
    } else
    {
        ui->Mp3Phys->setText("");
    }

    //Affichage des Titres selon l'album
    QList<Meta_Titre*> titres =  album->gettitres();

    if ( titres.count() == 0 )
    {
        ui->Titres->addItem( "Pas d'album existant" );
    }

    for ( int i = 0; i <  titres.count(); i++ )
    {

        QListWidgetItem* item = new QListWidgetItem;

        Meta_Titre* titre = titres[i];

        QString temp;
        temp = QString::number( titre->getnum_piste() ).rightJustified( 2, '0' ) + " - " + titre->getnom_titre() + "(" + titre->getduree() + ")";
        item->setText( temp );
        //On affiche l'icone si le mp3 existe aussi

        if ( titre->getsupportmp3() != "Aucun" )
        {
            item->setIcon( QIcon( mp3physoui ) );
        }
        else
        {
            item->setIcon( QIcon( mp3physnon ) );
            item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsUserCheckable );
        }
        ui->Titres->addItem( item );

        delete titre;
    }

    delete album;

}

void OngletMP3::afficherTitresAlbum( QList<Meta_Titre*> titres, int Cate, int row )
{
    int col = 1;
    int ligne = 0;
    Cate =1;
    int temp = 0;

    for ( int cpt = 0; cpt < titres.count(); cpt ++ )
    {
        if ( titres[cpt]->getsupportmp3() != "Aucun" && titres[cpt]->getsupportmp3() != "")
        {
            temp++;
        }
    }

    int maxcol = std::max( 2, ( temp + 6 - 1 ) / 6 );

    int maxlignes = temp / maxcol + ( temp % maxcol == 0 ? 0 : 1 );

    int nbcol = std::max( ui->AlbumsTitres->columnCount() + m_colonnetitre, maxcol + m_colonnetitre + 1 ) ;


    ui->AlbumsTitres->setColumnCount( nbcol );

    for ( int cpt = 0; cpt < titres.count(); cpt ++ )
    {
        if ( titres[cpt]->getsupportmp3() != "Aucun" )
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setData( Qt::UserRole, titres[cpt]->getid_relation() );
            QString texte =  QString::number( titres[cpt]->getnum_piste() ).rightJustified( 2, '0' ) + " - " + titres[cpt]->getnom_titre() + "(" + titres[cpt]->getduree() + ")";
            item->setText(  texte );
            item->setTextAlignment( Qt::AlignLeft | Qt::AlignBottom );
            ui->AlbumsTitres->setItem( row + ligne, m_colonnetitre + col, item );

            ligne++;
            if ( ligne == maxlignes && Cate != 2 )
            {
                ligne = 0;
                col++;
            }
        }
    }
    /*    if ( Cate != 2 )
    {
        m_lignestitres = std::max( row + 6, row + maxlignes );
    }
*/
}
void OngletMP3::afficherInfosTitre()
{
    vider( "Titre" );

    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( m_mp3 );

    if ( mp3->getcheminmp3() != "" )
    {


        QString temp = QString::number( mp3->getnum_piste() ).rightJustified( 2, '0' ) + " - " + mp3->getnom_titre().toUpper() + "(" + mp3->getduree() + ")";
        ui->Titre->setText( temp );

        ui->NomAlbum->setText( mp3->getnom_album() );
        ui->NomArtiste->setText( mp3->getnom_artiste() );

        ui->Annee->setText( QString::number( mp3->getannee() ) );

        if ( mp3->getsupportmp3() !="Aucun" && mp3->getsupportphys() != "Aucun" )
        {
            ui->Mp3Phys->setText( "Existe en version physique." );
        }

        QPixmap scaled( QPixmap::fromImage( mp3->getpoch() ) );
        scaled = scaled.scaled( 100, 100 );
        ui->Pochette->setPixmap( scaled );

        Similaires( mp3->getid_titre() );
        AfficherPlaylist( mp3->getid_relation() );
    }

    delete mp3;

}
void OngletMP3::afficherListeMp3()
{
    ui->Titres->clear();
    ui->AjouterAlbumPlaylist->setVisible( false );
    ui->AjoutListePlaylist->setVisible( true );

    QPixmap mp3physoui( ":/Autres/Vrai" );
    QPixmap mp3physnon( ":/Autres/Faux" );


    for (int i =0; i< m_listemp3.count(); i ++ )
    {
        Meta_Titre* titre = Meta_Titre::RecupererBDD( m_listemp3[i] );

        QListWidgetItem* item = new QListWidgetItem;

        QString temp;
        temp = QString::number( titre->getnum_piste() ).rightJustified( 2, '0' ) + " - " + titre->getnom_titre() + "(" + titre->getduree() + ")";
        item->setText( temp );
        //On affiche l'icone si le mp3 existe aussi

        if ( titre->getsupportmp3() != "Aucun" )
        {
            item->setIcon( QIcon( mp3physoui ) );
        }
        else
        {
            item->setIcon( QIcon( mp3physnon ) );
            item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsUserCheckable );
        }
        ui->Titres->addItem( item );

        delete titre;
    }
}
void OngletMP3::Similaires( const int id )
{
    QList<int> Simi = m_bddInterface.RecupererSimilaires( id );

    Meta_Titre* mp3ensimi = Meta_Titre::RecupererBDD( m_mp3 );

    //On affiche chaque titre similaire
    for ( int i = 0; i < Simi.count(); i++ )
    {
        //On récupère les infos du titre similaire
        Meta_Titre* mp3 = Meta_Titre::RecupererBDD( Simi[i]);

        if ( mp3ensimi->getid_relation() != mp3->getid_relation() )
        {
            //On affiche les infos du titre dans un item
            QListWidgetItem* item = new QListWidgetItem;
            item->setData( Qt::UserRole, mp3->getid_relation() );
            item->setText( QString::number( mp3->getannee() ) + " - " + mp3->getnom_titre() );
            item->setToolTip( mp3->getnom_titre() );
            item->setFlags( Qt::ItemIsEnabled );
            //On s'occupe de sa pochette
            QPixmap scaled( QPixmap::fromImage( mp3->getpoch() ) );
            item->setIcon( QIcon( scaled ) );

            ui->Similaires->addItem( item );

        }
        delete mp3;
    }
    delete mp3ensimi;

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
            Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( artistes[cpt] );
            if ( artiste->get_id_artiste() > 0 )
            {
                QListWidgetItem* item = new  QListWidgetItem;
                QPixmap scaled( QPixmap::fromImage( artiste->getPoch() ) );
                scaled = scaled.scaled( 85, 85 );
                item->setIcon( QIcon( scaled ) );
                //On s'occupe du nom de l'artiste
                item->setData( Qt::UserRole, artiste->get_id_artiste() );
                item->setText( artiste->getNom_Artiste() );
                ui->ArtistesAnnees->addItem( item );
            }

            delete artiste;
        }
        srand( static_cast<unsigned int>(time( nullptr )) );
        aleatoire = ( rand() % ( artistes.count() - 0 + 1 ) ) + 0;
        aleatoire = 0;
    }
    else
    {
        afficherListeAnnees();
    }
    ui->ArtistesAnnees->setCurrentRow( aleatoire );

    if ( ui->ArtistesAnnees->currentItem() != nullptr )

        m_artiste = ui->ArtistesAnnees->currentItem()->data( Qt::UserRole ).toInt();

}
void OngletMP3::afficherListeAnnees()
{
    QImage image( "./Pochettes/def.jpg" );

    QStringList ListeAnnees;
    ListeAnnees << "Avant 1980" << "1980-1989" << "1990-1999" << "2000-2009" <<  "2010-2014" << "2015-2019";
    for ( int cpt = 0; cpt < ListeAnnees.count(); cpt++ )
    {
        QListWidgetItem* item = new  QListWidgetItem;
        QPixmap scaled( QPixmap::fromImage( image ) );
        scaled = scaled.scaled( 85, 85 );
        item->setIcon( QIcon( scaled ) );
        //On s'occupe d'afficher la liste de l'année en cours
        item->setData( Qt::UserRole, cpt );
        item->setText( ListeAnnees[cpt] );

        ui->ArtistesAnnees->addItem( item );
    }
    ui->ArtistesAnnees->setCurrentRow( 0 );

    m_artiste = ui->ArtistesAnnees->currentItem()->data( Qt::UserRole ).toInt();

}
void OngletMP3::on_AlbumsTitres_doubleClicked( const QModelIndex& index )
{

    if ( !index.data(Qt::UserRole).isNull() )
    {
        copier();
    }
}

void OngletMP3::EnvoyerTexteAMain()
{
    emit EnvoyerTexte();
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
        DialogModifierAlbum mod( m_album, this );
        mod.exec();
    }
}

void OngletMP3::on_ArtistesAnnees_doubleClicked( const QModelIndex& index )
{
    m_artiste = index.data( Qt::UserRole ).toInt();
    Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( m_artiste );
    DialogModifierArtiste temp( artiste, this );
    temp.exec();
    vider( "Artiste" );
    affichageartistes();
    delete artiste;
}
void OngletMP3::afficherMP3ouAlbum( const QString& MouA )
{
    if ( MouA == "Album" )
    {
        ui->Sur->setText("");
        ui->NomAlbum->setText("");
        ui->Play->setVisible( false );
        ui->Simi->setVisible( false );
        ui->TitresAlb->setVisible( true );

        ui->AjouterAlbumPlaylist->setVisible( true );
        ui->AjoutListePlaylist->setVisible( false );
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
    m_listemp3.clear();

    if ( index.column() == 0 )
    {
        if ( !index.data(Qt::UserRole).isNull() )
        {
            m_album = index.data( Qt::UserRole ).toInt();
            afficherMP3ouAlbum( "Album" );
            afficherAlbumSelectionne();
        }
    }
    else {
        QModelIndexList modelIndList =ui->AlbumsTitres->selectionModel()->selectedIndexes();

        //regarde si la selection est multiple ou non
        if ( modelIndList.count() > 1 )
        {
            for (int i = 0; i< modelIndList.count();i++ )
            {
                //  modelIndList.at(i).data().toString();
                m_listemp3 <<  modelIndList.at(i).data( Qt::UserRole).toInt();
            }
            afficherMP3ouAlbum( "Album" );
            afficherListeMp3();
        } else
        {
            if ( modelIndList.count() == 1 )
            {
                if ( !index.data(Qt::UserRole).isNull() )
                {
                    vider( "Titres" );
                    m_mp3 = modelIndList.at(0).data( Qt::UserRole).toInt();
                    afficherMP3ouAlbum( "MP3" );
                    afficherInfosTitre();
                }
            }
        }
    }
}
void OngletMP3::on_Similaires_clicked(const QModelIndex &index)
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( index.data( Qt::UserRole ).toInt() );
    //On selectionne la bonne categorie
    m_categorie = mp3->getid_type();
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
        m_artiste = mp3->getid_art();

    } else
    {
        m_artiste = CompilsAnnees( mp3->getannee() );
    }
    for (int i = 0; i<ui->ArtistesAnnees->count(); i++)
    {
        if ( ui->ArtistesAnnees->item(i)->data( Qt::UserRole).toInt() == m_artiste)
        {
            ui->ArtistesAnnees->setCurrentRow( i );
        }
    }
    afficheralbumsettitres();

    //On sélectionne l'album et le titre
    m_album =  mp3->getid_alb();
    m_mp3 = mp3->getid_relation();

    for (int row = 0; row<ui->AlbumsTitres->rowCount() ; row++)
    {
        for (int col = 1; col< ui->AlbumsTitres->columnCount(); col++ )
        {

            QTableWidgetItem* item = ui->AlbumsTitres->item(row,col);

            if ( item!= nullptr)
            {
                if (item->data(Qt::UserRole).toInt() == m_mp3 )
                {
                    ui->AlbumsTitres->setCurrentCell(row,col);
                }
            }
        }
    }
    vider("Titre");
    afficherInfosTitre();

    delete mp3;

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
    if ( annee >=2015 && annee<2020 )
    {
        return 7;
    }
    return 7;
}

void OngletMP3::on_LireMP3_clicked()
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( m_mp3 );
    m_PlaylistLecteur.clear();
    m_PlaylistLecteur << mp3->getcheminmp3();

    emit modifplaylist(m_PlaylistLecteur);
    m_fichierlu = QString::number( mp3->getnum_piste() ).rightJustified( 2, '0' ) + " - "+ mp3->getnom_titre() + " ajouté au lecteur.";
    EnvoyerTexteAMain();

    delete mp3;
}

void OngletMP3::on_CopierMP3_clicked()
{

    copier();
}

void OngletMP3::copier()
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( m_mp3 );
    QFileInfo fich( mp3->getcheminmp3() );
    QString doss = ("C:/Users/Alex/Desktop/Musique/");

    if (  mp3->getnom_artiste() == "Indochine" )
    {
        doss +=  mp3->getnom_artiste();
    }
    QDir dir( doss );
    dir.mkpath(doss);
    QString nouvelemplacementchemin =  doss + "/" + fich.fileName();
    QFile::copy( mp3->getcheminmp3(), nouvelemplacementchemin );

    m_fichierlu = nouvelemplacementchemin + " ajouté au dossier de copie. ";
    EnvoyerTexteAMain();

    delete mp3;
}

void OngletMP3::on_LireArtiste_clicked()
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( m_mp3 );
    m_PlaylistLecteur = m_lecteur->listeTitresArtiste( QString::number( mp3->getid_art() ) );
    emit modifplaylist(m_PlaylistLecteur);
    m_fichierlu = mp3->getnom_artiste() + " ajouté au lecteur.";
    EnvoyerTexteAMain();

    delete mp3;
}

void OngletMP3::on_LireAlbum_clicked()
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( m_mp3 );
    m_PlaylistLecteur = m_lecteur->listeTitresAlbum( QString::number( mp3->getid_alb()  ) );
    emit modifplaylist(m_PlaylistLecteur);
    m_fichierlu = mp3->getnom_album() + " ajouté au lecteur.";
    EnvoyerTexteAMain();

    delete mp3;
}

void OngletMP3::on_LireAnnee_clicked()
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( m_mp3 );
    m_PlaylistLecteur = m_lecteur->listeTitresAnnee( QString::number( mp3->getannee() ) );
    emit modifplaylist(m_PlaylistLecteur);
    m_fichierlu = QString::number(mp3->getannee() ) + " ajouté au lecteur.";
    EnvoyerTexteAMain();

    delete mp3;
}

void OngletMP3::on_DialogueLecteurAnnee_clicked()
{
    QString annee = QInputDialog::getText(this, "Année", "Quelle année voulez-vous écouter ?");
    m_PlaylistLecteur = m_lecteur->listeTitresAnnee( annee );
    emit modifplaylist(m_PlaylistLecteur);
    m_fichierlu =  annee + " ajouté au lecteur.";
    EnvoyerTexteAMain();
}

void OngletMP3::on_ModifierArtiste_clicked()
{
    Meta_Artiste* artiste = Meta_Artiste::RecupererBDD( m_artiste );
    DialogModifierArtiste temp( artiste, this );
    temp.exec();
    vider( "Artiste" );
    affichageartistes();
    delete artiste;
}

void OngletMP3::on_Bouton_Playlist_clicked()
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDD( m_mp3 );
    DialogAjoutEnPlaylist* temp = new DialogAjoutEnPlaylist( mp3->getnom_titre() , mp3->getid_relation() , "MP3", this);
    temp->exec();


}
void OngletMP3::AfficherPlaylist( int id )
{
    ui->Playlists->clear();

    QStringList liste;

    liste = m_bddInterface.RecupererPlaylist( id );

    QImage image( "./Pochettes/def.jpg" );

    for ( int cpt = 0; cpt < liste.count(); cpt++ )
    {
        QPixmap scaled( QPixmap::fromImage( image ) );
        scaled = scaled.scaled( 150, 150 );
        QListWidgetItem* item = new QListWidgetItem;
        item->setIcon( QIcon( scaled ) );
        item->setText( liste[cpt] );

        ui->Playlists->addItem( item );
    }
}

void OngletMP3::setCouleur(const QString& couleur)
{
    m_couleur = couleur;
}

void OngletMP3::on_AjouterAlbumPlaylist_clicked()
{
    DialogAjoutEnPlaylist* temp = new DialogAjoutEnPlaylist( ui->Titre->text() , m_album , "Album", this);
    temp->exec();
}

void OngletMP3::on_AjoutListePlaylist_clicked()
{
    DialogAjoutEnPlaylist* temp = new DialogAjoutEnPlaylist( m_listemp3 );
    temp->exec();
}



void OngletMP3::on_Mode_Playlist_clicked(bool checked)
{
    if ( checked )
    {
        ui->AlbumsTitres->setSelectionMode(QAbstractItemView::MultiSelection );


    } else
    {
        ui->AlbumsTitres->setSelectionMode(QAbstractItemView::SingleSelection );

    }
}


