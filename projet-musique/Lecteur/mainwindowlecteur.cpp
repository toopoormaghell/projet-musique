#include "mainwindowlecteur.h"
#include "ui_mainwindowlecteur.h"
#include <QStringList>
#include <QFile>

MainWindowLecteur::MainWindowLecteur( const QStringList& couleurs , QWidget *parent ) :
    QWidget( parent ),m_playlist(  ),
    ui( new Ui::MainWindowLecteur ),
    m_couleurs( couleurs ),
    m_controles()
{
    ui->setupUi( this );
    QFile file( ":/qss/style" );
    QString styleSheet="";
    if ( file.open ( QFile::ReadOnly ) )
    {
        styleSheet = QLatin1String( file.readAll() ) ;
    }
    ui->centralwidget->setStyleSheet( styleSheet.arg(  m_couleurs[0] , m_couleurs[1] , m_couleurs[2] , m_couleurs[3] , m_couleurs[4] ) );
    m_controles = ui->widget;
    ui->widget_2->setDialogControles( m_controles );
    ui->widget_2->setPlaylist( m_playlist );
    ui->widget_2->raise();
    connect( ui->widget_2 , SIGNAL( SupprimerdansPlaylist( QStringList ) ), this , SLOT( SupprimerdansPlaylist( QStringList ) ) );
    connect( ui->widget , SIGNAL( FinMP3() ), ui->widget_2 , SLOT( FinMP3() ) );
}

MainWindowLecteur::~MainWindowLecteur()
{
    delete ui;
}

void MainWindowLecteur::modifplaylist( QStringList list )
{

    m_playlist.clear();

    m_playlist = list;

    ui->widget_2->setPlaylist( m_playlist );

}
void MainWindowLecteur::SupprimerdansPlaylist( QStringList temp )
{
    m_playlist = temp;
    emit suppplaylist( m_playlist );

}
