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

Meta_Titre::Meta_Titre(const QString& nom_album, const QString& nom_artiste, const QString& nom_titre, int annee, const QString& duree, int num_piste, const QImage& poch, const QString& type, const QString& support, int id_alb, int id_art, int id_titre, int id_relation, int id_type, int id_support, bool MP3 , QObject* parent ):
    m_nom_album ( nom_album)
  , m_nom_artiste( nom_artiste )
  , m_nom_titre ( nom_titre )
  , m_annee ( annee )
  , m_duree ( duree )
  , m_num_piste ( num_piste )
  , m_poch ( poch )
  , m_Type ( type )
  , m_Support_phys ( support )
  , m_MP3 ( MP3 )
  , m_id_album ( id_alb )
  , m_id_artiste ( id_art )
  , m_id_titre ( id_titre )
  , m_id_relation ( id_relation )
  , m_id_type ( id_type )
  , m_id_support_phys ( id_support )

{
    Q_UNUSED ( parent );
}

Meta_Titre* Meta_Titre::RecupererBDD(const int id)
{

    QString queryStr = "SELECT Id_Album, Id_Artiste, Id_Titre , Num_Piste, MP3 , Phys  FROM Relations WHERE Id_Relation='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    QString nom_Alb, nom_Art, nom_Tit, duree, type, support ;
    int annee, num_piste , id_alb, id_art, id_tit, id_type, id_support ;
    bool MP3;
    QImage poch;
    id_support = -1;
    support = "Pas de support physique";

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
            BDDSupport* supp = BDDSupport::RecupererSupport( id_alb );
            id_support = supp->id();
            support = supp->m_support;
        }

        if ( rec.value("MP3").toInt() == 1 )
        {
            MP3 = true;
        } else
        {
            MP3 = false;
        }

        num_piste = rec.value("Num_Piste").toInt();
    }

    return new Meta_Titre(nom_Alb,nom_Art,nom_Tit,annee,duree,num_piste,poch,type,support,id_alb,id_art,id_tit,id,id_type,id_support,MP3);
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

QString Meta_Titre::getsupport()
{
    return m_Support_phys;
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

void Meta_Titre::setsupport(QString support)
{
    m_Support_phys = support;
}