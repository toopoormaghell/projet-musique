#include "MainWindow.h"
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

    //Choix des couleurs
    srand(time(NULL));
    int nombreMystere = (rand() % 7 ) + 1;


    switch ( nombreMystere )
    {
    //1ère : fond 1 // 2ème : écriture utilisateur// 3ème : fond 2 // 4ème : surlignage// 5ème : contour // 6ème : couleur hors cadre
    case 1 : couleurs << "#A8F3FF" << "#1EA7EC" << "#FFFF96" << "#1EA7EC" << "#333399" << "#1EA7EC"; break;
    case 2 : couleurs << "#FF6C6C" << "#790404" << "#FFFF96" << "#EE1F1F" << "#9B9B9B" << "#FFFF96"; break;
    case 3 : couleurs << "#7B7B7B" << "#CCCCCC" << "#FFFF96" << "#454948" << "#9B9B9B" << "#FFFF96"; break;
    case 4 : couleurs << "#7B7B7B" << "#CCCCCC" << "#CECECE" << "#454948" << "#9B9B9B" << "#CECECE"; break;
    case 5 : couleurs << "#40A497" << "#01B0F0" << "#EFECCA" << "#1D625E" << "#046380" << "#002F2F"; break;
    case 6 : couleurs << "#4BB5C1" << "#FEE925" << "#FFF168" << "#454948" << "#9B9B9B" << "#046380"; break;
    case 7 : couleurs << "#FC7F3C" << "#4C1B1B" << "#F6E497" << "#A43C00" << "#BD8D46" << "#402A2F"; break;
    case 8 : couleurs << "#BCBCBC" << "#505050" << "#000000" << "#727063" << "#FEE500" << "#333333"; break;
    default :   couleurs << "#A8F3FF" << "#BBFFFF" << "#FFFF96" << "#1EA7EC" << "#339" << "#BBFFFF";

    }

    FenetrePrincipale w(couleurs);

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

    w.setStyleSheet( styleSheet.arg ( couleurs[0],couleurs[1],couleurs[2],couleurs[3], couleurs[4], couleurs[5] ) );
    w.setWindowTitle( "Projet Musique" );
    w.setWindowIcon( QIcon( ":/menuIcones/Musique" ));
    w.show();

    return a.exec();
}

