#include "ongletphys.h"
#include "ui_ongletphys.h"

OngletPhys::OngletPhys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletPhys)
{
    ui->setupUi(this);
}

OngletPhys::~OngletPhys()
{
    delete ui;
}
