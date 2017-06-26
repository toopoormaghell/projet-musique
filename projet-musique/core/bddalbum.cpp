#include "bddalbum.h"
#include "bddpoch.h"
#include "util.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddtype.h"
#include "bddartiste.h"
#include "bddtitre.h"

BDDAlbum::BDDAlbum(const QString& album, const BDDPoch& pochette, int annee, const BDDType& type, const BDDArtiste& artiste , QObject* parent):
    IdOwner(-1, parent)
  , m_nom(album)
  , m_pochette(&pochette)
  , m_nomFormate(album)
  , m_annee(annee)
  , m_type(&type)
  , m_artiste(&artiste)
  , m_areTypeAndPochetteSelfCreated(false)

{
    FormaterEntiteBDD(m_nomFormate);
    recupererId();
    if (id() == -1)
        ajouterBDD();
    else
        updateBDD();
}

void BDDAlbum::updateBDD()
{
    QString queryStr = "UPDATE Album SET Album_Formate ='" + m_nomFormate + "', Id_Pochette='" + QString::number( m_pochette->id() ) + "', Annee= '" + QString::number( m_annee ) + "', Id_Artiste= '" + QString::number( m_artiste->id() ) + "'  WHERE Id_Album = '" + QString::number( id() ) + "'";
    madatabase.exec( queryStr );
}


BDDAlbum::~BDDAlbum()
{
    if ( m_areTypeAndPochetteSelfCreated )
    {
        delete m_artiste;
        delete m_type;
        delete m_pochette;
    }
}
void BDDAlbum::recupererId()
{
    QString queryStr = "Select Id_Album As 'Album' from Album WHERE Album_Formate='" + m_nomFormate + "' AND Id_Artiste='" + QString::number( m_artiste->id() ) + "'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        setId(rec.value( "Album" ).toInt());
    }
    else
    {
        setId(-1);
    }
}

BDDAlbum::BDDAlbum(const int id, QObject* parent):
    IdOwner(id, parent)
  , m_nom()
  , m_pochette(NULL)
  , m_nomFormate()
  , m_annee(1)
  , m_type(NULL)
  , m_artiste(NULL)
{
    QString queryStr = "SELECT Album, Album_Formate, Id_Pochette, Annee, Type, Id_Artiste FROM Album WHERE Id_Album='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next())
    {
        QSqlRecord rec = query.record();

        m_nom = rec.value("Album").toString().replace("$", "'");
        m_pochette = BDDPoch::recupererBDD(rec.value("Id_Pochette").toInt());
        m_nomFormate = rec.value("Album_Formate").toString();
        m_annee = rec.value("Annee").toInt();
        m_type = BDDType::RecupererType(rec.value("Type").toInt());
        m_artiste = BDDArtiste::RecupererArtiste(rec.value("Id_artiste").toInt());
        m_areTypeAndPochetteSelfCreated = true;
    }
}

BDDAlbum* BDDAlbum::RecupererAlbum( const int id )
{
    return new BDDAlbum( id );
}

void BDDAlbum::ajouterBDD()
{
    QString queryStr = "INSERT INTO Album VALUES (null,'" + m_nom + "','" + QString::number( m_pochette->id() ) + "','" + m_nomFormate + "','" + QString::number( m_annee ) + "','" + QString::number( m_type->id() ) + "','" + QString::number( m_artiste->id() )+ "')";
    QSqlQuery query = madatabase.exec( queryStr );

    setId(query.lastInsertId().toInt());
}

void BDDAlbum::supprimerenBDD() const
{
    if ( id() != -1 )
    {

        //On vérifie si l'album existe ou non dans la table des relations
        QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Album='" + QString::number( id() ) + "'" ;
        QSqlQuery  query2 = madatabase.exec( queryStri );

        //si la deuxième requête ne renvoie pas de résultat, on efface du coup l'album
        if ( !query2.first() )
        {

            madatabase.exec( "DELETE FROM Album WHERE Id_Album='" + QString::number( id() ) + "'" );

        }

        m_pochette->supprimerenBDD();
        m_artiste->supprimerenBDD();
    }
}
AlbumPhys BDDAlbum::RecupAlbumEntite( const int id )
{
    AlbumPhys albphys;

    //On récupère les infos liées à l'album
    BDDAlbum* alb = BDDAlbum::RecupererAlbum( id );
    albphys.Album = alb->m_nom;
    albphys.Annee = alb->m_annee;
    albphys.Id_Album = alb->id();
    albphys.Poch = alb->m_pochette->m_image;
    albphys.Id_Poch = alb->m_pochette->id();
    albphys.Type = alb->m_type->id();
    albphys.Artiste = alb->m_artiste->m_nom;
    delete alb;

    //On récupère le Type
    BDDType* typ = BDDType::RecupererType( albphys.Type );
    delete typ;

    //On récupère les titres liés à l'album
    QString queryStr = "SELECT DISTINCT R.Id_Titre, R.Duree, R.Num_Piste, R.MP3, R.Phys,  R.Id_Artiste FROM Relations R, Titre T WHERE R.Id_Album='" + QString::number( id ) + "' AND T.Id_Titre=R.Id_Titre ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        TitresPhys titre;
        QSqlRecord rec = query.record();
        BDDTitre*  TitreEnCours = BDDTitre::RecupererTitre( rec.value( "Id_Titre" ).toInt() );
        BDDArtiste* art = BDDArtiste::RecupererArtiste(rec.value( "Id_Artiste" ).toInt());

        titre.Artiste = art->m_nom;
        titre.Duree = rec.value( "Duree" ).toString();
        titre.id = QString::number( TitreEnCours->id() ) ;
        titre.Num_Piste = rec.value( "Num_Piste" ).toInt();
        titre.Titre = TitreEnCours->m_nom;
        titre.MP3Phys = rec.value("MP3").toBool() && rec.value("Phys").toBool();
        titre.MP3 = rec.value("MP3").toBool();
        titre.Phys = rec.value("Phys").toBool();
        albphys.titres << titre;
        delete TitreEnCours;
        delete art;

    }
    return albphys;
}
