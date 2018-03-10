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

void Meta_Album::setcommentaires(QString commentaires)
{
    m_commentaires = commentaires;
}
void Meta_Album::settitres(QList<Meta_Titre*> titres)
{
    m_titres = titres;
}

Meta_Album::Meta_Album():
    m_nom_album()
  , m_nom_artiste()
  , m_annee(0)
  , m_poch()
  , m_Type()
  , m_titres()
  , m_support_p()
  , m_support_m()
  , m_commentaires()
  , m_ean()
  , m_id_album(0)
  , m_id_artiste(0)
  , m_id_poch(0)
  , m_id_type(0)
  , m_id_support_p(0)
  , m_id_support_m(0)
{

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


        BDDPhys* phys = BDDPhys::RecupererBDD( id );
        commentaires = phys->m_commentaires;
        ean = phys->m_ean;

        //On récupère les titres liés à l'album
        QString queryStr = "SELECT DISTINCT Id_Relation FROM Relations R WHERE Id_Album='" + QString::number( id ) + "' ORDER BY Num_Piste";
        QSqlQuery query = madatabase.exec( queryStr );

        while ( query.next() )
        {
            QSqlRecord rec = query.record();

            Meta_Titre* titre = Meta_Titre::RecupererBDD( rec.value("Id_Relation").toInt());

            titres << titre;

            if ( titre->getid_support_m() != -1 )
                id_support_m = 4;

            if ( titre->getid_support_p() != -1 )
                id_support_p = titre->getid_support_p();
        }
        if ( id_support_m == 4)
        {
            support_m = "MP3";
        }
        if ( id_support_p != -1)
        {
            support_p = BDDSupport::RecupererSupport( id_support_p )->m_support;
        }
    }
    return new Meta_Album(nom_alb,nom_art,Annee,Poch,type,titres,support_p,support_m,commentaires,ean, id_alb,id_art,id_poch,id_type,id_support_p,id_support_m);
}

Meta_Album::~Meta_Album()
{
    for (int i=0; i < m_titres.count() ; i++)
    {

        delete m_titres[i];

    }
}
Meta_Album* Meta_Album::CreerMeta_Album(const QString& nom_album, const QString& nom_artiste, int annee, const QImage& Poch, int type, const QList<Meta_Titre*>& titres, int support_p,  const QString& commentaires, const QString& ean)
{
    return new Meta_Album( nom_album, nom_artiste, annee, Poch, "Aucun", titres, "Aucun", "Aucun", commentaires, ean, -1 , -1, -1 , type, support_p, -1);
}

void Meta_Album::SupprimerBDDPhys()
{
    BDDPhys* phys = BDDPhys::RecupererBDD( m_id_album );
    phys->supprimerBDD();
    delete phys;
}
void Meta_Album::UpdateBDD()
{
   /* BDDPoch* poch = BDDPoch::recupererBDD(Poch, Album, (Support==2 ? "Compil":Artiste));
    poch->updateBDD();

    BDDPoch* def = BDDPoch::recupererBDD(1);

    BDDArtiste* art = BDDArtiste::recupererBDD(Artiste, (Type==2 ?*def : *poch));
    art->updateBDD();
    BDDAlbum* alb= BDDAlbum::recupererBDD( Album, *poch, Annee, *BDDType::RecupererType(Type), *art );
    alb->updateBDD();

    for ( int cpt = 0; cpt < titres.count(); cpt++ )
    {
        Meta_Titre temp = titres[cpt];
        BDDTitre* tit = BDDTitre::recupererBDD( temp.Titre.replace( "'", "$" ) );
        tit->updateBDD();
        if ( Type == 2 )
        {
            BDDArtiste* artTitre = BDDArtiste::recupererBDD(temp.Artiste, *def);
            artTitre->updateBDD();
            BDDRelation* rel = BDDRelation::recupererBDD( *alb, *artTitre, *tit, temp.Num_Piste, temp.Duree, 0,1 );
            rel->updateBDD();

        }
        else
        {
            BDDRelation* rel = BDDRelation::recupererBDD( *alb, *art, *tit, temp.Num_Piste, temp.Duree, 0,1 );
            rel->updateBDD();
        }
    }

    BDDPhys* phys = BDDPhys::RecupererBDD( *alb, ean, *BDDSupport::RecupererSupport(Support), Commentaires );
    phys->updateBDD();

    */
}
