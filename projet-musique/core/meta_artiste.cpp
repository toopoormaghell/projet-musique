#include "meta_artiste.h"
#include "bddpoch.h"
#include "bddartiste.h"


Meta_Artiste* Meta_Artiste::RecupererBDD(const int id)
{
    int id_artiste = -1 , id_poch = -1;
    QString nom_art;
    QImage Poch;

    //On récupère les infos liées à l'artiste
    BDDArtiste* art = BDDArtiste::recupererBDD( id );

    nom_art = art->m_nom;
    Poch = art->m_pochette->m_image;
    id_artiste = art->id();
    id_poch = art->m_pochette->id();

    delete art;

    return new Meta_Artiste( nom_art,Poch,id_artiste,id_poch );
}

Meta_Artiste::~Meta_Artiste()
{

}

QString Meta_Artiste::getNom_Artiste()
{
    return m_nom_artiste;
}

QImage Meta_Artiste::getPoch()
{
    return m_poch;
}

int Meta_Artiste::get_id_artiste()
{
    return m_id_artiste;
}

int Meta_Artiste::get_id_poch()
{
    return m_id_poch;
}

Meta_Artiste::Meta_Artiste(const QString& nom_artiste, QImage& Poch, int id_artiste, int id_poch, QObject* parent):
    m_nom_artiste ( nom_artiste )
  , m_poch ( Poch )
  , m_id_artiste ( id_artiste )
  , m_id_poch ( id_poch )
{

    Q_UNUSED ( parent );
}
