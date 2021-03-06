#include "meta_album.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtype.h"
#include "bddpoch.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddphys.h"
#include "bddsupport.h"

Meta_Album::Meta_Album(const QString& nom_album, const QString& nom_artiste, int annee, const QImage& Poch, const QString& Type, const QList<Meta_Titre*>& titres, const QString& support_p, const QString& support_m, const QString& commentaires, const QString& ean,int id_album, int id_artiste, int id_poch, int id_type, int id_support_p, int id_support_m, QObject* parent ):
    m_nom_album ( nom_album )
  , m_nom_artiste ( nom_artiste )
  , m_annee ( annee )
  , m_poch ( Poch )
  , m_Type ( Type )
  , m_titres ( titres )
  , m_support_p ( support_p )
  , m_support_m ( support_m )
  , m_commentaires ( commentaires )
  , m_ean ( ean )
  , m_id_album ( id_album )
  , m_id_artiste ( id_artiste)
  , m_id_poch ( id_poch)
  , m_id_type ( id_type)
  , m_id_support_p ( id_support_p )
  , m_id_support_m ( id_support_m )

{
    Q_UNUSED ( parent )
}

const QString& Meta_Album::getnom_album()
{
    return m_nom_album;
}

const QString& Meta_Album::getnom_artiste()
{
    return m_nom_artiste;
}

int Meta_Album::getannee()
{
    return m_annee;
}

const QString& Meta_Album::gettype()
{
    return m_Type;
}

const QList<Meta_Titre*>& Meta_Album::gettitres()
{
    return m_titres;
}
const QImage& Meta_Album::getPoch()
{
    return m_poch;
}

const QString& Meta_Album::getsupport_p()
{
    return m_support_p;
}

int Meta_Album::getid_alb()
{
    return m_id_album;
}

int Meta_Album::getid_art()
{
    return m_id_artiste;
}
int Meta_Album::getid_type()
{
    return m_id_type;
}
int Meta_Album::getid_support_p()
{
    return m_id_support_p;
}
int Meta_Album::getid_support_m()
{
    return m_id_support_m;
}
QString Meta_Album::getean()
{
    return m_ean;
}
int Meta_Album::getid_poch()
{
    return m_id_poch;
}
const QString& Meta_Album::getcommentaires()
{
    return m_commentaires;
}

void Meta_Album::setnom_album(QString nom)
{
    m_nom_album = nom;
}

void Meta_Album::setnom_artiste(QString nom)
{
    m_nom_artiste = nom;
}

void Meta_Album::setannee(int annee)
{
    m_annee = annee;
}

void Meta_Album::settype(QString type)
{
    m_Type = type;
}
void Meta_Album::setPoch(QImage poch)
{
    m_poch = poch;
}

void Meta_Album::setsupport_p(int support_p)
{
    m_id_support_p = support_p;
}

void Meta_Album::setcommentaires(QString commentaires)
{
    m_commentaires = commentaires;
}

void Meta_Album::setid_type(int type)
{
    m_id_type = type;
}
void Meta_Album::settitres(QList<Meta_Titre*> titres)
{
    m_titres = titres;
}

Meta_Album* Meta_Album::RecupererBDD(const int id)
{
    int Annee=-1, id_alb=-1, id_art =-1, id_poch=-1, id_type =-1, id_support_p=-1, id_support_m = -1;
    QString nom_alb, nom_art, type, support_p, commentaires, support_m, ean ;
    QImage Poch;
    QList<Meta_Titre*> titres;

    if (id !=0 )
    {
        //On récupère les infos liées à l'album
        Handle<BDDAlbum> alb = BDDAlbum::recupererBDD( id );

        nom_alb = alb->m_nom;
        Annee = alb->m_annee;
        id_alb = alb->id();
        Poch = alb->m_pochette->m_image;
        id_poch = alb->m_pochette->id();
        id_type = alb->m_type->id();
        type = alb->m_type->m_type;
        nom_art = alb->m_artiste->m_nom;
        id_art = alb->m_artiste->id();

        Handle<BDDPhys> phys = BDDPhys::RecupererBDD( id );
        commentaires = phys->m_commentaires;
        ean = phys->m_ean;

        //On récupère les titres liés à l'album
        QList<int> listetitres = RecupererTitresAlbum( id );

        for (int i = 0; i< listetitres.count(); i++ )
        {
            Meta_Titre* titre = Meta_Titre::RecupererBDD( listetitres[i] );

            titres << titre;

            if ( titre->getid_support_m() != -1 )
                id_support_m = 4;

            if ( titre->getid_support_p() != -1 )
                id_support_p = titre->getid_support_p();
        }
        if ( id_support_m == 1 || id_support_m == 2 )
        {
            support_m = "MP3";
        }
        if ( id_support_p != -1)
        {
            Handle<BDDSupport> tmp = BDDSupport::RecupererSupport( id_support_p );
            support_p = tmp->m_support;
        }
    }
    return new Meta_Album( nom_alb, nom_art , Annee, Poch, type, titres, support_p, support_m, commentaires, ean, id_alb, id_art, id_poch, id_type, id_support_p, id_support_m);
}

Meta_Album::~Meta_Album()
{
    for (int i=0; i < m_titres.count() ; i++)
    {
   //     delete m_titres[i];
    }

}
Meta_Album* Meta_Album::CreerMeta_Album(const QString& nom_album, const QString& nom_artiste, int annee, const QImage& Poch, int type, const QList<Meta_Titre*>& titres, int support_p,  const QString& commentaires, const QString& ean)
{
    return new Meta_Album( nom_album, nom_artiste, annee, Poch, "Aucun", titres, "Aucun", "Aucun", commentaires, ean, -1 , -1, -1 , type, support_p, -1);
}

