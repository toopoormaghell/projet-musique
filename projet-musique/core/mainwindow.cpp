#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include "dialogajouterphys.h"
#include <QToolBar>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gestionMP3( new BDDGestionMp3 )
{
    ui->setupUi(this);
    ajouterToolbar();
connect(m_gestionMP3,SIGNAL(interac()),this,SLOT(afficherinteraction()));
}
void MainWindow::ajouterToolbar()
{
    QPixmap essai(":/menuIcones/actump3");
    ui->toolBar->addAction(QIcon(essai),"Actualiser Mp3",this,SLOT(on_actionActualiser_Mp3_triggered()));

    essai.load(":/menuIcones/ajoutphys");
    ui->toolBar->addAction(QIcon(essai),"Ajouter un Album physique",this,SLOT(on_actionAjouter_Album_triggered()));

    essai.load(":/menuIcones/vider");
    ui->toolBar->addAction(QIcon(essai),"Vider BDD",this,SLOT(on_actionViderBDD_triggered()));

    essai.load(":/menuIcones/exporter");
    ui->toolBar->addAction(QIcon(essai),"Exporter",this,SLOT(actionExporter()));

    essai.load(":menuIcones/artistesinv");
    ui->toolBar->addAction(QIcon(essai),"Artistes Inversés",this,SLOT(actionartistesinverses()));

    essai.load(":menuIcones/bdd");
    ui->toolBar->addAction(QIcon(essai),"Configuration BDD",this,SLOT(actionBDD()));

    essai.load(":menuIcones/config actu");
    ui->toolBar->addAction(QIcon(essai),"Configuration Actualiser MP3",this,SLOT(actionconfigactu()));
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
int choix =QMessageBox::question(this,tr("Vidage BDD"),tr("Voulez vous vraiment vider la base de données?"),QMessageBox::Yes,QMessageBox::No);
if (choix == QMessageBox::Yes)
{
    BDDSingleton::getInstance().viderBDD();
}
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

void MainWindow::afficherinteraction()
{
 ui->Interaction->setText(m_gestionMP3->m_fichierlu);
}
