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
};

#endif // BDDMP3_H
