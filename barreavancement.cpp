#include "barreavancement.h"
#include "ui_barreavancement.h"

BarreAvancement::BarreAvancement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BarreAvancement)
{
    ui->setupUi(this);
    init();
}

BarreAvancement::~BarreAvancement()
{
    delete ui;
}

void BarreAvancement::notifierPouah(const QString &chemin, const float pourcentage)
{
    ui->progressBar->setValue( pourcentage * 100 );
    ui->progressBar->setFormat( chemin );
}

void BarreAvancement::init()
{
    ui->progressBar->setValue( 0 );
    ui->progressBar->setFormat( "" );
}
