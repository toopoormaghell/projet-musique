#include "fenetreprincipale.h"
#include <QApplication>
#include "autorisationdiscogs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenetrePrincipale w;
    w.show();
    
    AutorisationDiscogs tmp;
    tmp.xauth();

    return a.exec();
}
