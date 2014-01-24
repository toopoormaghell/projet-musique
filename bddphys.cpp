#include "bddphys.h"
#include "bddsingleton.h"

BDDPhys::BDDPhys(QObject *parent):
    BDDCommun(parent)
{
}


void BDDPhys::AjouterAlbum(AlbumGestion album)
{
    QString CheminPochette= AjouterPochette(album).replace("'","$");

}
