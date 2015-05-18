#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include "dialogajouterphys.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gestionMP3( new BDDGestionMp3 )
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_gestionMP3;
}

void MainWindow::on_actionActualiser_Mp3_triggered()
{
    m_gestionMP3->demarreractualiser(1);
}

void MainWindow::on_actionViderBDD_triggered()
{
    BDDSingleton::getInstance().viderBDD();
}

void MainWindow::on_actionAjouter_Album_triggered()
{
    DialogAjouterPhys temp;
    temp.exec();
}
