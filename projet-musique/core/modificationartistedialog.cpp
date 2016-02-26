#include "modificationartistedialog.h"
#include "ui_modificationartistedialog.h"
#include "bddartiste.h"
#include "bddpoch.h"
#include "bddalbum.h"
#include "choixalbumphysdialog.h"
#include "util.h"
ModificationArtisteDialog::ModificationArtisteDialog( BDDArtiste* Artiste, QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::ModificationArtisteDialog ),
    m_artiste( Artiste )
{
    ui->setupUi( this );
    AfficherArtiste();
}

ModificationArtisteDialog::~ModificationArtisteDialog()
{
    delete ui;
}
void ModificationArtisteDialog::AfficherArtiste()
{
    QPixmap scaled( QPixmap::fromImage( m_artiste->m_pochette->m_image ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );

    ui->NomArtiste->setText( m_artiste->m_nom );
}

void ModificationArtisteDialog::on_Inversion_clicked()
{
    BDDArtiste::EchangerArtiste( m_artiste->m_nom );
    FormaterEntiteBDD( m_artiste->m_nomFormate );
    AfficherArtiste();
}

void ModificationArtisteDialog::on_ChangerPochette_clicked()
{
    ChoixAlbumPhysDialog choixPoch( m_artiste->m_nom );
    choixPoch.exec();
    if ( choixPoch.m_selection != 0 )
    {
        BDDAlbum* alb = BDDAlbum::RecupererAlbum( choixPoch.m_selection );
        m_artiste->m_pochette = alb->m_pochette;
        AfficherArtiste();
    }
}
void ModificationArtisteDialog::Enregistrer()
{
    m_artiste->updateBDD();
}

void ModificationArtisteDialog::on_buttonBox_accepted()
{
    Enregistrer();
}
