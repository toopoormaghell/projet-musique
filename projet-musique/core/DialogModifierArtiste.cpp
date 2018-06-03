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
    m_artiste->inversion();
    AfficherArtiste();

}

void DialogModifierArtiste::on_ChangerPochette_clicked()
{
    DialogChoixAlbumPhys choixPoch( QString::number( m_artiste->get_id_artiste() ) );
    choixPoch.exec();
    if ( choixPoch.m_selection != 0 )
    {
        m_artiste->setPoch( choixPoch.m_selection );

        AfficherArtiste();
    }

}
void DialogModifierArtiste::Enregistrer()
{
    m_artiste->update();
}

void DialogModifierArtiste::on_buttonBox_accepted()
{
    Enregistrer();
    this->close();
}
