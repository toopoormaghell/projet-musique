#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Ajout du style pour la fenêtre
    QFile file( "./qss/default.qss" );

    if ( file.open( QFile::ReadOnly ) )
    {
        w.setStyleSheet( QLatin1String( file.readAll() ) );
    }

  //  w.setWindowFlags( Qt::CustomizeWindowHint);
    w.show();

    return a.exec();
}
