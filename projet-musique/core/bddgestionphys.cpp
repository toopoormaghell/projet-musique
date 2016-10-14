#include "bddgestionphys.h"
#include "util.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddrelation.h"
#include "bddtype.h"
#include "bddphys.h"
#include <QDebug>

BDDGestionPhys::BDDGestionPhys( QObject* parent ) :
    QObject( parent )
{
}

void BDDGestionPhys::ajouterAlbum(QImage Poch, QString Album, QString Artiste, QString ean, int Annee, QList<TitresPhys> titres, int Type, QString Commentaires)
{

    BDDPoch poch(Poch, Album, Artiste);

    BDDArtiste art( Artiste, poch );
    BDDAlbum alb( Album, poch, Annee, Type, art );

    for ( int cpt = 0; cpt < titres.count(); cpt++ )
    {
        TitresPhys temp = titres[cpt];
        BDDTitre tit( temp.Titre.replace( "'", "$" ), temp.Num_Piste, temp.Duree, alb );
        if ( Type == 2 )
        {
            BDDArtiste artTitre( temp.Artiste, poch );
            BDDRelation rel( alb, artTitre, tit );
        }
        else
        {
            BDDRelation rel( alb, art, tit );
        }
    }


    BDDPhys phys( alb, ean, Type, Commentaires );
}
void BDDGestionPhys::SupprimerenBDDPhys( int Id )
{
    BDDPhys* phys = BDDPhys::RecupererPhys( Id );
    phys->deleteBDD();
    phys->~BDDPhys();
}

void BDDGestionPhys::modifierAlbum( QString Album, QString Artiste, QString ean, int Annee, QList<TitresPhys> titres, int Type, int Id_Poch, int Id_Album, QString Commentaires)
{
    BDDPoch* poch  = BDDPoch::recupererBDD( Id_Poch );
    BDDArtiste art( Artiste, *poch );
    BDDAlbum* alb = BDDAlbum::RecupererAlbum(Id_Album);
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

        BDDTitre tit( albphys.titres[i].Titre.replace( "'", "$" ), albphys.titres[i].Num_Piste, albphys.titres[i].Duree, *alb );
        BDDRelation rel (*alb, art, tit);

        tit.supprimerenBDD();
        rel.supprimerenBDDPhys();
    }

   //Et On remet les titres
    for ( int cpt = 0; cpt < titres.count(); cpt++ )
    {
        TitresPhys temp = titres[cpt];
        BDDTitre tit( temp.Titre.replace( "'", "$" ), temp.Num_Piste, temp.Duree, *alb );

        if ( Type == 2 )
        {
            BDDArtiste artTitre( temp.Artiste, *poch );
            BDDRelation rel( *alb, artTitre, tit );
        }
        else
        {
            BDDRelation rel( *alb, art, tit );
        }
    }

    delete poch;
    BDDPhys phys( *alb, ean, Type, Commentaires );
}
