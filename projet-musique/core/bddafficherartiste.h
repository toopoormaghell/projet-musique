#ifndef BDDAFFICHERARTISTE_H
#define BDDAFFICHERARTISTE_H

#include <QObject>

class BddAfficherArtiste
{
public:
    BddAfficherArtiste();
    QStringList ListeArtiste();
    QStringList TitresPourArt(QString rech);
    QList<int> AlbumsPourArt(QString rech);
    QList<int> AlbPourTitre(QString rech);
    QList<int> TitresPourAlbum(int id);
    int RecupererIdArtisteNom(QString Nom_Artiste);
};

#endif // BDDAFFICHERARTISTE_H
