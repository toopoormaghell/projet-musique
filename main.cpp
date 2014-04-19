#include "fenetreprincipale.h"
#include <QApplication>
#include <QCleanlooksStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("cleanlooks");
    FenetrePrincipale w;
    w.show();
    


    return a.exec();
}
