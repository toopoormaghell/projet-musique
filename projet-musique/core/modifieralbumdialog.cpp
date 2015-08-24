#include "modifieralbumdialog.h"
#include "ui_modifieralbumdialog.h"
#include "bddphys.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddpoch.h"
#include <QListWidgetItem>
#include "bddtype.h"
#include "bddgestionphys.h"
#include <QDebug>

ModifierAlbumDialog::ModifierAlbumDialog(int selection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierAlbumDialog),
    m_selection(selection)
{
    ui->setupUi(this);
    AfficherAlbum();
}

ModifierAlbumDialog::~ModifierAlbumDialog()
{
    delete ui;
}

void ModifierAlbumDialog::AfficherAlbum()
{

    //On récupère l'album à afficher
    BDDPhys* phys= BDDPhys::RecupererPhys(m_selection);

    //On ajoute les données en vue de la suite
    m_album.Id_Release = phys->m_ean.toInt();
    m_album.Id_Album=phys->m_id;
    //On met le nom, l'artiste, l'année
    ui->Album->setText(phys->m_album->m_nom);
    ui->Annee->setText(QString::number(phys->m_album->m_annee));
    ui->Artiste->setText(phys->m_artiste->m_nom);

    //On affiche la pochette
    QPixmap scaled( QPixmap::fromImage( phys->m_album->m_pochette->m_image  ) );
    scaled = scaled.scaled( 100, 100 );
    ui->Pochette->setPixmap(scaled);

    //On affiche les titres
    for (int comp=0;comp<phys->m_titres.count();comp++)
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(phys->m_titres[comp]->m_nom);
        item->setFlags (item->flags () | Qt::ItemIsEditable);
        ui->Titres->addItem(item);
        ui->Duree->addItem(phys->m_titres[comp]->m_duree);
        ListeNumeros();
    }
    //On affiche le type de l'album
    ui->Type->setCurrentText(phys->m_type->m_type);
}
void ModifierAlbumDialog::ListeNumeros()
{
    ui->Num_Pistes->clear();
    for (int i=1;i<ui->Titres->count()+1;i++)
    {
        ui->Num_Pistes->addItem(new QListWidgetItem(QString::number(i).rightJustified(2,'0')+" - "));
    }
}

void ModifierAlbumDialog::EnregistrerAlbum()
{

    m_album.Album= ui->Album->text();
    m_album.Artiste=ui->Artiste->text();
    m_album.Annee=ui->Annee->text().toInt();
    m_album.Type = ui->Type->currentIndex();

    //On récupère la pochette
    const QPixmap* pixmap = ui->Pochette->pixmap();
    QImage image = pixmap->toImage();
    m_album.Poch=image;

    //On récupère les titres
    for (int i=0;i<ui->Titres->count();i++)
    {
        TitresPhys titre;
        titre.Titre=ui->Titres->item(i)->text();
        titre.Duree=ui->Duree->item(i)->text();
        titre.Num_Piste=i+1;

        if (m_album.Type==2)
        {
            //A faire l'edition de compilation
        }

        m_album.titres << titre;
    }

}
void ModifierAlbumDialog::Supprimer_Titre()
{
    QList<QListWidgetItem *> fileSelected = ui->Titres->selectedItems();
    if (fileSelected.size())
    {
        for (int i=ui->Titres->count()-1 ; i>=0 ;i--)
        {
            if (ui->Titres->item(i)->isSelected())
            {
                QListWidgetItem * item = ui->Titres->takeItem(i);
                ui->Titres->removeItemWidget(item);
            }
        }
    }
    ListeNumeros();
}

void ModifierAlbumDialog::on_buttonBox_accepted()
{

    EnregistrerAlbum();

    BDDGestionPhys m_bddinterface;

    m_bddinterface.ajouterAlbum(m_album.Poch,m_album.Album,m_album.Artiste,QString::number(m_album.Id_Release),m_album.Annee,m_album.titres,m_album.Type);

}
