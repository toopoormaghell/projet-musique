#include "ongletproblemes.h"
#include "ui_ongletproblemes.h"

OngletProblemes::OngletProblemes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletProblemes)
{
    ui->setupUi(this);
}

OngletProblemes::~OngletProblemes()
{
    delete ui;
}
