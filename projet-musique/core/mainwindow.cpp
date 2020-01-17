#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QWidget>
#include <QStatusBar>
#include <QPushButton>
#include <QRadioButton>
#ifdef Q_OS_WIN
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#endif
#include <QShowEvent>

#include "dialogconfigactu.h"
#include "DialogVidageBDD.h"
#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include "dialogajouterphys.h"
#include "ongletmp3.h"
#include "dialogverifications.h"
#include "gestionverifications.h"
#include "bddsauvegardebdd.h"
#include "bddexporterhtml.h"

FenetrePrincipale::FenetrePrincipale( QWidget* parent ) :
    QMainWindow( parent ),
    m_couleurs(),
    ui( new Ui::MainWindow ),
    m_progressbar( new QProgressBar ),
    m_gestionMP3( new BDDGestionMp3 ),
    m_interaction( new QLabel ),
    m_ongletMP3 (  ),
    m_lecteur (  ),
    m_dialogajouterphys( nullptr ),
    m_vidage( this ),
    stop( new QPushButton( "Stop" ) )

  #ifdef Q_OS_WIN
  , m_taskbarButton ( nullptr )
  #endif
{

    ui->setupUi( this );
}
void FenetrePrincipale::ActualiserFenetre()
{
    m_ongletMP3 = ui->MP3;
    m_ongletMP3->setCouleur( m_couleurs[0] ) ;
    m_ongletMP3->ActualiserOnglet();
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
    ui->toolBar->clear();
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

    essai.load(":menuIcones/ExportBDD" );
    ui->toolBar->addAction( QIcon( essai ), " Sauvegarder BDD", this, SLOT( actionExporterBDD() ) );

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    ui->toolBar->addWidget( empty);
    m_lecteur = new MainWindowLecteur(m_couleurs, this);
    m_lecteur->setMinimumHeight(100);
    m_lecteur->setMaximumHeight( 100 );
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
            m_interaction->setText( "Suppression des MP3 de la BDD..." );
            m_gestionMP3->ViderBDD();
            GestionVerifications* temp = new GestionVerifications;
            temp->VerifierBDD();

            m_interaction->setText( "Fini." );
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
    BDDExporterHTML* temp = new BDDExporterHTML();
    temp->exporterHTML();
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

void FenetrePrincipale::actionExporterBDD()
{
    m_interaction->setText( " Sauvegarde de la BDD sur Dropbox..." );

    BDDSauvegardeBDD* temp = new BDDSauvegardeBDD();
    temp->sauvegarde();

    m_interaction->setText( " Fin de la sauvegarde." );
}

QStringList FenetrePrincipale::choixCouleurs()
{
    m_couleurs.clear();
    //Choix des couleurs
    srand(static_cast< unsigned int> (time(nullptr) ) );
    int nombreMystere = (rand() % 11 ) + 1;

    switch ( nombreMystere )
    {
    //1ère : fond 1 // 2ème : écriture widget// 3ème : fond 2 // 4ème : surlignage// 5ème : contour // 6ème : écriture hors cadre
    case 1 : m_couleurs << "#A8F3FF" << "#1EA7EC" << "#FFFF96" << "#1EA7EC" << "#333399" << "#1EA7EC"; break;
    case 2 : m_couleurs << "#FF6C6C" << "#EE1F1F" << "#FFFF96" << "#EE1F1F" << "#9B9B9B" << "#FFFF96"; break;
    case 3 : m_couleurs << "#7B7B7B" << "#454948" << "#FFFF96" << "#454948" << "#9B9B9B" << "#FFFF96"; break;
    case 4 : m_couleurs << "#7B7B7B" << "#454948" << "#CECECE" << "#454948" << "#9B9B9B" << "#CECECE"; break;
    case 5 : m_couleurs << "#40A497" << "#40A497" << "#EFECCA" << "#1D625E" << "#046380" << "#002F2F"; break;
    case 6 : m_couleurs << "#4BB5C1" << "#454948" << "#FFF168" << "#454948" << "#9B9B9B" << "#046380"; break;
    case 7 : m_couleurs << "#FC7F3C" << "#A43C00" << "#F6E497" << "#A43C00" << "#BD8D46" << "#402A2F"; break;
    case 8 : m_couleurs << "#5FF269" << "#727063" << "#B8F2BC" << "#727063" << "#FEE500" << "#1A7620"; break;
    case 9 : m_couleurs << "#EFECCA" << "#EFECCA" << "#40A497" << "#1D625E" << "#046380" << "#002F2F"; break;
    case 10: m_couleurs << "#A97BE6" << "#19003B" << "#E4D2FB" << "#4F2586" << "#9E5BF7" << "#19003B"; break;
    case 11: m_couleurs << "#cccccc" << "#bbbbbb" << "#FFFFFF" << "#000000" << "#bbbbbb" << "#000000"; break;
    default : m_couleurs << "#EFECCA" << "#EFECCA" << "#40A497" << "#1D625E" << "#046380" << "#002F2F"; break;

    }

    return m_couleurs;
}



void FenetrePrincipale::on_ChangerBouton_clicked()
{
    choixCouleurs();
    //Ajout du style pour la fenêtre
    QFile file( ":/qss/default" );
    QString styleSheet="";

    if ( file.open( QFile::ReadOnly ) )
    {
        styleSheet =  QLatin1String( file.readAll() );

    } else
    {
        qDebug() <<"test";
    }


    QString stylesheetcoul = styleSheet.arg ( m_couleurs[0],m_couleurs[1],m_couleurs[2],m_couleurs[3], m_couleurs[4],m_couleurs[5] );

    setStyleSheet( stylesheetcoul );
    update();


    m_ongletMP3->appliquerstyle( stylesheetcoul );
    m_ongletMP3->setCouleur( m_couleurs[0] ) ;
    m_ongletMP3->ActualiserOnglet();
    ui->tab_2->appliquerstyle( stylesheetcoul );
    ui->tab->appliquerstyle( stylesheetcoul );
    ui->tab_3->appliquerstyle( stylesheetcoul );
    ui->tab_4->appliquerstyle( stylesheetcoul );
    ui->tab_5->appliquerstyle(stylesheetcoul );
    ui->tab_6->appliquerstyle( stylesheetcoul );
    ui->Erreurs->appliquerstyle( stylesheetcoul );

    ui->toolBar->setStyleSheet( stylesheetcoul );
    ui->toolBar->update();

    ui->statusBar->setStyleSheet( stylesheetcoul );
    ui->statusBar->update();
    ui->centralWidget->setStyleSheet( stylesheetcoul );
    ui->centralWidget->update();

    ui->tabWidget->setStyleSheet( stylesheetcoul );
    ui->tabWidget->update();

    m_lecteur->setCouleur( m_couleurs );
    m_lecteur->appliquerStyle();

    m_dialogajouterphys->appliquerstyle( stylesheetcoul );
}
