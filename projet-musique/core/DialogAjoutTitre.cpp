#include "DialogAjoutTitre.h"
#include "ui_DialogAjoutTitre.h"
#include "bddafficherphys.h"
#include <QCompleter>

DialogAjoutTitre::DialogAjoutTitre( int Type, QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::DialogAjoutTitre )
{
    ui->setupUi( this );
    ActualiserOnglet( Type );
    //Ajoute le raccourci

}

DialogAjoutTitre::~DialogAjoutTitre()
{
    delete ui;
}
void DialogAjoutTitre::ActualiserOnglet( int Type )
{
    AjouterListeTitres();
    AjouterListeArtistes();
    if ( Type == 2 )
    {
        ui->Artiste->setHidden( 0 );
        ui->label_2->setHidden( 0 );
    }
    else
    {
        ui->Artiste->setHidden( 1 );
        ui->label_2->setHidden( 1 );
    }

}


void DialogAjoutTitre::RecupererDonnees()
{
    m_Duree = ui->Duree->text();
    m_Artiste = ui->Artiste->text();
    m_Titre = ui->Titre->text();
}

void DialogAjoutTitre::on_buttonBox_clicked( QAbstractButton* button )
{
    if ( ui->buttonBox->standardButton( button ) == QDialogButtonBox::Save )
    {
        RecupererDonnees();
        emit enregistr( m_Titre, m_Duree, m_Artiste );
    }
    if ( ui->buttonBox->standardButton( button ) == QDialogButtonBox::Ok )
    {
        RecupererDonnees();
    }
}
void DialogAjoutTitre::Raccourci()
{
    RecupererDonnees();
    emit enregistr( m_Titre, m_Duree, m_Artiste );
}

void DialogAjoutTitre::on_Sauvegarde_clicked()
{
    RecupererDonnees();
    emit enregistr( m_Titre, m_Duree, m_Artiste );
}
void DialogAjoutTitre::AjouterListeTitres()
{
    BDDAfficherPhys temp;
    ui->Titre->setCompleter( new QCompleter( temp.ListeTitresPossibles() ) );
}
void DialogAjoutTitre::AjouterListeArtistes()
{
    BDDAfficherPhys temp;
    ui->Artiste->setCompleter( new QCompleter( temp.ListeArtistesPossibles() ) );
}
