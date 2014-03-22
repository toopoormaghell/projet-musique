#include "dialogdossierpardef.h"
#include "ui_dialogdossierpardef.h"
#include "QDebug"
#include <QFileDialog>
DialogDossierParDef::DialogDossierParDef(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDossierParDef)
{
    ui->setupUi(this);
    AfficherDossierParDef();
    AfficherActu();
}
DialogDossierParDef::~DialogDossierParDef()
{
    delete ui;
}
void DialogDossierParDef::AfficherDossierParDef()
{
    ui->lineEdit->setText(m_bddInterface.getdossierpardef());
}
void DialogDossierParDef::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this,tr("Dossier par défaut"),ui->lineEdit->text(),QFileDialog::ShowDirsOnly);

    ui->lineEdit->setText(fileName);
}
void DialogDossierParDef::EnregistrerDossierParDef()
{
    m_bddInterface.EnregistrerDossierParDef(ui->lineEdit->text());
}
void DialogDossierParDef::on_buttonBox_accepted()
{
    EnregistrerDossierParDef();
    EnregistrerActualiser();
}
void DialogDossierParDef::AfficherActu()
{
    ui->actuAlbums->setChecked(m_bddInterface.ActualiserAlbums());
    ui->actuCompil->setChecked(m_bddInterface.ActualiserCompil());
    ui->actuLives->setChecked(m_bddInterface.ActualiserLives());
}
void DialogDossierParDef::EnregistrerActualiser()
{
    m_bddInterface.EnregistrerActuAlbums(ui->actuAlbums->isChecked());
    m_bddInterface.EnregistrerActuCompil(ui->actuCompil->isChecked());
    m_bddInterface.EnregistrerActuLives(ui->actuLives->isChecked());
}
