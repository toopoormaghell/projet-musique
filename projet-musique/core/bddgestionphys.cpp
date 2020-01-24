#include "bddgestionphys.h"
#include "util.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddrelation.h"
#include "bddsupport.h"
#include "bddtype.h"
#include "bddphys.h"

#include "meta_album.h"
#include "meta_titre.h"

BDDGestionPhys::BDDGestionPhys( QObject* parent ) :
    QObject( parent )
{
}



void BDDGestionPhys::SupprimerenBDDPhys( int Id )
{
    Meta_Album* phys = Meta_Album::RecupererBDD( Id );
    phys->SupprimerBDDPhys();
    delete phys;
}


