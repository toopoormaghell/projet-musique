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

    //En rapport avec la BDD ( ajout, modification, suppression)
    void AjouterAlbum(AlbumGestion album);
    int lireIDPhys(int Id_Album, QString Type, QString CodeBarres);
    void SupprimerAlbumPhys(QString Id_Album);
    void AjouterErreur(AlbumGestion album);
    void ModifierAlbum(AlbumGestion album);

    //Affichage des Albums
    QStringList listeArtistes(QString Categorie);
    QStringList listeCategories();
    QStringList listeAlbums(QString Id_Artiste, QString Categorie);
    QList<TitreGestion> listeTitresAlbum(QString Id_Album);
    AlbumGestion InfosAlbum(QString Id_Album);
    QString choixCategorie(QString Categorie);

    //Exportation (et sauvegarde)
    QStringList ListeAlbumArtisteExport(QString Type);
    void ExporterHTML(QString Type);
    QStringList ListeAlbumSauvegarde();
    void SauvegarderAlbums();

    //En rapport avec l'API
    QString getjetonAcces();
    QString getjetonSecret();
    void changerjetonSecret(QString jeton);
    void changerjetonAcces(QString jeton);

    void AjouterCompil(CompilGestion album);
    void AjouterErreur(CompilGestion album);
};

#endif // BDDPHYS_H
