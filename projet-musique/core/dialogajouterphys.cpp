#include "dialogajouterphys.h"
#include "ui_dialogajouterphys.h"

DialogAjouterPhys::DialogAjouterPhys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjouterPhys)
{
    ui->setupUi(this);
}

DialogAjouterPhys::~DialogAjouterPhys()
{
    delete ui;
}
