#include "ongletstats.h"
#include "ui_ongletstats.h"

OngletStats::OngletStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletStats)
{
    ui->setupUi(this);
    AfficherInfos();
}

OngletStats::~OngletStats()
{
    delete ui;
}

OngletStats::AfficherInfos()
{
ui->NbMp3Total->setText("Nombre de Mp3 : "+QString::number(m_bddInterface.NbMp3Total()));
ui->NbPhysTotal->setText("Nombre de cds : "+QString::number(m_bddInterface.NbPhysTotal()));
}
