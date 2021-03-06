#ifndef BDDAFFICHERPHYS_H
#define BDDAFFICHERPHYS_H

#include <QObject>


class BDDAfficherPhys : public QObject
{
    Q_OBJECT


public:
    explicit BDDAfficherPhys( QObject* parent = nullptr );

    QStringList RecupererListeTypes();
    QList<int> ListeArtiste(int categorie);
    QList<int> listeAlbums(QString Id_Artiste , int Categorie);
    QList<int> listeCompils(QString Id_Artiste , int Categorie);
    QList<int> listeSingles(QString Id_Artiste );
    QStringList ListeTitresPossibles();
    QStringList ListeArtistesPossibles();
    QList<int> TitresParArtistes( QString Id_Artiste );

    QList<int> AlbSansMP3(QString Id_Artiste, int Categorie);

    QList<int> listeLives(QString Id_Artiste);
};

#endif // BDDAFFICHERPHYS_H
