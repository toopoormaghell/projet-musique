#include "mainwindowlecteur.h"
#include "ui_mainwindowlecteur.h"
#include <QStringList>

MainWindowLecteur::MainWindowLecteur(QWidget *parent) :
    QWidget(parent),m_playlist(  ),
    ui(new Ui::MainWindowLecteur),
    m_controles()
{
    ui->setupUi(this);

    m_playlist << "F:/Albums/Blunt James/10 - Where Is My Mind.mp3" <<"F:\\Albums\\Indochine\\1999 - Danceteria\\06 - Rose Song.mp3" << "F:/Albums/Farmer Mylene/2012 - Monkey Me/03 - Monkey Me.mp3";

    m_controles = ui->widget;
    ui->widget_2->setDialogControles( m_controles );
    ui->widget_2->setPlaylist( m_playlist);
}

MainWindowLecteur::~MainWindowLecteur()
{
    delete ui;
}

