#include "meta_album.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtype.h"
#include "bddpoch.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddphys.h"

Meta_Album::Meta_Album(const QString& nom_album, const QString& nom_artiste, int annee, QImage& Poch, const QString& Type, const QList<Meta_Titre*>& titres, const QString& support_p, const QString& commentaires, int id_album, int id_artiste, int id_poch, int id_type, int id_support_p, QObject* parent ):
    m_nom_album ( nom_album )
  , m_nom_artiste ( nom_artiste )
  , m_annee ( annee )
  , m_poch ( Poch )
  , m_Type ( Type )
  , m_titres ( titres )
  , m_support_p ( support_p )
  , m_commentaires ( commentaires )
  , m_id_album ( id_album )
  , m_id_artiste ( id_artiste)
  , m_id_poch ( id_poch)
  , m_id_type ( id_type)
  , m_id_support_p ( id_support_p )
{

    Q_UNUSED ( parent );
}

QString Meta_Album::getnom_album()
{
    return m_nom_album;
}

QString Meta_Album::getnom_artiste()
{
    return m_nom_artiste;
}

int Meta_Album::getannee()
{
    return m_annee;
}

QString Meta_Album::gettype()
{
    return m_Type;
}

QList<Meta_Titre*> Meta_Album::gettitres()
{
    return m_titres;
}
QImage Meta_Album::getPoch()
{
    return m_poch;
}

QString Meta_Album::getsupport_p()
{
    return m_support_p;
}

int Meta_Album::getid_alb()
{
    return m_id_album;
}

int Meta_Album::getid_support_p()
{
    return m_id_support_p;
}

QString Meta_Album::getcommentaires()
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

void Meta_Album::setsupport_p(QString support_p)
{
    m_support_p = support_p;
}
void Meta_Album::settitres(QList<Meta_Titre*> titres)
{
    m_titres = titres;
}

Meta_Album* Meta_Album::RecupererBDD(const int id)
{
    int Annee=-1, id_alb=-1, id_art =-1, id_poch=-1, id_type =-1, id_support_p=-1;
    QString nom_alb, nom_art, type, support_p, commentaires ;
    QImage Poch;
    QList<Meta_Titre*> titres;

    //On récupère les infos liées à l'album
    BDDAlbum* alb = BDDAlbum::recupererBDD( id );

    nom_alb = alb->m_nom;
    Annee = alb->m_annee;
    id_alb = alb->id();
    Poch = alb->m_pochette->m_image;
    id_poch = alb->m_pochette->id();
    id_type = alb->m_type->id();
    type = alb->m_type->m_type;
    nom_art = alb->m_artiste->m_nom;
    id_art = alb->m_artiste->id();

    delete alb;

    BDDPhys* phys = BDDPhys::RecupererPhys( id );
    commentaires = phys->m_commentaires;

    //On récupère les titres liés à l'album
    QString queryStr = "SELECT DISTINCT Id_Relation FROM Relations R WHERE Id_Album='" + QString::number( id ) + "' ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        Meta_Titre* titre = Meta_Titre::RecupererBDD( rec.value("Id_Relation").toInt());

        titres << titre;

        support_p = titre->getsupportphys();
        id_support_p = titre->getid_support_p();

    }
    return new Meta_Album(nom_alb,nom_art,Annee,Poch,type,titres,support_p,commentaires, id_alb,id_art,id_poch,id_type,id_support_p);
}

Meta_Album::~Meta_Album()
{
    for (int i=0; i < m_titres.count() ; i++)
    {

          delete m_titres[i];

    }
}

