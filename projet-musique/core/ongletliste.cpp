#include "ongletliste.h"
#include "ui_ongletliste.h"
#include "bddalbum.h"
#include "bddpoch.h"
#include <QListWidgetItem>


OngletListe::OngletListe(QWidget *parent) :
    QWidget(parent),
    id_selectionnes(  ) ,

    ui(new Ui::OngletListe)
{
    ui->setupUi(this);
    ActualiserOnglet();
}

OngletListe::~OngletListe()
{
    delete ui;
}
void OngletListe::AfficherAlbums( int id)
{
    ui->ListeAlbums->clear();
    QList<int> liste;
    if ( id == -1 )
    {
        liste = m_bddInterface->listeAlbums();
    } else
    {
        liste = m_bddInterface->listeAlbums( id );
    }
    for (int i = 0; i < liste.count(); i++ )
    {
        //Pour chaque album...
        BDDAlbum* alb = BDDAlbum::recupererBDD( liste[i] );

        QListWidgetItem* item = new QListWidgetItem;
        //on affiche la pochette et le nom de l'album
        QPixmap scaled( QPixmap::fromImage( alb->m_pochette->m_image ) );
        scaled = scaled.scaled( 90, 90 );
        item->setIcon( QIcon( scaled ) );
        item->setData( Qt::UserRole, alb->id() );
        item->setText( alb->m_nom.replace("$","'")  );
        if ( id != -1 )
        {
            item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsUserCheckable );
        }
        ui->ListeAlbums->addItem( item );
        delete alb;
    }
    ui->Restants->setText( QString::number( liste.count() ) + " Albums Restants. ");
}

void OngletListe::on_ListeAlbums_itemSelectionChanged()
{
    id_selectionnes.clear();
    foreach (QListWidgetItem* item, ui->ListeAlbums->selectedItems())
    {
        id_selectionnes += item->data( Qt::UserRole ).toInt();

    }
    ui->Selectionnes->setText( QString::number( id_selectionnes.count() )+ " albums sélectionnés" );
}

void OngletListe::on_ViderSelection_clicked()
{
    ViderSelection();
}

void OngletListe::on_ListeBoite_itemSelectionChanged()
{

}
void OngletListe::ViderSelection()
{
    foreach (QListWidgetItem* item, ui->ListeAlbums->selectedItems())
        item->setSelected( false );
}
void OngletListe::on_OkAjout_clicked()
{
    if ( ui->AjoutBoite->text() != "")
    {
        //1 . enregistrement de la boite infos
        int id =    m_bddInterface->EnregistrerBoite( ui->AjoutBoite->text() );
        //2 . enregistrement selection

        m_bddInterface->EnregistrerSelection( id_selectionnes, id );
    }

    ActualiserOnglet();
}
void OngletListe::ActualiserOnglet()
{
    ViderSelection();
    AfficherBoites( );
    AfficherAlbums( -1 );
    ui->AjoutBoite->clear();
}
void OngletListe::AfficherBoites()
{
    ui->ListeBoite->clear();

    QStringList liste;
    liste << "-1" << "Aucune";
    liste << "0" << "Toutes ";
    liste += m_bddInterface->AfficherBoites();

    for (int i = 0; i < liste.count(); i=i+2 )
    {
        QListWidgetItem* item = new QListWidgetItem;
        //on affiche la pochette et le nom de l'album
        item->setData( Qt::UserRole, liste[i] );
        item->setText( liste[i+1]  );

        ui->ListeBoite->addItem( item );

    }
}

void OngletListe::on_ListeBoite_itemClicked(QListWidgetItem *item)
{
    int id = item->data( Qt::UserRole ).toInt();
    AfficherAlbums( id );
}
