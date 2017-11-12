#include "DialogModifierArtiste.h"
#include "ui_DialogModifierArtiste.h"
#include "bddartiste.h"
#include "bddpoch.h"
#include "bddalbum.h"
#include "DialogChoixAlbumPhys.h"
#include "util.h"
DialogModifierArtiste::DialogModifierArtiste( BDDArtiste* Artiste, QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::DialogModifierArtiste ),
    m_artiste( Artiste )
{
    ui->setupUi( this );
    AfficherArtiste();
}

DialogModifierArtiste::~DialogModifierArtiste()
{
    delete ui;
}
void DialogModifierArtiste::AfficherArtiste()
{
    QPixmap scaled( QPixmap::fromImage( m_artiste->m_pochette->m_image ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );

    ui->NomArtiste->setText( m_artiste->m_nom );
}

void DialogModifierArtiste::on_Inversion_clicked()
{
    BDDArtiste::EchangerArtiste( m_artiste->m_nom );
    FormaterEntiteBDD( m_artiste->m_nomFormate );
    AfficherArtiste();
}

void DialogModifierArtiste::on_ChangerPochette_clicked()
{
    DialogChoixAlbumPhys choixPoch( m_artiste->m_nom );
    choixPoch.exec();
    if ( choixPoch.m_selection != 0 )
    {
        BDDAlbum* alb = BDDAlbum::recupererBDD( choixPoch.m_selection );
        delete m_artiste->m_pochette;
        m_artiste->m_pochette = BDDPoch::recupererBDD(alb->m_pochette->id());
        delete alb;
        AfficherArtiste();
    }
}
void DialogModifierArtiste::Enregistrer()
{
    m_artiste->updateBDD();
}

void DialogModifierArtiste::on_buttonBox_accepted()
{
    Enregistrer();
    this->close();
}
