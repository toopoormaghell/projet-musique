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
int Id_Relation;

    TitreGestion():
        Num_Piste(0),
        Duree(),
        Titre(),
        Id_Titre(0),
        TitreenMp3etPhys(false),
    Id_Relation(0)
    {}
};
typedef struct TitreGestion TitreGestion;
struct MP3Gestion: public TitreGestion
{
    QImage Pochette;
    QString Artiste;
    QString Album;
    QString Type;
    QString Annee;
    int Id_Poch;
    int Id_Artiste;
    int Id_Album;
    QString CheminFichier;
    int Id_Relation;

    MP3Gestion():
        TitreGestion(),
        Pochette(),
        Artiste(),
        Album(),
        Type(),
        Annee(),
        Id_Poch( 0 ),
        Id_Artiste( 0 ),
        Id_Album( 0 ),
        CheminFichier(),
        Id_Relation( 0 )
    {}
};
typedef struct MP3Gestion MP3Gestion;
template <class T>
struct CDGestion
{
    QImage Pochette;
    QList<T> titres;
    QString Artiste;
    QString Album;
    QString Type;
    QString Annee;
    int Id_Poch;
    int Id_Album;
    int Id_Artiste;
    QString CodeBarres;
    bool ErreurPochette;
    QString Chem_Poch_Alt;
    int Id_Relation;

    CDGestion():
        Pochette(),
        titres(),
        Artiste(),
        Album(),
        Type(),
        Annee(),
        Id_Poch( 0 ),
        Id_Album( 0 ),
        Id_Artiste( 0 ),
        CodeBarres(),
        Id_Relation( 0)
    {}
};
typedef struct CDGestion <TitreGestion> AlbumGestion;
typedef struct CDGestion <MP3Gestion> CompilGestion;


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

    PlaylistGestion():
        Pochette(),
        Titre(),
        ChangerAlbum( false ),
        AlbumChanger(),
        Id_Poch( 0 ),
        Id_Playlist( 0 ),
        NombrePistes( 0 ),
        titres()
    {}
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
