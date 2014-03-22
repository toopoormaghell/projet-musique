#ifndef UTIL_H
#define UTIL_H

#include <QImage>
#include <QStringList>


struct TitreGestion
{
    int Num_Piste;
    QString Duree;
    QString Titre;
    int Id_Titre;
    bool TitreenMp3etPhys;
};
typedef struct TitreGestion TitreGestion;
struct AlbumGestion
{
    QImage Pochette;
    QList<TitreGestion> titres;
    QString Artiste;
    QString Album;
    QString Type;
    QString Annee;
    int Id_Poch;
    int Id_Album;
    int Id_Artiste;
    QString CodeBarres;
};
typedef struct AlbumGestion AlbumGestion;
struct MP3Gestion
{
    QImage Pochette;
    QString Artiste;
    QString Album;
    QString Type;
    QString Annee;
    int Num_Piste;
    QString Duree;
    QString Titre;
    int Id_Titre;
    bool TitreenMp3etPhys;
    int Id_Poch;
    int Id_Artiste;
    int Id_Album;
    QString CheminFichier;
};
typedef struct MP3Gestion MP3Gestion;
struct PlaylistGestion
{
    QImage Pochette;
    QString Titre;
    bool ChangerAlbum;
    QString AlbumChanger;
    int Id_Poch;
    int Id_Playlist;
    int NombrePistes;
    QList<MP3Gestion> titres;
};
typedef struct PlaylistGestion PlaylistGestion;
struct Pochette
{
QImage Pochette;
int Id_Poch;
QString Nom;
};
typedef struct Pochette Pochette;
// Enlève les accents présents dans une QString
void EnleverAccents ( QString& Nom );
QString EchangerArtiste(QString Artiste);

#endif // UTIL_H
