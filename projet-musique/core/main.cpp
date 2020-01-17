#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTranslator>
#include <QLocale>
#include <algorithm>
#include <time.h>
#include "bddsingleton.h"
#include <QLibraryInfo>


int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );
    BDDSingleton::getInstance().changementversion();

    QStringList couleurs;


    FenetrePrincipale w;

    //Application du qt_fr pour la traduction
    QString locale = QLocale::system().name().section( '_', 0, 0 );
    QTranslator translator;
    if ( translator.load( "qtbase_" + locale, QLibraryInfo::location( QLibraryInfo::TranslationsPath ) ) )
    {
        a.installTranslator( &translator );
    }


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

    couleurs = w.choixCouleurs();

    w.setStyleSheet( styleSheet.arg ( couleurs[0],couleurs[1],couleurs[2],couleurs[3], couleurs[4], couleurs[5] ) );
    w.ActualiserFenetre();
    w.setWindowTitle( "Projet Musique" );
    w.setWindowIcon( QIcon( ":/menuIcones/Musique" ));
    w.show();


    return a.exec();
}

