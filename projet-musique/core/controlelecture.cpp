#include "controlelecture.h"
#include "ui_controlelecture.h"



ControleLecture::ControleLecture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControleLecture)
{
    ui->setupUi(this);

    // Re-émet le signal clicked du bouton qui lance la lecture
    QObject::connect( ui->lecturePause, SIGNAL( clicked(bool) ), this, SIGNAL( playPauseClicked() ) );
}



ControleLecture::~ControleLecture()
{
    delete ui;
}
