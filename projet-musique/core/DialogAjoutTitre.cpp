#include "DialogAjoutTitre.h"
#include "ui_DialogAjoutTitre.h"
#include "bddafficherphys.h"
#include <QCompleter>
#include <QDebug>

DialogAjoutTitre::DialogAjoutTitre( int Type, int Nb_Piste, QWidget* parent ) :
    QDialog( parent ),
    m_Piste ( QString::number( Nb_Piste+1 ) ),
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

    ui->Num_Piste->setValue( m_Piste.toInt() );

}


void DialogAjoutTitre::RecupererDonnees()
{
    m_Piste = QString::number( ui->Num_Piste->value() );
    m_Artiste = ui->Artiste->text();
    m_Titre = ui->Titre->text();
}


void DialogAjoutTitre::Raccourci()
{
    RecupererDonnees();
    emit enregistr(m_Piste, m_Titre , m_Artiste );
}

void DialogAjoutTitre::on_Sauvegarde_clicked()
{
    RecupererDonnees();
    emit enregistr(m_Piste, m_Titre , m_Artiste );
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

void DialogAjoutTitre::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton( button ) == QDialogButtonBox::Ok )
    {
        RecupererDonnees();
        emit enregistr(m_Piste, m_Titre , m_Artiste );
        this->close();
    }
}
