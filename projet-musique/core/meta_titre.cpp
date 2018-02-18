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


Meta_Titre* Meta_Titre::RecupererBDD(const int id)
{

    QString queryStr = "SELECT Id_Album, Id_Artiste, Id_Titre , Num_Piste, MP3 , Phys, Duree  FROM Relations WHERE Id_Relation='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    QString nom_Alb, nom_Art , nom_Tit, duree, type, support_m, support_p, chemin_m ;
    int annee=-1, num_piste=-1 , id_alb=-1, id_art=-1, id_tit=-1, id_type =-1, id_support_m=-1 , id_support_p =-1;
    QImage poch;


    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        //Album
        BDDAlbum* alb = BDDAlbum::recupererBDD(rec.value("Id_Album").toInt());
        nom_Alb = alb->m_nom;
        id_alb = alb->id();
        poch = alb->m_pochette->m_image;
        annee = alb->m_annee;
        type = alb->m_type->m_type;
        id_type = alb->m_type->id();

        //Artiste
        BDDArtiste* art = BDDArtiste::recupererBDD(rec.value("Id_Artiste").toInt());
        nom_Art = art->m_nom;
        id_art = art->id();

        //Titre
        BDDTitre* tit = BDDTitre::recupererBDD(rec.value("Id_Titre").toInt());
        id_tit = tit->id();
        nom_Tit = tit->m_nom;

        if ( rec.value("Phys").toInt() == 1 )
        {
            BDDSupport* supp = BDDSupport::RecupererSupportAlb( id_alb, "Phys" );
            id_support_p = supp->id();
            support_p = supp->m_support;

       delete supp;
        } else
        {
            id_support_p = -1;
            support_p = "Aucun";
        }

        if ( rec.value("MP3").toInt() == 1 )
        {
            BDDSupport* supp = BDDSupport::RecupererSupportAlb( id_alb, "MP3" );
            id_support_m = supp->id();
            support_m = supp->m_support;
            BDDMp3* mp3 = BDDMp3::RecupererMP3ParRelation( id );
            chemin_m = mp3->m_chemin;

           delete supp; delete mp3;

        } else
        {
            id_support_m = -1;
            support_m = "Aucun";
            chemin_m = "Aucun";
        }

        num_piste = rec.value("Num_Piste").toInt();
        duree =  rec.value("Duree").toString();

     delete alb ; delete art; delete tit;
    }


    return new Meta_Titre(nom_Alb,nom_Art,nom_Tit,annee,duree,num_piste,poch,type,support_p, support_m , chemin_m, id_alb,id_art,id_tit,id,id_type,id_support_p,id_support_m);
}

QString Meta_Titre::getnom_album()
{
    return m_nom_album;
}

QString Meta_Titre::getnom_artiste()
{
    return m_nom_artiste;
}

QString Meta_Titre::getnom_titre()
{
    return m_nom_titre;
}

int Meta_Titre::getannee()
{
    return m_annee;
}

QString Meta_Titre::getduree()
{
    return m_duree;
}

int Meta_Titre::getnum_piste()
{
    return m_num_piste;
}

QString Meta_Titre::gettype()
{
    return m_Type;
}

QString Meta_Titre::getsupportphys()
{
    return m_Support_p;
}
QString Meta_Titre::getsupportmp3()
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

QString Meta_Titre::getcheminmp3()
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

QImage Meta_Titre::getpoch()
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
void Meta_Titre::setnom_album( QString nom )
{
    m_nom_album = nom;
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

void Meta_Titre::setsupportphys(QString support)
{
    m_Support_p = support;
}
void Meta_Titre::setsupportmp3(QString support)
{
    m_Support_m = support;
}
void Meta_Titre::setcheminmp3(QString chemin)
{
    m_chemin_m = chemin;
}

Meta_Titre::Meta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m, QObject* parent):
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
  , m_id_album ( id_alb )
  , m_id_artiste ( id_art )
  , m_id_titre ( id_titre )
  , m_id_relation ( id_relation )
  , m_id_type (id_type )
  , m_id_support_p ( id_support_p )
  , m_id_support_m ( id_support_m )

{
Q_UNUSED ( parent );
}
Meta_Titre::~Meta_Titre()
{

}
void Meta_Titre::ChangerDonnees(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support_p, const QString& support_m, const QString& chemin_m, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support_p, int id_support_m)
{

}
