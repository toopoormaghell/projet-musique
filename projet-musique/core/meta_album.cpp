#include "meta_album.h"
#include "bddalbum.h"

Meta_Album::Meta_Album(QObject *parent) : QObject(parent)
{

}
/*
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

QList<Meta_Titre> Meta_Album::gettitres()
{
    return m_titres;
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

void Meta_Album::settitres(QList<Meta_Titre> titres)
{
    m_titres = titres;
}
Meta_Album* Meta_Album::RecupererBDD(const int id)
{
    //On récupère les infos liées à l'album
    BDDAlbum* alb = BDDAlbum::recupererBDD( id );


    albphys.Album = alb->m_nom;
    albphys.Annee = alb->m_annee;
    albphys.Id_Album = alb->id();
    albphys.Poch = alb->m_pochette->m_image;
    albphys.Id_Poch = alb->m_pochette->id();
    albphys.Type = alb->m_type->id();
    albphys.Artiste = alb->m_artiste->m_nom;

    delete alb;

    //On récupère les titres liés à l'album
    QString queryStr = "SELECT DISTINCT Id_Relation FROM Relations RWHERE Id_Album='" + QString::number( id ) + "' ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        Meta_Titre* titre = Meta_Titre::RecupererBDD( rec.value(Id_Relation));

    }
    return
}
*/
