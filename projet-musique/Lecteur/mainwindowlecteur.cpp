#include "mainwindowlecteur.h"
#include "ui_mainwindowlecteur.h"
#include <QStringList>
#include <QFile>
MainWindowLecteur::MainWindowLecteur(QWidget *parent) :
    QWidget(parent),m_playlist(  ),
    ui(new Ui::MainWindowLecteur),
    m_controles()
{
    ui->setupUi(this);
    QFile file(":/qss/style");

    if (file.open (QFile::ReadOnly))
    {
        ui->centralwidget->setStyleSheet(QLatin1String( file.readAll() ) );

    }
    m_controles = ui->widget;
    ui->widget_2->setDialogControles( m_controles );
    ui->widget_2->setPlaylist( m_playlist);
    ui->widget_2->raise();
    connect( ui->widget_2,SIGNAL(SupprimerdansPlaylist(QStringList)),this,SLOT(SupprimerdansPlaylist(QStringList)));
}

MainWindowLecteur::~MainWindowLecteur()
{
    delete ui;
}

void MainWindowLecteur::modifplaylist(QStringList list)
{

    m_playlist.clear();

    m_playlist = list;

    ui->widget_2->setPlaylist( m_playlist);
}
void MainWindowLecteur::SupprimerdansPlaylist(QStringList temp)
{
    m_playlist = temp;
    emit suppplaylist( m_playlist );

}
