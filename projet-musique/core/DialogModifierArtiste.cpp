#include "DialogModifierArtiste.h"
#include "ui_DialogModifierArtiste.h"
#include "DialogChoixAlbumPhys.h"

#include "meta_artiste.h"

DialogModifierArtiste::DialogModifierArtiste(Meta_Artiste* Artiste, QWidget* parent ) :
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
    QPixmap scaled( QPixmap::fromImage( m_artiste->getPoch() ) );
    scaled = scaled.scaled( 150, 150 );
    ui->Pochette->setPixmap( scaled );

    ui->NomArtiste->setText( m_artiste->getNom_Artiste() );
}

void DialogModifierArtiste::on_Inversion_clicked()
{
    /*    BDDArtiste::EchangerArtiste( m_artiste->m_nom );
    FormaterEntiteBDD( m_artiste->m_nomFormate );
    AfficherArtiste();
    */
}

void DialogModifierArtiste::on_ChangerPochette_clicked()
{
/*    DialogChoixAlbumPhys choixPoch( m_artiste->getNom_Artiste() );
    choixPoch.exec();
    if ( choixPoch.m_selection != 0 )
    {
        Meta_Album* alb = Meta_Album::RecupererBDD( choixPoch.m_selection );

        m_artiste->m_pochette = BDDPoch::recupererBDD(alb->m_pochette->id());
        delete alb;
        AfficherArtiste();
    }
    */
}
void DialogModifierArtiste::Enregistrer()
{
    //m_artiste->updateBDD();
}

void DialogModifierArtiste::on_buttonBox_accepted()
{
    Enregistrer();
    this->close();
}
