#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include "dialogajouterphys.h"
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include "dialogconfigactu.h"
#include "vidagebdddialog.h"
#include "QDebug"
#include <QWidget>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gestionMP3( new BDDGestionMp3 ),
    m_progressbar( new QProgressBar),
    m_interaction( new QLabel),
    m_dialogajouterphys( NULL),
    m_vidage(this)
{
    ui->setupUi(this);
    m_dialogajouterphys = new DialogAjouterPhys( this );
    ajouterToolbar();
    ajouterStatusBar();
    connect(m_gestionMP3,SIGNAL(pourcentage()),this,SLOT(changerPourcentage()));
    connect(m_gestionMP3,SIGNAL(fin()),this,SLOT(ActualiserOngletMP3()));
    connect(m_dialogajouterphys,SIGNAL(ajout()),this,SLOT(ActualiserOngletPhys()));

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
void MainWindow::ajouterStatusBar()
{
    //Propriétés de la statusbar
    ui->statusBar->setContentsMargins(0,0,0,0);

    ui->statusBar->addPermanentWidget(m_progressbar,1);
    ui->statusBar->addPermanentWidget(m_interaction,1);

    //Propriétés de la progressBar
    m_progressbar->setTextVisible( true );
    m_progressbar->setAlignment( Qt::AlignCenter );
    QString temp = "%p% -"+m_gestionMP3->m_fichierlu;
    m_progressbar->setFormat(temp);
    m_progressbar->setFixedWidth(500);

    //Propriétés du widget d'intéraction
    m_interaction->setText("Prêt");
    m_interaction->setMaximumHeight(20);

}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_gestionMP3;
}

void MainWindow::on_actionActualiser_Mp3_triggered()
{
    m_gestionMP3->demarreractualiser();
}

void MainWindow::on_actionViderBDD_triggered()
{
    m_vidage.show();  qDebug() << m_vidage.Mp3;
    if (m_vidage.Mp3)
    {

    }
}
void MainWindow::ActualiserOngletPhys()
{
    ui->tab_2->vider("Categories");
    ui->tab_2->vider("Artiste");
    ui->tab_2->afficherListeType();
    ui->tab_2->afficherListeArtiste();
}
void MainWindow::on_actionAjouter_Album_triggered()
{
    m_dialogajouterphys->show();
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
    DialogConfigActu temp(this);
    temp.exec();
}

void MainWindow::changerPourcentage()
{
    m_progressbar->setValue(m_gestionMP3->m_pourcentage);
    m_progressbar->setFormat("%p%");
    m_interaction->clear();
    m_interaction->setText(m_gestionMP3->m_fichierlu);
}
void MainWindow::ActualiserOngletMP3()
{
    ui->MP3->vider("Categories");
    ui->MP3->afficherListeType();
}
