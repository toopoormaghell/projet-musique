#ifndef GESTIONVERIFICATIONS_H
#define GESTIONVERIFICATIONS_H

#include <QObject>

class GestionVerifications
{
public:
    GestionVerifications();
    void SuppressionPochettes();
    void verifierbdd();
    void titresphysetmp3();
    void PochCompils();
private:
    QStringList creerfilepochettes();
};

#endif // GESTIONVERIFICATIONS_H
