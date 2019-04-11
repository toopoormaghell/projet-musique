#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QWidget>
#include <QStatusBar>
#include <QPushButton>
#ifdef Q_OS_WIN
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#endif
#include <QShowEvent>

#include "dialogconfigactu.h"
#include "DialogVidageBDD.h"
#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include "DialogAjouterPhys.h"
#include "ongletmp3.h"
#include "dialogverifications.h"
#include "gestionverifications.h"

FenetrePrincipale::FenetrePrincipale(const QStringList& couleurs, QWidget* parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    m_progressbar( new QProgressBar ),
    m_gestionMP3( new BDDGestionMp3 ),
    m_interaction( new QLabel ),
    m_ongletMP3 ( ),
    m_lecteur (  ),
    m_dialogajouterphys( nullptr ),
    m_vidage( this ),
    stop( new QPushButton( "Stop" ) ),
    m_couleurs(couleurs)
#ifdef Q_OS_WIN
  , m_taskbarButton ( nullptr )
#endif
{
    ui->setupUi( this );
    m_ongletMP3 = ui->MP3;
    m_dialogajouterphys = new DialogAjouterPhys( this );
    ajouterToolbar();
    ajouterStatusBar();

    //Change le pourcentage de la progressbar
    connect( m_gestionMP3, SIGNAL( pourcentage() ), this, SLOT( changerPourcentage() ) );
    //A la fin de l'actualiser MP3, il actualise l'onglet MP3
    connect( m_gestionMP3, SIGNAL( fin() ), this, SLOT( ActualiserOngletMP3() ) );
    connect( m_gestionMP3, SIGNAL( fin() ), this, SLOT( ActualiserOngletStats() ) );
    //A la fin de l'ajout d'album Phys, il actualise l'onglet Phys
    connect( m_dialogajouterphys, SIGNAL( ajout() ), this, SLOT( ActualiserOngletPhys() ) );
    //Si le bouton STOP est cliqué, il renvoie un signal
    connect( stop, SIGNAL( clicked() ), m_gestionMP3, SLOT( stop_clique() ) );
    //Si uune action est faite dans l'onglet MP3, la barre de status l'affiche
    connect ( m_ongletMP3, SIGNAL( EnvoyerTexte() ), this, SLOT( AfficherTexte() ) );
    //Si un titre est ajouté dans la playlist du lecteur
    connect( m_ongletMP3,SIGNAL(modifplaylist(QStringList)),m_lecteur,SLOT(modifplaylist(QStringList)));
    //Si un titre est supprimé dans la playlist du lecteur
    connect ( m_lecteur,SIGNAL(suppplaylist(QStringList)),m_ongletMP3,SLOT(suppplaylist(QStringList)));


}
void FenetrePrincipale::ajouterToolbar()
{
    QPixmap essai( ":/menuIcones/actump3" );
    ui->toolBar->addAction( QIcon( essai ), "Actualiser Mp3", this, SLOT( on_actionActualiser_Mp3_triggered() ) );

    essai.load( ":/menuIcones/ajoutphys" );
    ui->toolBar->addAction( QIcon( essai ), "Ajouter un Album physique", this, SLOT( on_actionAjouter_Album_triggered() ) );

    essai.load( ":/menuIcones/vider" );
    ui->toolBar->addAction( QIcon( essai ), "Vider BDD", this, SLOT( on_actionViderBDD_triggered() ) );

    essai.load( ":/menuIcones/exporter" );
    ui->toolBar->addAction( QIcon( essai ), "Exporter", this, SLOT( actionExporter() ) );

    essai.load( ":menuIcones/bdd" );
    ui->toolBar->addAction( QIcon( essai ), "Vérifier BDD", this, SLOT( actionBDD() ) );

    essai.load( ":menuIcones/config actu" );
    ui->toolBar->addAction( QIcon( essai ), "Configurer Actualiser MP3", this, SLOT( actionconfigactu() ) );

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    ui->toolBar->addWidget( empty);
    m_lecteur = new MainWindowLecteur(m_couleurs, this);
    m_lecteur->setMinimumHeight(85);
    m_lecteur->setMaximumHeight( 85 );
    m_lecteur->setMinimumWidth( 700 );
    m_lecteur->setMaximumWidth( 700 );
    ui->toolBar->addWidget( m_lecteur);

}
void FenetrePrincipale::ajouterStatusBar()
{
    //Propriétés de la statusbar
    ui->statusBar->setContentsMargins( 0, 0, 0, 0 );
    ui->statusBar->addPermanentWidget( stop, 1 );
    ui->statusBar->addPermanentWidget( m_progressbar, 1 );
    ui->statusBar->addPermanentWidget( m_interaction, 1 );
    ui->statusBar->setMaximumWidth( 1500 );

    //Propriétés de la progressBar
    m_progressbar->setTextVisible( true );
    m_progressbar->setAlignment( Qt::AlignCenter );
    QString temp = "%p% -";
    m_progressbar->setFormat( temp );
    m_progressbar->setFixedWidth( 500 );

    //Propriétés du widget d'intéraction
    m_interaction->setText( "Prêt" );
    m_interaction->setMaximumHeight( 20 );

}

void FenetrePrincipale::stop_clique()
{
    emit stopper();
}


FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
    delete m_gestionMP3;
}

