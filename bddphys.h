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

};

#endif // BDDPHYS_H
