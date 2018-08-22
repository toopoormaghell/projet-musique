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
 /*
void BDDGestionPhys::modifierAlbum( QString Album, QString Artiste, QString ean, int Annee, QList<TitresPhys> titres, int Type, int Id_Poch, int Id_Album, QString Commentaires, int Support)
{


    BDDPoch* poch  = BDDPoch::recupererBDD( Id_Poch );
    BDDArtiste* art = BDDArtiste::recupererBDD(Artiste, *poch);
    Handle<BDDAlbum> alb = BDDAlbum::recupererBDD(Id_Album);
    alb->m_annee = Annee;
    alb->m_type = BDDType::RecupererType(Type);
    alb->m_pochette = poch;
    alb->m_nom = Album;
    FormaterEntiteBDD ( Album );
    alb->m_nomFormate = Album ;

    alb->updateBDD();


    //On supprime la liste des titres déjà présents dans la bdd
    AlbumPhys albphys = BDDAlbum::RecupAlbumEntite( Id_Album);
    for ( int i=0;i< albphys.titres.count();i++ )
    {

        BDDTitre* tit= BDDTitre::recupererBDD( albphys.titres[i].Titre.replace( "'", "$" ) );

        BDDRelation* rel = BDDRelation::recupererBDD(alb, *art, *tit, albphys.titres[i].Num_Piste, albphys.titres[i].Duree,titres[i].MP3 ? 1 : 0,titres[i].Phys ? 1 : 0 );

        tit->supprimerenBDD();
        rel->supprimerenBDDPhys();
    }

    //Et On remet les titres
    for ( int cpt = 0; cpt < titres.count(); cpt++ )
    {
        TitresPhys temp = titres[cpt];
        BDDTitre* tit= BDDTitre::recupererBDD( temp.Titre.replace( "'", "$" ) );
        tit->updateBDD();
        if ( Type == 2 )
        {
            BDDArtiste* artTitre = BDDArtiste::recupererBDD(temp.Artiste, *poch);
            BDDRelation* rel = BDDRelation::recupererBDD (alb, *artTitre, *tit, temp.Num_Piste, temp.Duree,temp.MP3 ? 1 : 0,temp.Phys ? 1 : 0);
            rel->updateBDD();
            delete artTitre;
            delete rel;
        }
        else
        {
            BDDRelation* rel = BDDRelation::recupererBDD(alb, *art, *tit, temp.Num_Piste, temp.Duree,temp.MP3 ? 1 : 0,temp.Phys ? 1 : 0);
            rel->updateBDD();
            delete rel;

        }
    }

    BDDPhys* phys = BDDPhys::RecupererBDD( *alb, ean, *BDDSupport::RecupererSupport(Support), Commentaires );
    phys->updateBDD();

    delete art;

}    */

