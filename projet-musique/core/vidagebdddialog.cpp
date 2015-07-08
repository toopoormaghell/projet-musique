#include "vidagebdddialog.h"
#include "ui_vidagebdddialog.h"
#include "bddsingleton.h"
#include "bddgestionmp3.h"
#include "QDebug"
VidageBDDDialog::VidageBDDDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VidageBDDDialog)
{
    ui->setupUi(this);
}

VidageBDDDialog::~VidageBDDDialog()
{
    delete ui;
}

void VidageBDDDialog::on_MP3_toggled(bool checked)
{
    Mp3= ui->MP3->isChecked();
}

void VidageBDDDialog::on_Phys_toggled(bool checked)
{
    Phys=ui->Phys->isChecked();
}

void VidageBDDDialog::on_Config_toggled(bool checked)
{
    Config=ui->Config->isChecked();
}

void VidageBDDDialog::on_buttonBox_accepted()
{
    Mp3= ui->MP3->isChecked();
    Phys=ui->Phys->isChecked();
    Config=ui->Config->isChecked();
}
