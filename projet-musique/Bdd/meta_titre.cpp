#include "meta_titre.h"
#include "bddpoch.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddrelation.h"
#include "bddtype.h"
#include "bddsupport.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddmp3.h"
#include "bddphys.h"

Meta_Titre::Meta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, const QString& commentaires, const QString& ean, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m, int id_mp3, QObject* parent):
    m_nom_album ( nom_album )
  , m_nom_artiste ( nom_artiste )
  , m_nom_titre ( nom_titre )
  , m_annee ( annee )
  , m_duree ( duree )
  , m_num_piste ( num_piste )
  , m_poch ( poch )
  , m_Type ( type )
  , m_Support_p ( support_p )
  , m_Support_m ( support_m )
  , m_chemin_m ( chemin_m )
  , m_commentaires ( commentaires )
  , m_ean ( ean )
  , m_id_album ( id_alb )
  , m_id_artiste ( id_art )
  , m_id_titre ( id_titre )
  , m_id_relation ( id_relation )
  , m_id_type (id_type )
  , m_id_support_p ( id_support_p )
  , m_id_support_m ( id_support_m )
  , m_id_mp3 ( id_mp3 )
{
    m_nom_artiste_compilphys="";
    Q_UNUSED ( parent )
}
Meta_Titre* Meta_Titre::RecupererBDD(const int id)
{
    QString queryStr = "SELECT Id_Album, Id_Artiste, Id_Titre , Num_Piste, MP3 , Phys, Duree  FROM Relations WHERE Id_Relation='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    QString nom_Alb, nom_Art , nom_Tit, duree, type, support_m, support_p, chemin_m, commentaires, ean;
    int annee=-1, num_piste=-1 , id_alb=-1, id_art=-1, id_tit=-1, id_type =-1, id_support_m=-1 , id_support_p =-1, id_mp3 = -1;
    QImage poch;

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        //Album
        Handle<BDDAlbum> alb = BDDAlbum::recupererBDD(rec.value("Id_Album").toInt());
        nom_Alb = alb->m_nom;
        id_alb = alb->id();
        poch = alb->m_pochette->m_image;
        annee = alb->m_annee;
        type = alb->m_type->m_type;
        id_type = alb->m_type->id();

        //Artiste
        Handle<BDDArtiste> art = BDDArtiste::recupererBDD(rec.value("Id_Artiste").toInt());
        nom_Art = art->m_nom;
        id_art = art->id();

        //Titre
        Handle<BDDTitre> tit = BDDTitre::recupererBDD(rec.value("Id_Titre").toInt());
        id_tit = tit->id();
        nom_Tit = tit->m_nom;

        //Phys
        if ( rec.value("Phys").toInt() == 1 )
        {
            Handle<BDDSupport> supp = BDDSupport::RecupererSupportAlb( id_alb, "Phys" );
            id_support_p = supp->id();
            support_p = supp->m_support;
            Handle<BDDPhys> phys = BDDPhys::RecupererBDD( id_alb );
            commentaires = phys->m_commentaires;
            ean = phys->m_ean;
        } else
        {
            int phystemp = BDDRelation::supportPhys( id_tit, id_art );
            if ( phystemp != 0 )
            {
                Handle<BDDSupport> supp = BDDSupport::RecupererSupportAlb( phystemp, "Phys" );
                id_support_p = supp->id();
                support_p = supp->m_support;
                Handle<BDDPhys> phys = BDDPhys::RecupererBDD( phystemp );
                commentaires = phys->m_commentaires;
                ean = phys->m_ean;
            } else {
                id_support_p = -1;
                support_p = "Aucun";
            }
        }

        //MP3
        if ( rec.value("MP3").toInt() == 1 )
        {
            Handle<BDDSupport> supp = BDDSupport::RecupererSupportAlb( id_alb, "MP3" );
            id_support_m = supp->id();
            support_m = supp->m_support;
            Handle<BDDMp3> mp3 = BDDMp3::RecupererBDDParRelation( id );
            id_mp3 = mp3->id();
            chemin_m = mp3->m_chemin;
        } else
        {
            int mp3temp = BDDRelation::supportMp3( id_tit, id_art);
            if ( mp3temp > 0 )
            {
                Handle<BDDMp3> mp3 = BDDMp3::RecupererBDDParRelation( mp3temp );
                id_mp3 = mp3->id();
                chemin_m = mp3->m_chemin;
                Handle<BDDSupport> supp = BDDSupport::RecupererSupportAlb( mp3->m_relation->m_album->id() , "MP3" );
                id_support_m = supp->id();
                support_m = supp->m_support;
            } else
            {
                id_support_m = -1;
                support_m = "Aucun";
                chemin_m = "Aucun";
            }
        }

        num_piste = rec.value("Num_Piste").toInt();
        duree =  rec.value("Duree").toString();
    }


    return new Meta_Titre( nom_Alb,nom_Art,nom_Tit,annee,duree,num_piste,poch,type,support_p, support_m , chemin_m, commentaires, ean, id_alb,id_art,id_tit,id,id_type,id_support_p,id_support_m,id_mp3 );
}
void Meta_Titre::setPoch(QImage poch )
{
    m_poch = poch;
}
Meta_Titre* Meta_Titre::RecupererBDDMP3(const int id)
{
    Handle<BDDMp3> mp3 = BDDMp3::RecupererBDD( id );
    int id_rel = mp3->m_relation->id() ;
    return RecupererBDD( id_rel );
}