void FenetrePrincipale::on_actionActualiser_Mp3_triggered()
{
    m_gestionMP3->demarreractualiser();
}

void FenetrePrincipale::on_actionViderBDD_triggered()
{
    connect( &m_vidage, SIGNAL( vidage() ), this, SLOT( ViderBDD() ) );

    m_vidage.show();
}
void FenetrePrincipale::ViderBDD()
{
    //Problème: il faut attendre que la fenêtre se ferme
    if ( m_vidage.Mp3 && m_vidage.Phys && m_vidage.Config )
    {
        m_interaction->setText( "Suppression entière de la BDD..." );
        BDDSingleton::getInstance().viderBDD();
        m_interaction->setText( "Prêt" );
    }
    else
    {
        if ( m_vidage.Mp3 )
        {
            m_gestionMP3->ViderBDD();
            GestionVerifications* temp = new GestionVerifications;
            temp->VerifierBDD();


        }
    }
    ActualiserOngletMP3();
    ActualiserOngletPhys();
}

void FenetrePrincipale::ActualiserOngletPhys()
{
    ui->tab_2->vider( "Artiste" );
    ui->tab_2->afficherListeArtiste();
}
void FenetrePrincipale::on_actionAjouter_Album_triggered()
{
    m_dialogajouterphys->show();
}

void FenetrePrincipale::actionExporter()
{
    m_interaction->setText( "Exportation en cours..." );
    BDDAfficherPhys::exporterHTML();
    m_interaction->setText( "Exportation terminée." );
}


void FenetrePrincipale::actionBDD()
{
    DialogVerifications temp( this );
    temp.exec();


}

void FenetrePrincipale::actionconfigactu()
{
    DialogConfigActu temp( this );
    temp.exec();
}

void FenetrePrincipale::changerPourcentage()
{
    m_progressbar->setValue( m_gestionMP3->m_pourcentage );
    m_progressbar->setFormat( "%p%" );
#ifdef Q_OS_WIN
    m_taskbarButton->progress()->setValue( m_gestionMP3->m_pourcentage );
#endif

    m_interaction->clear();
    m_interaction->setText( m_gestionMP3->m_fichierlu );
}

void FenetrePrincipale::AfficherTexte()
{
    m_interaction->clear();
    m_interaction->setText( m_ongletMP3->m_fichierlu );
}
void FenetrePrincipale::ActualiserOngletMP3()
{
    m_progressbar->setValue( 100 );
#ifdef Q_OS_WIN
    m_taskbarButton->progress()->setValue( 100 );
#endif
    m_progressbar->setFormat( "%p%" );
    m_interaction->setText( "Fin de l'actualisation." );
    m_ongletMP3->vider( "Categories" );
    m_ongletMP3->afficherListeType();
}
void FenetrePrincipale::ActualiserOngletStats()
{
    ui->tab->AfficherInfos();
}


void FenetrePrincipale::showEvent(QShowEvent *e)
{
#ifdef Q_OS_WIN
    m_taskbarButton = new QWinTaskbarButton(this);
    QWindow* toto = windowHandle();
    m_taskbarButton->setWindow(toto);

    m_taskbarButton->progress()->setRange( 0 , 100 );
    m_taskbarButton->progress()->setValue( 0 );
    m_taskbarButton->progress()->show();
#endif
    e->accept();
}