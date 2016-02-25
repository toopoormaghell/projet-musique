#include "bddgestionphys.h"
#include "util.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddrelation.h"
#include "bddtype.h"
#include "bddphys.h"

BDDGestionPhys::BDDGestionPhys(QObject *parent) :
    QObject(parent)
{
}

void BDDGestionPhys::ajouterAlbum(QImage Poch, QString Album, QString Artiste,QString ean, int Annee, QList<TitresPhys> titres, int Type)
{
    BDDPoch poch(Poch,Album,Artiste);
    BDDArtiste art(Artiste,poch);
    BDDAlbum alb(Album,poch,Annee,Type);


    for (int cpt=0; cpt<titres.count(); cpt++)
    {
        TitresPhys temp = titres[cpt];
        BDDTitre tit(temp.Titre.replace("'","$"),temp.Num_Piste,temp.Duree);
        if (Type==2)
        {
            BDDArtiste artTitre(temp.Artiste,poch);
            BDDRelation rel(alb,artTitre,tit);
        }
        else
        {
            BDDRelation rel(alb,art,tit);
        }
    }
    BDDPhys phys(alb,ean,Type);
}
void BDDGestionPhys::SupprimerenBDDPhys(int Id)
{
    BDDPhys* phys= BDDPhys::RecupererPhys(Id);
    phys->deleteBDD();
    phys->~BDDPhys();
}