const QString& Meta_Titre::getnom_album()
{
    return m_nom_album;
}

const QString& Meta_Titre::getnom_artiste()
{
    return m_nom_artiste;
}

const QString& Meta_Titre::getnom_titre()
{
    return m_nom_titre;
}

int Meta_Titre::getannee()
{
    return m_annee;
}

const QString& Meta_Titre::getduree()
{
    return m_duree;
}

int Meta_Titre::getnum_piste()
{
    return m_num_piste;
}

const QString& Meta_Titre::gettype()
{
    return m_Type;
}

const QString& Meta_Titre::getsupportphys()
{
    return m_Support_p;
}
const QString& Meta_Titre::getsupportmp3()
{
    return m_Support_m;
}


int Meta_Titre::getid_support_p()
{
    return m_id_support_p;
}

int Meta_Titre::getid_support_m()
{
    return m_id_support_m;
}

const QString& Meta_Titre::getcheminmp3()
{
    return m_chemin_m;
}

int Meta_Titre::getid_relation()
{
    return m_id_relation;
}

int Meta_Titre::getid_titre()
{
    return m_id_titre;
}

const QImage& Meta_Titre::getpoch()
{
    return m_poch;
}

int Meta_Titre::getid_art()
{
    return m_id_artiste;
}
int Meta_Titre::getid_alb()
{
    return m_id_album;
}

int Meta_Titre::getid_type()
{
    return m_id_type;
}

int Meta_Titre::getid_mp3()
{
    return m_id_mp3;
}

const QString& Meta_Titre::getcommentaires()
{
    return m_commentaires;
}

const QString& Meta_Titre::getean()
{
    return m_ean;
}
void Meta_Titre::setnom_album( QString nom )
{
    m_nom_album = nom;
}
void Meta_Titre::setnom_artiste_compilphys(QString nom)
{
    m_nom_artiste_compilphys = nom;
}
void Meta_Titre::setnom_artiste(QString nom)
{
    m_nom_artiste = nom;
}

void Meta_Titre::setnom_titre( QString nom )
{
    m_nom_titre = nom;
}

void Meta_Titre::setannee(int annee )
{
    m_annee = annee;
}

void Meta_Titre::setduree(QString duree)
{
    m_duree = duree;
}

void Meta_Titre::setnum_piste(int num)
{
    m_num_piste = num;
}

void Meta_Titre::settype( QString type )
{
    m_Type = type;
}

void Meta_Titre::setsupportphys(int support)
{
    m_id_support_p = support;
}
void Meta_Titre::setsupportmp3(QString support)
{
    m_Support_m = support;
}
void Meta_Titre::setcheminmp3(QString chemin)
{
    m_chemin_m = chemin;
}

void Meta_Titre::setid_support_m(int id)
{
    m_id_support_m = id;
}


Meta_Titre::~Meta_Titre()
{

}

