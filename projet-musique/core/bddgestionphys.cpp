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


BDDGestionPhys::BDDGestionPhys( QObject* parent ) :
    QObject( parent )
{
}

void BDDGestionPhys::ajouterAlbum(QImage Poch, QString Album, QString Artiste, QString ean, int Annee, QList<TitresPhys> titres, int Support, QString Commentaires, int Type)
{
    BDDPoch* poch = BDDPoch::recupererBDD(Poch, Album, (Support==2 ? "Compil":Artiste));
    poch->updateBDD();

    BDDPoch* def = BDDPoch::recupererBDD(1);

    BDDArtiste* art = BDDArtiste::recupererBDD(Artiste, (Type==2 ?*def : *poch));
    BDDAlbum* alb= BDDAlbum::recupererBDD( Album, *poch, Annee, *BDDType::RecupererType(Type), *art );

    for ( int cpt = 0; cpt < titres.count(); cpt++ )
    {
        TitresPhys temp = titres[cpt];
        BDDTitre* tit = BDDTitre::recupererBDD( temp.Titre.replace( "'", "$" ) );
        if ( Type == 2 )
        {
            BDDArtiste* artTitre = BDDArtiste::recupererBDD(temp.Artiste, *def);
            BDDRelation rel( *alb, *artTitre, *tit, temp.Num_Piste, temp.Duree, 0,1,0 );
            delete artTitre;
        }
        else
        {
            BDDRelation rel( *alb, *art, *tit, temp.Num_Piste, temp.Duree, 0,1,0 );
        }
    }


    BDDPhys phys( *alb, ean, *BDDSupport::RecupererSupport(Support), Commentaires );

    delete def;
    delete art;
    delete poch;
}
void BDDGestionPhys::SupprimerenBDDPhys( int Id )
{
    BDDPhys* phys = BDDPhys::RecupererPhys( Id );
    phys->deleteBDD();
    delete phys;
}

void BDDGestionPhys::modifierAlbum( QString Album, QString Artiste, QString ean, int Annee, QList<TitresPhys> titres, int Type, int Id_Poch, int Id_Album, QString Commentaires, int Support)
{
    BDDPoch* poch  = BDDPoch::recupererBDD( Id_Poch );
    BDDArtiste* art = BDDArtiste::recupererBDD(Artiste, *poch);
    BDDAlbum* alb = BDDAlbum::recupererBDD(Id_Album);
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

        BDDRelation rel (*alb, *art, *tit, albphys.titres[i].Num_Piste, albphys.titres[i].Duree,titres[i].MP3 ? 1 : 0,titres[i].Phys ? 1 : 0, 1);



        tit->supprimerenBDD();
        rel.supprimerenBDDPhys();
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
            BDDRelation rel (*alb, *artTitre, *tit, temp.Num_Piste, temp.Duree,temp.MP3 ? 1 : 0,temp.Phys ? 1 : 0,0);
            delete artTitre;
        }
        else
        {
            BDDRelation rel (*alb, *art, *tit, temp.Num_Piste, temp.Duree,temp.MP3 ? 1 : 0,temp.Phys ? 1 : 0,0);

        }
    }

    BDDPhys phys( *alb, ean, *BDDSupport::RecupererSupport(Support), Commentaires );
    delete art;
    delete alb;
}
