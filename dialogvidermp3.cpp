#include "dialogvidermp3.h"
#include "ui_dialogvidermp3.h"
#include <QDebug>

DialogViderMp3::DialogViderMp3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogViderMp3)
{
    ui->setupUi(this);
}
DialogViderMp3::~DialogViderMp3()
{
    delete ui;
}
void DialogViderMp3::on_buttonBox_accepted()
{
    if (ui->Albums->isChecked())
    {
        m_bddInterface.ViderMp3("Albums");
    }
    if (ui->Compil->isChecked())
    {
        m_bddInterface.ViderMp3("Compil");
    }
    if (ui->Lives->isChecked())
    {
        m_bddInterface.ViderMp3("Lives");
    }
}
