#include "dialogajouterphys.h"
#include "ui_dialogajouterphys.h"
#include "qdebug.h"
#include "bddgestionphys.h"
#include "util.h"
#include <QFileDialog>
#include "sousdialogajouttitre.h"
#include "bddalbum.h"

DialogAjouterPhys::DialogAjouterPhys( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::DialogAjouterPhys )

{
    m_Type = 1;

    ui->setupUi( this );
    AffichageListeArtistes( -2 );

    AjoutConnex();
}
DialogAjouterPhys::DialogAjouterPhys( int id_album, QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::DialogAjouterPhys )

{
    m_Type = 1;

    ui->setupUi( this );
    AffichageListeArtistes( -2 );


    m_album = BDDAlbum::RecupAlbumEntite( id_album );
    AfficherAlbum();
    AjoutConnex();
}
void DialogAjouterPhys::AjoutConnex()
{
    connect( ui->buttonGroup, SIGNAL( buttonClicked( int ) ), this, SLOT( AffichageListeArtistes( int ) ) ) ;
}

DialogAjouterPhys::~DialogAjouterPhys()
{
    delete ui;
}
void DialogAjouterPhys::recupererEAN()
{
    m_EAN = ui->EAN->text();
}
void DialogAjouterPhys::on_ChercherEAN_clicked()
{
    recupererEAN();

    //On vérifie qu'il y a bien 13 caractères
    while ( m_EAN.count() != 13 )
    {
        m_EAN = "0" + m_EAN;
    }
    m_album = m_research.getAlbumFromEAN( m_EAN );
    AfficherAlbum();
}
void DialogAjouterPhys::AfficherAlbum()
{
    ui->Annee->setText( QString::number( m_album.Annee ) );
    ui->Nom_Album->setText( m_album.Album );
    ui->Nom_Artiste->setText( m_album.Artiste );

    for ( int cpt = 0; cpt < m_album.titres.count(); cpt++ )
    {
        TitresPhys titre = m_album.titres[cpt];
        ui->Piste->addItem( QString::number( titre.Num_Piste ) );
        ui->Titres->addItem( titre.Titre + "(" + titre.Duree + ")" );
        ui->Artiste_Titres->addItem( titre.Artiste );
    }
    AfficherPoch();
}
void DialogAjouterPhys::AfficherPoch()
{
    QPixmap* pixmap = new QPixmap();
    pixmap->convertFromImage( m_album.Poch );

    QPixmap imageScaled = pixmap->scaled( 150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation );
    ui->Pochette->setPixmap( imageScaled );
}
void DialogAjouterPhys::on_Enregistrer_clicked()
{
    RecupererAlbum();
    BDDGestionPhys m_bddinterface;
    m_bddinterface.ajouterAlbum( m_album.Poch, m_album.Album, m_album.Artiste, m_EAN, m_album.Annee, m_album.titres, m_Type );
    ui->Interaction->append( "Album enregistré." );
    emit ajout();
    ViderBoiteDialogue();
}
void DialogAjouterPhys::AfficheInteraction()
{
}
void DialogAjouterPhys::AffichageListeArtistes( int id )
{
    switch ( id )
    {
        case ( -2 ):
            m_Type = 1;
            ui->Artiste_Titres->setHidden( true );
            ui->ArtisteLabel->setHidden( true );
            break;
        case ( -3 ):
            m_Type = 2;
            ui->Artiste_Titres->setHidden( false );
            ui->ArtisteLabel->setHidden( false );
            break;
        case ( -4 ):
            m_Type = 3;
            ui->Artiste_Titres->setHidden( true );
            ui->ArtisteLabel->setHidden( true );
            break;
    }
}
void DialogAjouterPhys::ViderBoiteDialogue()
{
    ui->Artiste_Titres->clear();
    ui->EAN->clear();
    ui->Nom_Album->clear();
    ui->Nom_Artiste->clear();
    ui->Piste->clear();
    ui->Pochette->clear();
    ui->Titres->clear();
    ui->Annee->clear();

    m_album.titres.clear();


}
void DialogAjouterPhys::on_ViderAlbum_clicked()
{
    ViderBoiteDialogue();
}
void DialogAjouterPhys::RecupererAlbum()
{
    m_album.titres.clear();
    m_album.Album = ui->Nom_Album->text().replace( "'", "$" );
    m_album.Artiste = ui->Nom_Artiste->text().replace( "'", "$" );
    m_album.Annee = ui->Annee->text().toInt();
    m_album.Type = m_Type;

    //On récupère la pochette
    const QPixmap* pixmap = ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    m_album.Poch = image;

    //On récupère les titres
    for ( int i = 0; i < ui->Titres->count(); i++ )
    {
        TitresPhys titre;
        QListWidgetItem *item = ui->Titres->item( i );
        QStringList parsing = item->text().split( "(" );
        titre.Titre = parsing[0];

        QStringList parsing2 = parsing[1].split( ")" );
        titre.Duree = parsing2[0];
        titre.Num_Piste = i + 1;

        if ( m_Type == 2 )
        {
            item = ui->Artiste_Titres->item( i );
            titre.Artiste = item->text();
        }

        m_album.titres << titre;
    }

}
void DialogAjouterPhys::listeNumeros()
{
    ui->Piste->clear();
    for ( int i = 1; i < ui->Titres->count() + 1; i++ )
    {
        ui->Piste->addItem( new QListWidgetItem( QString::number( i ).rightJustified( 2, '0' ) + " - " ) );
    }
}
void DialogAjouterPhys::on_Supprimer_Titre_clicked()
{
    QList<QListWidgetItem *> fileSelected = ui->Titres->selectedItems();
    if ( fileSelected.size() )
    {
        for ( int i = ui->Titres->count() - 1 ; i >= 0 ; i-- )
        {
            if ( ui->Titres->item( i )->isSelected() )
            {
                QListWidgetItem * item = ui->Titres->takeItem( i );
                ui->Titres->removeItemWidget( item );
            }
        }
    }
    listeNumeros();
}

void DialogAjouterPhys::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName( this,
                       "Ouvrir l'image contenant la pochette",
                       "C:/Users/Nico/Desktop",
                       "Images (*.png *.xpm *.jpg *.bmp)" );
    QPixmap* pixmap = new QPixmap();
    QImage* image = new QImage( fileName );
    pixmap->convertFromImage( *image );
    QPixmap pixmapscaled = pixmap->scaled( 150, 150, Qt::IgnoreAspectRatio, Qt::FastTransformation );

    ui->Pochette->setPixmap( pixmapscaled );
}

void DialogAjouterPhys::on_Ajouter_Titre_clicked()
{
    SousDialogAjoutTitre toto( m_Type, this );
    connect( &toto, SIGNAL( enregistr( QString, QString, QString ) ), this, SLOT( AjouterTitreManuel( QString, QString, QString ) ) );
    int retVal = toto.exec();
    if ( ( retVal == QDialog::Accepted ) && !toto.m_Titre.isEmpty() )
    {
        AjouterTitreManuel( toto.m_Titre, toto.m_Duree, toto.m_Artiste );
    }

}
void DialogAjouterPhys::AjouterTitreManuel( const QString& titre, const QString& duree, const QString& artiste )
{
    ui->Titres->addItem( titre + "(" + duree + ")" );
    ui->Artiste_Titres->addItem( artiste );
    listeNumeros();

}
