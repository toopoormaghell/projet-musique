#include "bddfusion.h"
#include "util.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddpoch.h"
#include "bddphys.h"
#include "bddartiste.h"
#include "bddrelation.h"
#include "bddmp3.h"
#include "bddrelation.h"
#include "bddsingleton.h"
#include <QtSql>
#include "tags.h"
#include "dialogchoixtitrefusion.h"
#include "QDebug"

BDDFusion::BDDFusion(QWidget *parent) : QWidget(parent)
{

}
void BDDFusion::fusionalbums( QPair<QString,QString> Choix1_Album,  QPair<QImage,QString> Choix1_Pochette, QList<TitresPhys> Choix1_Titres, QPair<QString,QString> Choix2_Album,  QPair<QImage,QString> Choix2_Pochette,  QList<TitresPhys > Choix2_Titres, int ChoixFusion_Annee, int ChoixFusion_Album,  int ChoixFusion_Pochette, QStringList ChoixFusion_Titres )
{
    QString AlbumChoix = "";
    QString PochChoix = "";
    m_Choix1_Titres = Choix1_Titres;
    m_Choix2_Titres = Choix2_Titres;

    BDDAlbum* Alb1 = BDDAlbum::RecupererAlbum( Choix1_Album.second.toInt() );
    BDDAlbum* Alb2 = BDDAlbum::RecupererAlbum( Choix2_Album.second.toInt() );

    BDDPoch* Poch1 = BDDPoch::recupererBDD( Choix1_Pochette.second.toInt() );
    BDDPoch* Poch2 = BDDPoch::recupererBDD( Choix2_Pochette.second.toInt() );


    if ( ChoixFusion_Album == 1 && ChoixFusion_Pochette == 1 )
    {
        fusionnerAlb( Alb1,ChoixFusion_Annee );
        SupprimerAlbum( Alb2, Alb1->id() );
        SupprimerPoch( Poch2, Poch1->id());
        AlbumChoix = Alb1->m_nom;
        PochChoix = Poch1->m_chemin;

    } else if ( ChoixFusion_Album == 1 && ChoixFusion_Pochette == 2 )
    {
        fusionnerAlb( Alb1,ChoixFusion_Annee,Poch2 );
        SupprimerAlbum( Alb2, Alb1->id() );
        SupprimerPoch( Poch1, Poch2->id() );
        AlbumChoix = Alb1->m_nom;
        PochChoix = Poch1->m_chemin;

    } else if ( ChoixFusion_Album == 2 && ChoixFusion_Pochette == 1 )
    {
        fusionnerAlb( Alb2,ChoixFusion_Annee, Poch1 );
        SupprimerAlbum( Alb1, Alb2->id());
        SupprimerPoch( Poch2, Poch1->id());
        AlbumChoix = Alb2->m_nom;
        PochChoix = Poch2->m_chemin;

    } else if ( ChoixFusion_Album == 2 && ChoixFusion_Pochette == 2)
    {
        fusionnerAlb( Alb2, ChoixFusion_Annee);
        SupprimerAlbum( Alb1, Alb2->id());
        SupprimerPoch( Poch1, Poch2->id() );
        AlbumChoix = Alb2->m_nom;
        PochChoix = Poch2->m_chemin;
    }


    //on s'occupe des titres qu'on garde
    for ( int cpt=0 ; cpt < ChoixFusion_Titres.count() ; cpt++ )
    {
        //On change le numéro de piste
        BDDTitre * titre = BDDTitre::RecupererTitre( RecupererMP3( ChoixFusion_Titres[cpt] ) );
        BDDRelation* rel = BDDRelation::RecupererRelationParTitre( titre->id() );
        rel->m_num_piste = cpt+1;
        rel->updateBDD(2);


        //si le titre est un mp3, on change aussi son tag
        if ( rel->m_mp3 )
        {
            BDDMp3* mp3 = BDDMp3::RecupererMP3ParTitre( titre->id() );
            mp3->ChangerTag(AlbumChoix,titre->m_nom,mp3->m_relation->m_artiste->m_nom,ChoixFusion_Annee,cpt,PochChoix);
            delete mp3;
        }
        delete rel;
        delete titre;
    }

    SupprimerTitresEnTrop( m_Choix1_Titres << m_Choix2_Titres, AlbumChoix, ChoixFusion_Annee, PochChoix );

    delete Alb1, Alb2, Poch1, Poch2;

}
void BDDFusion::SupprimerTitresEnTrop(  QList<TitresPhys> titresph, QString AlbumChoix, int ChoixFusion_Annee, QString PochChoix )
{
    for (int cpt = 0 ; cpt < titresph.count(); cpt++ )
    {
        if (! titresph[cpt].Garde)
        {
            BDDRelation* rel = BDDRelation::RecupererRelationParTitre( titresph[cpt].id.toInt() );
            BDDTitre* tit = BDDTitre::RecupererTitre( rel->m_titre->id() );
            tit->mp3physfusion();

            if ( rel->m_mp3 )
            {
                BDDMp3* mp3 = BDDMp3::RecupererMP3ParTitre( tit->id() );
                int nouveau = RecupererNouveauTitre( tit->id() );
                BDDTitre* nvtit = BDDTitre::RecupererTitre( nouveau );
                mp3->ChangerTag(AlbumChoix,nvtit->m_nom,mp3->m_relation->m_artiste->m_nom,ChoixFusion_Annee,rel->m_num_piste,PochChoix);

                mp3->m_relation = BDDRelation::RecupererRelationParTitre( nvtit->id() );
                mp3->updateBDD();
                rel->supprimerModifier();
                delete mp3->m_relation;
                delete mp3;
                delete nvtit;
            }
            else
            {
                rel->supprimerenBDDPhys();

            }
            tit->supprimerenBDD();
            delete rel;
            delete tit;
        }
    }
}

