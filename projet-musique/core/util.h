#ifndef UTIL_H
#define UTIL_H

#include <QObject>

void FormaterEntiteBDD(QString &Entite);
QString EchangerArtiste(QString Artiste);
void EnleverAccents(QString &Nom);

struct TitresPhys
{
    int Num_Piste;
    QString Duree;
    QString Titre;

    TitresPhys():
        Num_Piste(0),
        Duree(),
        Titre()
    {}
};
typedef struct TitresPhys TitresPhys;
#endif // UTIL_H
