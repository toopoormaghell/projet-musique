#include "presentationlecture.h"
#include "ui_presentationlecture.h"

PresentationLecture::PresentationLecture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresentationLecture)
{
    ui->setupUi(this);
}

PresentationLecture::~PresentationLecture()
{
    delete ui;
}