void BDDFusion::fusionnerAlb( BDDAlbum* Alb, int ChoixFusion_Annee, BDDPoch* Poch )
{
    Alb->m_annee = ChoixFusion_Annee;
    Alb->m_pochette = Poch;
    Alb->updateBDD();
}
void BDDFusion::fusionnerAlb( BDDAlbum* Alb, int ChoixFusion_Annee )
{
    Alb->m_annee = ChoixFusion_Annee;
    Alb->updateBDD();
}
void BDDFusion::SupprimerAlbum(BDDAlbum* Alb, int NouvelId)
{
    //On met à jour l'id des relations
    QString queryStr = "UPDATE Relations SET Id_Album  ='" + QString::number( NouvelId ) + "'  WHERE Id_Album = '" + QString::number( Alb->id() ) + "'";
    madatabase.exec( queryStr );
    //On met à jour l'id des albums phys
    queryStr = "UPDATE Phys SET Id_Album  ='" + QString::number( NouvelId ) + "'  WHERE Id_Album = '" + QString::number( Alb->id() ) + "'";
    madatabase.exec( queryStr );

    Alb->supprimerenBDD();

}
void BDDFusion::SupprimerPoch(BDDPoch* Poch, int NouvelId)
{
    //On met à jour l'id des albums
    QString queryStr = "UPDATE Album SET Id_Pochette  ='" + QString::number( NouvelId ) + "'  WHERE Id_Pochette = '" + QString::number( Poch->id() ) + "'";
    madatabase.exec( queryStr );

    //On met à jour l'id des artistes
    queryStr = "UPDATE Artiste SET Id_Pochette  ='" + QString::number( NouvelId ) + "'  WHERE Id_Pochette = '" + QString::number( Poch->id() ) + "'";
    madatabase.exec( queryStr );

    Poch->supprimerenBDD();

}
int BDDFusion::RecupererMP3(QString choix )
{
    int idMp3 = 0;
    QStringList temp = choix.split("_");
    int id = temp[1].toInt();

    if ( temp[0] == "C1")
    {
        TitresPhys titre = m_Choix1_Titres[id];
        m_Choix1_Titres[id].Garde = true;
        idMp3 = titre.id.toInt();
    } else if ( temp[0] == "C2" )
    {
        TitresPhys titre = m_Choix2_Titres[id];
        m_Choix2_Titres[id].Garde = true;
        idMp3 = titre.id.toInt();
    }
    return idMp3;
}

int BDDFusion::RecupererNouveauTitre(int Ancien)
{
    DialogChoixTitreFusion temp(m_Choix1_Titres << m_Choix2_Titres, Ancien,this);
    temp.exec();

    return temp.m_selection;

}

