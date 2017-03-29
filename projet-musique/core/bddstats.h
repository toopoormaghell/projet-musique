#ifndef BDDSTATS_H
#define BDDSTATS_H

#include <QObject>

class bddstats : public QObject
{
    Q_OBJECT
public:
    explicit bddstats( QObject* parent = 0 );
    int NbMp3Total();
    int NbPhysTotal();
    int NbMp3Categorie( int type );
    int NbPhysCategorie( int type );
    int NbChansonsPhys();
    QList<int> ListeArtistesCompils();
    QList<int> ListeMp3ArtisteCompil( int Id_Artiste );
    int NbCompilCategorie(int type);
    int NbTotalMp3Phys();
    int NbTotalAlbumMP3Phys();



};

#endif // BDDSTATS_H
