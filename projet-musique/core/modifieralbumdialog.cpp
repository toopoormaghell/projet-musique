#include "modifieralbumdialog.h"
#include "ui_modifieralbumdialog.h"
#include "bddphys.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddpoch.h"
#include <QListWidgetItem>

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
        ui->Titres->addItem(phys->m_titres[comp]->m_nom);
        ui->Num_Pistes->addItem(QString::number(phys->m_titres[comp]->m_num_piste));
    }
}
