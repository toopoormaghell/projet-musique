#ifndef BDDMP3_H
#define BDDMP3_H

#include <QObject>
#include "BDDcommun.h"
#include "util.h"
#include <fileref.h>
#include <id3v2/frames/attachedpictureframe.h>
#include <id3v2/id3v2tag.h>

class BDDMp3 : public BDDCommun
{
public:
    explicit BDDMp3(QObject *parent = 0);
    void actualiserMp3(QString type);
    QStringList listeArtistes(QString Categorie);
    QStringList listeCategories();
    QStringList listeAlbums(QString Id_Artiste);
    QStringList listeTitresAlbum(QString Id_Album);
    QMap<int, QStringList> recupererMp3(QString Type);
    QImage ImageAlbum(const char *encodedName);
    void ArtisteParChemin(TagLib::String &artist, QString chemin);
    int ajouterMp3(MP3Gestion mp3);
    int lireIdMp3(int IdTitre, QString cheminBDD, QString type);
    void SupprimerMp3(int Id_Titre, int Id_Mp3);
    MP3Gestion RecupererInfosMp3(int Id_Titre);
    QString getPathFromIdMp3( const QString& mp3Id );
    QMap<int, MP3Gestion> similaires(QString Id);
    bool ActualiserAlbums();
    bool ActualiserCompil();
    bool ActualiserLives();
    void EnregistrerActuAlbums(bool check);
    void EnregistrerActuCompil(bool check);
    void EnregistrerActuLives(bool check);
    QList<int> ListeMp3Compil(QString annee);
    PlaylistGestion RecupererInfosPlaylist(QString Id);
    QList<MP3Gestion> RecupererPistesPlaylist(QString Id);
    QList<PlaylistGestion> ListesPlaylist();
    QString CreerPlaylist(PlaylistGestion play);
};

#endif // BDDMP3_H
