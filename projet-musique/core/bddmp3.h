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

    //En rapport avec la BDD (ajout, modification, suppression)
    void actualiserMp3(QString type);
    int ajouterMp3(MP3Gestion mp3);
    int lireIdMp3(int IdRelation, QString cheminBDD, QString type);
    void SupprimerMp3(int Id_Titre);
    QImage ImageAlbum(const TagLib::FileRef& f); //récupère l'image du MP3 pour pouvoir l'enregistrer
    void ArtisteParChemin(TagLib::String &artist, QString chemin); //Change les artistes selon si c'est un chemin générique
    void ViderMp3(QString Type);

    //Pour afficher les MP3
    QStringList listeArtistes(QString Categorie);
    QStringList listeCategories();
    QStringList listeAlbums(QString Id_Artiste);
    QStringList listeTitresAlbum(QString Id_Album);
    QMap<int, QStringList> recupererMp3(QString Type);
    MP3Gestion RecupererInfosMp3(int Id_Titre); //récupère les infos du mp3 sélectionné
    QString getPathFromIdMp3( const QString& mp3Id ); //récupère le chemin du mp3 sélectionné
    QMap<int, MP3Gestion> similaires(QString Id);
    QList<int> ListeMp3Compil(QString annee);



    int NombreMP3();
};

#endif // BDDMP3_H
