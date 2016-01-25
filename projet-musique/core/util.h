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
    QString id;
    QString Artiste;
    bool MP3Phys;

    TitresPhys():
        Num_Piste(0),
        Duree(),
        Titre(),
        id(),
        Artiste(),
        MP3Phys(false)
    {}
};
typedef struct TitresPhys TitresPhys;

struct AlbumPhys
{
    int Type;
    QString Album;
    QString Artiste;
    int Annee;
    QList<TitresPhys> titres;
    int Id_Release;
    QImage Poch;
    int Id_Album;
    QString Type_Str;
    AlbumPhys():
        Type(1),
        Album(),
        Artiste(),
        Annee(1),
        titres(),
        Id_Release(1),
        Poch(),
        Id_Album(1),
        Type_Str()
    {}
};
typedef struct AlbumPhys AlbumPhys;
#endif // UTIL_H