void Meta_Album::SupprimerBDDPhys()
{
    Handle<BDDPhys> phys = BDDPhys::RecupererBDD( m_id_album );
    phys->supprimerBDD();
}
void Meta_Album::UpdateBDD()
{
    //Update Type
    Handle<BDDType> tmp1 = BDDType::RecupererType( m_id_type );
    m_Type = tmp1->m_type;
    //Update Support
    Handle<BDDSupport> tmp2 = BDDSupport::RecupererSupport( m_id_support_p );
    m_support_p = tmp2->m_support;

    //Update Pochette
    Handle<BDDPoch> poch(nullptr);
    if (m_id_type!=2)
    {
        poch = BDDPoch::recupererBDD( m_poch, m_nom_album.replace( "'", "$" ), (m_id_support_p==2 ? "compil":m_nom_artiste.replace( "'", "$" )));
        poch->updateBDD();
    }
    else
    {
        poch = BDDPoch::recupererBDD(1);
    }

    //Update Artiste
    Handle<BDDArtiste> art = BDDArtiste::recupererBDD(m_nom_artiste .replace("'", "$"), poch);
    art->updateBDD();
    m_id_artiste = art->id();

    //Update Album
    Handle<BDDAlbum> alb= BDDAlbum::recupererBDD( m_nom_album.replace( "'", "$" ),  poch, m_annee, BDDType::RecupererType( m_id_type ), art  );
    alb->updateBDD();
    m_id_album = alb->id();

    //On supprime les anciens Titres
    SupprimerAnciensTitres( true );
    //Update Titres
    for ( int cpt = 0; cpt < m_titres.count(); cpt++ )
    {
        Meta_Titre* temp = m_titres[cpt];
        if ( m_id_support_p != 2 )
        {
            temp->setnom_artiste( m_nom_artiste );

        } else
        {
            temp->setnom_artiste_compilphys( m_nom_artiste );
        }
        temp->setsupportphys( m_id_support_p );
        temp->UpdateBDD();
    }
}
void Meta_Album::majAlbum()
{
    //L'album existe déjà en BDD, il est modifié par l'utilisateur

    //MAJ Album : Nom, Type, Annee , Pochette
    Handle<BDDAlbum> alb = BDDAlbum::recupererBDD( m_id_album );
    alb->m_nom = getnom_album();
    //Type
    Handle<BDDType> tmp1 = BDDType::RecupererType( m_id_type );
    alb->m_type =  tmp1;
    //Annee
    alb->m_annee = getannee();
    //Poch
    Handle<BDDPoch> poch = BDDPoch::recupererBDD( m_poch, getnom_album(), getnom_artiste() );
    poch->updateBDD();
    alb->m_pochette = poch;
    //On met à jour l'album
    alb->updateBDD();

    //MAJ Phys : Support P, Commentaires, EAN
    Handle<BDDPhys> phys = BDDPhys::RecupererBDD( m_id_album );
    phys->m_ean = getean();
    phys->m_commentaires = getcommentaires();

    //Update Support
    Handle<BDDSupport> tmp2 = BDDSupport::RecupererSupport( m_id_support_p );
    phys->m_support = tmp2;

    //On met à jour Phys
    phys->updateBDD();

    //MAJ Artiste: Nom
    Handle<BDDArtiste> art = BDDArtiste::recupererBDD( m_id_artiste );
    art->m_nom = getnom_artiste();
    art->updateBDD();

    //On supprime les anciens Titres
    SupprimerAnciensTitres( false);

      //MAJ Titres
    for ( int cpt = 0; cpt < m_titres.count(); cpt++ )
    {
        Meta_Titre* temp = m_titres[cpt];
        temp->settype( m_Type );
        temp->setnom_album( m_nom_album );
        temp->setannee( m_annee );
        temp->setPoch( m_poch );

        if ( m_id_support_p != 2 )
        {
            temp->setnom_artiste( m_nom_artiste );
        }
        temp->setsupportphys( m_id_support_p );
        temp->UpdateBDD();
    }

}
void Meta_Album::SupprimerAnciensTitres(bool Update)
{
    QList<int> liste = RecupererTitresAlbum( m_id_album );

    for (int i=0 ; i < liste.count(); i++ )
    {
        Meta_Titre* titre = Meta_Titre::RecupererBDD( liste[i] );
        int comp=0;
        int fini=0;
        while (  comp < m_titres.count() && fini == 0 )
        {
            QString temp = titre->getnom_titre();
            FormaterEntiteBDD( temp );

            QString temp2 = m_titres[ comp ]->getnom_titre();
            FormaterEntiteBDD(temp2);
            if ( temp ==  temp2  )
            {
                m_titres[ comp ]->setid_support_m( titre->getid_support_m() );
                m_titres[ comp ]->setcheminmp3( titre->getcheminmp3() );
                m_titres[ comp ]->setduree( titre->getduree() );

                if ( Update )
                {
                    titre->SupprimerBDDMP3();
                } else
                {
                    titre->SupprimerBDDPhys();
                }

                fini = 1;
                break;
            }

            comp ++;
        }
        if ( fini == 0)
        {
            if ( Update )
            {
                titre->SupprimerBDDMP3();
            } else
            {
                titre->SupprimerBDDPhys();
            }
        }
        delete titre;
    }
}
QList< int> Meta_Album::RecupererTitresAlbum(int id)
{
    QList<int> liste;

    QString queryStr = "SELECT DISTINCT Id_Relation FROM Relations R WHERE Id_Album='" + QString::number( id ) + "' ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        liste << rec.value("Id_Relation").toInt();
    }

    return liste;
}
