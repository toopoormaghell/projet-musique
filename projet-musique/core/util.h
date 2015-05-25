#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QImage>
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

struct AlbumPhys
{
    QString Album;
    QString Artiste;
    int Annee;
    QList<TitresPhys> titres;
    int Id;
    QImage Poch;

    AlbumPhys():
    Album(),
    Artiste(),
    Annee(1),
    titres(),
    Id(1),
    Poch()
    {}
};
typedef struct AlbumPhys AlbumPhys;
#endif // UTIL_H