Meta_Titre* Meta_Titre::CreerMeta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, int type, int support_p, int support_m, const QString& chemin_m, const QString& commentaires, const QString& ean)
{

    return new Meta_Titre ( nom_album, nom_artiste, nom_titre,annee,duree,num_piste,poch,"Aucun","Aucun","Aucun",chemin_m,commentaires,ean, -1 , -1 , -1 , -1, type, support_p, support_m, -1);

}
void Meta_Titre::ChangerDonnees( const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, int  id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m )
{
    Q_UNUSED  ( nom_album )
    Q_UNUSED  ( nom_artiste )
    Q_UNUSED  ( nom_titre )
    Q_UNUSED  ( annee )
    Q_UNUSED  ( duree )
    Q_UNUSED  ( num_piste )
    Q_UNUSED  ( poch )
    Q_UNUSED  ( type )
    Q_UNUSED  ( support_p )
    Q_UNUSED  ( support_m )
    Q_UNUSED  ( chemin_m )
    Q_UNUSED  ( id_alb )
    Q_UNUSED  ( id_art )
    Q_UNUSED  ( id_titre )
    Q_UNUSED  ( id_relation )
    Q_UNUSED  ( id_type )
    Q_UNUSED  ( id_support_m )
    Q_UNUSED  ( id_support_p )

}
void Meta_Titre::UpdateBDD()
{

    int id_mp3 = 0;
    Handle<BDDType> tmp1 = BDDType::RecupererType( m_id_type );
    m_Type = tmp1->m_type;
    Handle<BDDSupport> tmp2 = BDDSupport::RecupererSupport( m_id_support_m );
    m_Support_m = tmp2->m_support;

    QString tempartpoch ;
    if ( m_id_support_p == 2 )
    {
        tempartpoch = m_nom_artiste_compilphys.replace( "'", "$" );
    } else {
        tempartpoch = m_nom_artiste.replace( "'", "$" );
    }

    Handle<BDDPoch> poch = BDDPoch::recupererBDD( m_poch , m_nom_album.replace( "'", "$" ), tempartpoch);
    poch->updateBDD();

    Handle<BDDPoch> def = BDDPoch::recupererBDD( 1 );

    Handle<BDDArtiste> art = BDDArtiste::recupererBDD (m_nom_artiste.replace("'", "$"), ( m_id_type==2 ?def : poch));
    art->updateBDD();
    m_id_artiste = art->id();

    Handle<BDDArtiste> artdef = BDDArtiste::recupererBDD( 1 );

    Handle<BDDAlbum> alb= BDDAlbum::recupererBDD( m_nom_album.replace( "'", "$" ),  poch, m_annee, BDDType::RecupererType( m_id_type ), m_id_type==2 ?artdef : art  );
    alb->updateBDD();
    m_id_album = alb->id();

    Handle<BDDTitre> tit= BDDTitre::recupererBDD( m_nom_titre.replace( "'", "$" ));
    tit->updateBDD();
    m_id_titre = tit->id();

    Handle<BDDPhys> physav = BDDPhys::RecupererBDD( m_id_album );

    int id_phys = 0;
    if ( physav->id() !=-1 )
    {
        id_phys = 1;
    }

    Handle<BDDRelation> rel= BDDRelation::recupererBDD( alb, art, tit, m_num_piste, m_duree , ( (id_mp3==0 && m_id_support_m==-1) ? 0:1) , ( (id_phys==0 && m_id_support_p==-1) ? 0:1) );

    Handle<BDDMp3> mp3av = BDDMp3::RecupererBDDParRelation( rel->id() );

    if ( mp3av->id() != -1)
    {
        rel->m_mp3 = 1;
    }

    rel->updateBDD();

    m_id_relation = rel->id();

    if ( m_id_support_p !=-1 )
    {
        Handle<BDDPhys> phys = BDDPhys::RecupererBDD( alb, m_ean, BDDSupport::RecupererSupport( m_id_support_p ) , m_commentaires);
        phys->updateBDD();
    }

    if ( m_id_support_m != -1 || id_mp3 == 1 )
    {
        Handle<BDDMp3> mp3 = BDDMp3::RecupererBDD( m_chemin_m.replace("'","$") , rel, BDDSupport::RecupererSupport( m_id_support_m ) );
        mp3->updateBDD();
        m_id_mp3 = mp3->id();
    }
}


void Meta_Titre::SupprimerBDDMP3()
{
    Handle<BDDMp3> mp3 = BDDMp3::RecupererBDD( m_id_mp3 );
    mp3->supprimerenBDD();

}
void Meta_Titre::SupprimerBDDPhys()
{
    Handle<BDDRelation> rel = BDDRelation::recupererBDD( m_id_relation );
    rel->supprimerenBDDPhys();
    Handle<BDDTitre> tit = BDDTitre::recupererBDD( m_id_titre );
    tit->supprimerenBDD();

}

void Meta_Titre::majTitre()
{

}
