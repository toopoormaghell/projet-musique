#ifndef BDDAFFICHERARTISTE_H
#define BDDAFFICHERARTISTE_H

#include <QObject>

class BddAfficherArtiste
{
public:
    BddAfficherArtiste();
    QList<int> ListeArtiste();
    QList<int> TitresPourArt(QString rech);
    QList<int> AlbumsPourArt(QString rech);
    QList<int> AlbPourTitre(QString rech);
    QList<int> TitresPourAlbum(int id);
};

#endif // BDDAFFICHERARTISTE_H
