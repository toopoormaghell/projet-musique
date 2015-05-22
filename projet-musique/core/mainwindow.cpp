#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include "dialogajouterphys.h"
#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gestionMP3( new BDDGestionMp3 )
{
    ui->setupUi(this);
    ajouterToolbar();

}
void MainWindow::ajouterToolbar()
{
    QToolBar* toolbar;

    toolbar=addToolBar("actump3");
    QPixmap essai(":/menuIcones/actump3");
    toolbar->addAction(QIcon(essai),"Actualiser Mp3",this,SLOT(on_actionActualiser_Mp3_triggered()));

    essai.load(":/menuIcones/ajoutphys");
    toolbar->addAction(QIcon(essai),"Ajouter un Album physique",this,SLOT(on_actionAjouter_Album_triggered()));

    essai.load(":/menuIcones/vider");
    toolbar->addAction(QIcon(essai),"Vider BDD",this,SLOT(on_actionViderBDD_triggered()));

    essai.load(":/menuIcones/exporter");
    toolbar->addAction(QIcon(essai),"Exporter",this,SLOT(actionExporter()));

    essai.load(":menuIcones/artistesinv");
    toolbar->addAction(QIcon(essai),"Artistes Inversés",this,SLOT(actionartistesinverses()));

    essai.load(":menuIcones/bdd");
    toolbar->addAction(QIcon(essai),"Configuration BDD",this,SLOT(actionBDD()));

    essai.load(":menuIcones/config actu");
    toolbar->addAction(QIcon(essai),"Configuration Actualiser MP3",this,SLOT(actionconfigactu()));
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

void MainWindow::actionExporter()
{

}

void MainWindow::actionartistesinverses()
{

}

void MainWindow::actionBDD()
{

}

void MainWindow::actionconfigactu()
{

}
