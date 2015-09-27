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
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_progressbar( new QProgressBar),
    m_gestionMP3( new BDDGestionMp3 ),
    m_interaction( new QLabel),
    m_dialogajouterphys( NULL),
    m_vidage(this),
    stop(new QPushButton("Stop"))
{
    ui->setupUi(this);
    m_dialogajouterphys = new DialogAjouterPhys( this );
    ajouterToolbar();
    ajouterStatusBar();

    //Change le pourcentage de la progressbar
    connect(m_gestionMP3,SIGNAL(pourcentage()),this,SLOT(changerPourcentage()));
    //A la fin de l'actualiser MP3, il actualise l'onglet MP3
    connect(m_gestionMP3,SIGNAL(fin()),this,SLOT(ActualiserOngletMP3()));
    //A la fin de l'ajout d'album Phys, il actualise l'onglet Phys
    connect(m_dialogajouterphys,SIGNAL(ajout()),this,SLOT(ActualiserOngletPhys()));
    //Si le bouton STOP est cliqué, il renvoie un signal
    connect(stop,SIGNAL(clicked()),m_gestionMP3,SLOT(stop_clique()));
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
    ui->statusBar->addPermanentWidget(stop,1);
    ui->statusBar->addPermanentWidget(m_progressbar,1);
    ui->statusBar->addPermanentWidget(m_interaction,1);

    //Propriétés de la progressBar
    m_progressbar->setTextVisible( true );
    m_progressbar->setAlignment( Qt::AlignCenter );
    QString temp = "%p% -";
    m_progressbar->setFormat(temp);
    m_progressbar->setFixedWidth(500);

    //Propriétés du widget d'intéraction
    m_interaction->setText("Prêt");
    m_interaction->setMaximumHeight(20);

}
void MainWindow::stop_clique()
{
    emit stopper();
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
    connect(&m_vidage,SIGNAL(vidage()),this,SLOT(ViderBDD()));

    m_vidage.show();
}
void MainWindow::ViderBDD()
{
    //Problème: il faut attendre que la fenêtre se ferme
    if (m_vidage.Mp3 && m_vidage.Phys && m_vidage.Config)
    {
        m_interaction->setText("Suppression entière de la BDD...");
        BDDSingleton::getInstance().viderBDD();
        m_interaction->setText("Prêt");
    } else
    {
        if (m_vidage.Mp3)
        {
            m_gestionMP3->ViderBDD();
        }
    }
    ActualiserOngletMP3();
    ActualiserOngletPhys();
}

void MainWindow::ActualiserOngletPhys()
{
    ui->tab_2->vider("Artiste");
    ui->tab_2->afficherListeArtiste();
}
void MainWindow::on_actionAjouter_Album_triggered()
{
    m_dialogajouterphys->show();
}

void MainWindow::actionExporter()
{
BDDAfficherPhys::exporterHTML();
}

void MainWindow::actionartistesinverses()
{

}

void MainWindow::actionBDD()
{
    m_interaction->clear();
    m_interaction->setText("Vérification de la BDD...");
    BDDSingleton::getInstance().verifierBDD();
    m_interaction->setText("Vérification terminée.");
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
