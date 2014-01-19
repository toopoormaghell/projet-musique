#ifndef UTIL_H
#define UTIL_H

#include <QImage>
#include <QStringList>

struct AlbumGestion
{
    QImage pochette;
    QStringList titres;
    QString Artiste;
    QString Album;
    QString Type;
    QString Annee;
};
typedef struct AlbumGestion AlbumGestion;
struct TitreGestion
{
    QImage pochette;
    QString Artiste;
    QString Album;
    QString Annee;
    QString Duree;
    QString Titre;
    QString Type;
    QString Phys;


};
typedef struct TitreGestion TitreGestion;

// Enlève les accents présents dans une QString
void EnleverAccents ( QString& Nom );
QString EchangerArtiste(QString Artiste);

#endif // UTIL_H
