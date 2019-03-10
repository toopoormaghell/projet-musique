#ifndef BDDSTATS_H
#define BDDSTATS_H

#include <QObject>
#include "bdd_global.h"

class BDDSHARED_EXPORT bddstats : public QObject
{
    Q_OBJECT
public:
    explicit bddstats( QObject* parent = nullptr );
    int NbMp3Total();
    int NbPhysTotal();
    int NbMp3Categorie( int type );
    int NbPhysCategorie(int support );
    int NbChansonsPhys();
    QList<int> ListeArtistesCompils();
    QList<int> ListeMp3ArtisteCompil( int Id_Artiste );
    int NbCompilCategorie(int type);
    int NbTotalMp3Phys();
    int NbTotalAlbumMP3Phys();
    QList<int> ListeMP3Doublons();


    int NbPhysType(int type);

};

#endif // BDDSTATS_H
