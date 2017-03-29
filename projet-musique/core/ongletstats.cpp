#include "ongletstats.h"
#include "ui_ongletstats.h"
#include "bddtype.h"
#include "bddartiste.h"
#include "bddtitre.h"

OngletStats::OngletStats( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::OngletStats )
{
    ui->setupUi( this );
    AfficherInfos();

}

OngletStats::~OngletStats()
{
    delete ui;
}

void OngletStats::AfficherInfos()
{
    ui->NbMp3Total->setText( "Nombre de Mp3 : " + QString::number( m_bddInterface.NbMp3Total() ) );
    ui->NbPhysTotal->setText( "Nombre de cds : " + QString::number( m_bddInterface.NbPhysTotal() ) );

    AfficherInfosCategoriesPhys();
    AfficherInfosCategoriesMP3();
    AfficherArtistesCompilMP3();

}
void OngletStats::AfficherInfosCategoriesMP3()
{
    int nb = 0;
    //Classique
    int temp = m_bddInterface.NbMp3Categorie( 8 );
    nb = temp + nb;
    ui->NbMp3Classique->setText( "<dd><dd>Classique: " + QString::number( temp ) );
    //BOF
    temp = m_bddInterface.NbMp3Categorie( 4 );
    nb = temp + nb;
    ui->NbMp3BOF->setText( "<dd><dd>BOF: " + QString::number( temp ) );
    //Spectacles
    temp = m_bddInterface.NbMp3Categorie( 5 );
    nb = temp + nb;
    ui->NbMp3Spect->setText( "<dd><dd>Spectacle Musical: " + QString::number( temp ) );
    //Tele
    temp = m_bddInterface.NbMp3Categorie( 6 );
    nb = temp + nb;
    ui->NbMp3Tele->setText( "<dd><dd>Télé Réalités: " + QString::number( temp ) );
    //New Age
    temp = m_bddInterface.NbMp3Categorie( 7 );
    nb = temp + nb;
    ui->NbMp3NA->setText( "<dd>New Age: " + QString::number( temp ) );
    //Generiques
    temp = m_bddInterface.NbMp3Categorie( 9 );
    nb = temp + nb;
    ui->NbMp3Gene->setText( "<dd>Associatif: " + QString::number( temp ) );
    //Inécoutés
    temp = m_bddInterface.NbMp3Categorie( 3 );
    nb = temp + nb;
    ui->NbMp3Gene->setText( "<dd>Inécoutés: " + QString::number( temp ) );
    //Reprises
    temp = m_bddInterface.NbMp3Categorie( 10 );

    nb = temp + nb;
    ui->NbMp3Reprises->setText( "<dd><dd>Reprises: " + QString::number( temp ) );
    //Albums
    temp = m_bddInterface.NbMp3Categorie( 1 );

    nb = temp + nb;
    ui->NbMp3Album->setText( "<dd><dd>Albums: " + QString::number( temp ) );


    ui->NbMp3ScAlbum->setText( "Categorie Albums: " + QString::number( nb ) );
    ui->NbMp3Compil->setText( "Categorie Compils: " + QString::number( m_bddInterface.NbMp3Categorie( 2 ) ) );
    //on détaille un peu les mp3 Compil
    ui->NbAvant1980->setText(" <dd>Avant 1980: " + QString::number( m_bddInterface.NbCompilCategorie( 0 ) ) );
    ui->Nb1980->setText(" <dd>1980-1989: " + QString::number( m_bddInterface.NbCompilCategorie( 1 ) ) );
    ui->Nb1990->setText(" <dd>1990-1999: " + QString::number( m_bddInterface.NbCompilCategorie( 2 ) ) );
    ui->Nb2000->setText(" <dd>2000-2004: " + QString::number( m_bddInterface.NbCompilCategorie( 3 ) ) );
    ui->Nb2005->setText(" <dd>2005-2009: " + QString::number( m_bddInterface.NbCompilCategorie( 4 ) ) );
    ui->Nb2010->setText(" <dd>2010-2014: " + QString::number( m_bddInterface.NbCompilCategorie( 5 ) ) );
    ui->Nb2015->setText(" <dd>2015-2019: " + QString::number( m_bddInterface.NbCompilCategorie( 6 ) ) );

    int pourcent= m_bddInterface.NbTotalMp3Phys()*100/nb;
    ui->PourcentMP3Phys->setText( "Pourcentage de mp3 en CD: "+QString::number( pourcent )+"%" );

}
void OngletStats::AfficherInfosCategoriesPhys()
{
    ui->NbPhysAlbum->setText( "<dd>Albums : " + QString::number( m_bddInterface.NbPhysCategorie( 1 ) ) );
    ui->NbPhysCompil->setText( "<dd>Singles : " + QString::number( m_bddInterface.NbPhysCategorie( 3 ) ) );
    ui->NbPhysSingle->setText( "<dd>Compils : " + QString::number( m_bddInterface.NbPhysCategorie( 2 ) ) );
    ui->Nb_Chansons->setText( "Nombre de chansons : " + QString::number( m_bddInterface.NbChansonsPhys() ) );
      int pourcent= m_bddInterface.NbTotalAlbumMP3Phys()*100/ m_bddInterface.NbPhysTotal();
    ui->PourcentAlbumPhysMp3->setText( "Pourcentage d'albums répresentés en MP3: "+QString::number( pourcent )+"%" );
}
void OngletStats::AfficherArtistesCompilMP3()
{
    QList<int> temp = m_bddInterface.ListeArtistesCompils();

    for ( int i = 0; i < temp.count(); i++ )
    {
        BDDArtiste* art = BDDArtiste::RecupererArtiste( temp[i] );
        QListWidgetItem* item =  new QListWidgetItem;
        item->setText( art->m_nom );
        item->setData( Qt::UserRole, temp[i] );
        ui->ArtistesDansCompil->addItem( item );
        delete art;
    }
}
void OngletStats::AfficherMP3ArtisteCompilMP3()
{
    QList<int> temp = m_bddInterface.ListeMp3ArtisteCompil( choixArtiste() );
    ui->MP3Artiste5->clear();
    for ( int i = 0; i < temp.count(); i++ )
    {
        BDDTitre* titre = BDDTitre::RecupererTitre( temp[i] );
        QListWidgetItem* item =  new QListWidgetItem;
        item->setText( titre->m_nom );
        item->setData( Qt::UserRole, temp[i] );
        ui->MP3Artiste5->addItem( item );
        delete titre;
    }
}
int OngletStats::choixArtiste()
{
    QListWidgetItem* item = ui->ArtistesDansCompil->currentItem();
    if ( item == NULL )
    {
        item = ui->ArtistesDansCompil->item( 0 );
    }
    if ( item != NULL )
    {
        return item->data( Qt::UserRole ).toInt();
    }
    else
    {
        return -1;
    }
}

void OngletStats::on_ArtistesDansCompil_currentRowChanged( int currentRow )
{
    Q_UNUSED( currentRow );
    AfficherMP3ArtisteCompilMP3();
}
