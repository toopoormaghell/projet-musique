#ifndef BDDPHYS_H
#define BDDPHYS_H

#include <QObject>
#include "BDDcommun.h"
#include <QStringList>
#include "util.h"

class BDDPhys : public BDDCommun
{

public:
    explicit BDDPhys(QObject *parent = 0);
    void AjouterAlbum(AlbumGestion album);


    QStringList listeArtistes(QString Categorie);
    QStringList listeCategories();
    QStringList listeAlbums(QString Id_Artiste, QString Categorie);
    QList<TitreGestion> listeTitresAlbum(QString Id_Album);
    AlbumGestion InfosAlbum(QString Id_Album);
    QString choixCategorie(QString Categorie);
    int lireIDPhys(int Id_Album, QString Type);
};

#endif // BDDPHYS_H
