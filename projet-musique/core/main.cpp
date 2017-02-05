#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QTranslator>
#include <QLocale>
#include "bddsingleton.h"
#include <QLibraryInfo>
int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );
    BDDSingleton::getInstance().changementversion();

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
    if ( file.open( QFile::ReadOnly ) )
    {
        w.setStyleSheet( QLatin1String( file.readAll() ) );
    } else
    {
        qDebug() <<"test";
    }

    w.setWindowTitle( "Projet Musique" );
    w.setWindowIcon( QIcon( ":/menuIcones/Musique" ));
    w.show();

    return a.exec();
}
