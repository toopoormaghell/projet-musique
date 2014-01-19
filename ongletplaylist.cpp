#include "ongletplaylist.h"
#include "ui_ongletplaylist.h"

OngletPlaylist::OngletPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletPlaylist)
{
    ui->setupUi(this);
}

OngletPlaylist::~OngletPlaylist()
{
    delete ui;
}
