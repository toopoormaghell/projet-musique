#include "modelecture.h"
#include "ui_modelecture.h"

ModeLecture::ModeLecture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeLecture)
{
    ui->setupUi(this);
}

ModeLecture::~ModeLecture()
{
    delete ui;
}
