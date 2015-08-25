#include "controlevolume.h"
#include "ui_controlevolume.h"

ControleVolume::ControleVolume(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControleVolume)
{
    ui->setupUi(this);
}

ControleVolume::~ControleVolume()
{
    delete ui;
}
