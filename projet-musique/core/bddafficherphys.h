#ifndef BDDAFFICHERPHYS_H
#define BDDAFFICHERPHYS_H

#include <QObject>


class BDDAfficherPhys : public QObject
{
    Q_OBJECT


public:
    explicit BDDAfficherPhys( QObject* parent = 0 );

    QStringList RecupererListeTypes();
    QList<int> ListeArtiste(int categorie);
    QList<int> listeAlbums(QString Id_Artiste );
    QList<int> listeCompils(QString Id_Artiste , int Categorie);
    QList<int> listeSingles(QString Id_Artiste );
    static void exporterHTML();
    static QStringList ListeAlbumSauvegarde( int Cate );
    QStringList ListeTitresPossibles();
    QStringList ListeArtistesPossibles();
    QList<int> TitresParArtistes( QString Id_Artiste );

    QList<int> AlbSansMP3(QString Id_Artiste, int Categorie);

};

#endif // BDDAFFICHERPHYS_H
