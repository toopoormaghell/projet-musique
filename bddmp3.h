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
};

#endif // BDDMP3_H
