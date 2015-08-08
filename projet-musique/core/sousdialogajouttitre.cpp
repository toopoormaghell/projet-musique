#include "sousdialogajouttitre.h"
#include "ui_sousdialogajouttitre.h"


SousDialogAjoutTitre::SousDialogAjoutTitre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SousDialogAjoutTitre)
{
    ui->setupUi(this);
}

SousDialogAjoutTitre::~SousDialogAjoutTitre()
{
    delete ui;
}

void SousDialogAjoutTitre::on_buttonBox_accepted()
{
    RecupererDonnees();
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
        emit enregistr();
    }
}

void SousDialogAjoutTitre::on_Sauvegarde_clicked()
{
    RecupererDonnees();
    emit enregistr();
}
