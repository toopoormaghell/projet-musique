#include "sousdialogajouttitre.h"
#include "ui_sousdialogajouttitre.h"
#include "bddafficherphys.h"
#include <QCompleter>

SousDialogAjoutTitre::SousDialogAjoutTitre(int Type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SousDialogAjoutTitre)
{
    ui->setupUi(this);
    ActualiserOnglet(Type);
    //Ajoute le raccourci

}

SousDialogAjoutTitre::~SousDialogAjoutTitre()
{
    delete ui;
}
void SousDialogAjoutTitre::ActualiserOnglet(int Type)
{
    AjouterListeTitres();
    AjouterListeArtistes();
    if (Type==2)
    {
        ui->Artiste->setHidden(0);
        ui->label_2->setHidden(0);
    }
    else
    {
        ui->Artiste->setHidden(1);
        ui->label_2->setHidden(1);
    }

}


void SousDialogAjoutTitre::RecupererDonnees()
{
    m_Duree= ui->Duree->text();
    m_Artiste = ui->Artiste->text();
    m_Titre = ui->Titre->text();
}

void SousDialogAjoutTitre::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Save)
    {
        RecupererDonnees();
        emit enregistr(m_Titre, m_Duree, m_Artiste);
    }
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
    {
        RecupererDonnees();
    }
}
void SousDialogAjoutTitre::Raccourci()
{
    RecupererDonnees();
    emit enregistr(m_Titre, m_Duree, m_Artiste);
}

void SousDialogAjoutTitre::on_Sauvegarde_clicked()
{
    RecupererDonnees();
    emit enregistr(m_Titre, m_Duree, m_Artiste);
}
void SousDialogAjoutTitre::AjouterListeTitres()
{
    BDDAfficherPhys temp;
    ui->Titre->setCompleter(new QCompleter(temp.ListeTitresPossibles()));
}
void SousDialogAjoutTitre::AjouterListeArtistes()
{
    BDDAfficherPhys temp;
    ui->Artiste->setCompleter(new QCompleter(temp.ListeArtistesPossibles()));
}
