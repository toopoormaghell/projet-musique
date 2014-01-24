#ifndef UTIL_H
#define UTIL_H

#include <QImage>
#include <QStringList>


struct TitreGestion
{
    QString Num_Piste;
    QString Duree;
    QString Titre;
};
typedef struct TitreGestion TitreGestion;
struct AlbumGestion
{
    QImage pochette;
    QList<TitreGestion> titres;
    QString Artiste;
    QString Album;
    QString Type;
    QString Annee;
};
typedef struct AlbumGestion AlbumGestion;

// Enlève les accents présents dans une QString
void EnleverAccents ( QString& Nom );
QString EchangerArtiste(QString Artiste);

#endif // UTIL_H
