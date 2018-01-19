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
    int nombreMystere = (rand() % 10 ) + 1;

    switch ( nombreMystere )
    {
    //1ère : fond 1 // 2ème : écriture widget// 3ème : fond 2 // 4ème : surlignage// 5ème : contour // 6ème : écriture hors cadre
    case 1 : couleurs << "#A8F3FF" << "#1EA7EC" << "#FFFF96" << "#1EA7EC" << "#333399" << "#1EA7EC"; break;
    case 2 : couleurs << "#FF6C6C" << "#EE1F1F" << "#FFFF96" << "#EE1F1F" << "#9B9B9B" << "#FFFF96"; break;
    case 3 : couleurs << "#7B7B7B" << "#454948" << "#FFFF96" << "#454948" << "#9B9B9B" << "#FFFF96"; break;
    case 4 : couleurs << "#7B7B7B" << "#454948" << "#CECECE" << "#454948" << "#9B9B9B" << "#CECECE"; break;
    case 5 : couleurs << "#40A497" << "#1D625E" << "#EFECCA" << "#1D625E" << "#046380" << "#002F2F"; break;
    case 6 : couleurs << "#4BB5C1" << "#454948" << "#FFF168" << "#454948" << "#9B9B9B" << "#046380"; break;
    case 7 : couleurs << "#FC7F3C" << "#A43C00" << "#F6E497" << "#A43C00" << "#BD8D46" << "#402A2F"; break;
    case 8 : couleurs << "#5FF269" << "#727063" << "#B8F2BC" << "#727063" << "#FEE500" << "#1A7620"; break;
    case 9 : couleurs << "#EFECCA" << "#EFECCA" << "#40A497" << "#1D625E" << "#046380" << "#002F2F"; break;
    case 10: couleurs << "#A97BE6" << "#19003B" << "#E4D2FB" << "#4F2586" << "#9E5BF7" << "#19003B"; break;
    default :  couleurs << "#EFECCA" << "#1D625E" << "#40A497" << "#1D625E" << "#046380" << "#002F2F"; break;

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

