#include "ongletstats.h"
#include "ui_ongletstats.h"

OngletStats::OngletStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletStats)
{
    ui->setupUi(this);
   Chiffres();
}

OngletStats::~OngletStats()
{
    delete ui;
}
void OngletStats::Chiffres()
{

    int temp=m_bddInterface.NombreAlbumsPhys();
ui->AlbPhys->setText(QString::number(temp));

temp=m_bddInterface.NombreMP3();
ui->MP3->setText(QString::number(temp));
}
