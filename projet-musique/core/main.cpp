#include "fenetreprincipale.h"
#include <QApplication>
#include <qfile.h>
#include <qDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenetrePrincipale w;

    //Ajout du style pour la fenêtre
    QFile file("H:\\projet-musique\\bin\\release\\default.qss");
    if (file.open(QFile::ReadOnly))
    {
       w.setStyleSheet(QLatin1String(file.readAll()));
    }

    w.setWindowTitle("Projet Musique");
    w.show();

    return a.exec();
}
