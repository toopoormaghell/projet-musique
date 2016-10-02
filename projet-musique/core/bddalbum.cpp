#include "bddalbum.h"
#include "bddpoch.h"
#include "util.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddtype.h"
#include "bddartiste.h"
#include "bddtitre.h"

BDDAlbum::BDDAlbum(const QString& album, const BDDPoch& pochette, int annee, int type, const BDDArtiste& artiste , QObject* parent) :
    QObject( parent ),
    m_nom( album ),
    m_nomFormate( album ),
    m_annee( annee ),
    m_type( BDDType::RecupererType( type ) ),
    m_pochette ( &pochette),
    m_artiste ( &artiste ),
    m_areTypeAndPochetteSelfCreated( false )

{
    m_id = -1;
    FormaterEntiteBDD( m_nomFormate );
    recupererId();
    if ( m_id == -1 )
    {
        ajouterBDD();
    }
    else
    {
        updateBDD();
    }
}

void BDDAlbum::updateBDD()
{
    QString queryStr = "UPDATE Album SET Album_Formate ='" + m_nomFormate + "', Id_Pochette='" + QString::number( m_pochette->m_id ) + "', Annee= '" + QString::number( m_annee ) + "', Id_Artiste= '" + QString::number( m_artiste->m_id ) + "'  WHERE Id_Album = '" + QString::number( m_id ) + "'";
    madatabase.exec( queryStr );
}


BDDAlbum::~BDDAlbum()
{
    if ( m_areTypeAndPochetteSelfCreated )
    {
        delete m_type;
        delete m_pochette;
        delete m_artiste;
    }
}
void BDDAlbum::recupererId()
{
    QString queryStr = "Select Id_Album As 'Album' from Album WHERE Album_Formate='" + m_nomFormate + "' AND Id_Artiste='" + QString::number( m_artiste->m_id ) + "'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Album" ).toInt();
    }
    else
    {
        m_id = -1;
    }
}

BDDAlbum::BDDAlbum( const int id, QObject* parent ):
    QObject( parent ),
    m_id( id ),
    m_nom(),
    m_nomFormate(),
    m_annee( 1 ),
    m_type(),
    m_pochette(),
    m_artiste()
{
    QString queryStr = "SELECT Album,Album_Formate,Id_Pochette, Annee, Type, Id_Artiste FROM Album WHERE Id_Album='" + QString::number( id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        m_nom = rec.value( "Album" ).toString().replace( "$", "'" );
        m_nomFormate = rec.value( "Album_Formate" ).toString();
        m_annee = rec.value( "Annee" ).toInt();
        m_type = BDDType::RecupererType( rec.value( "Type" ).toInt() );
        m_pochette = BDDPoch::recupererBDD( rec.value( "Id_Pochette" ).toInt() );
        m_areTypeAndPochetteSelfCreated = true;
        m_artiste = BDDArtiste::RecupererArtiste(rec.value("Id_artiste").toInt());

    }
}
BDDAlbum* BDDAlbum::RecupererAlbum( const int id )
{
    return new BDDAlbum( id );
}

void BDDAlbum::ajouterBDD()
{
    QString queryStr = "INSERT INTO Album VALUES (null,'" + m_nom + "','" + QString::number( m_pochette->m_id ) + "','" + m_nomFormate + "','" + QString::number( m_annee ) + "','" + QString::number( m_type->m_id ) + "','" + QString::number( m_artiste->m_id )+ "')";
    QSqlQuery query = madatabase.exec( queryStr );

    m_id = query.lastInsertId().toInt();
}

void BDDAlbum::supprimerenBDD() const
{

    //On vérifie si l'album existe ou non dans la table des relations
    QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Album='" + QString::number( m_id ) + "'" ;
    QSqlQuery  query2 = madatabase.exec( queryStri );

    //si la deuxième requête ne renvoie pas de résultat, on efface du coup l'album
    if ( !query2.first() )
    {

        madatabase.exec( "DELETE FROM Album WHERE Id_Album='" + QString::number( m_id ) + "'" );

    }
    m_pochette->supprimerenBDD();
}
AlbumPhys BDDAlbum::RecupAlbumEntite( const int id )
{
    AlbumPhys albphys;

    //On récupère les infos liées à l'album
    BDDAlbum* alb = BDDAlbum::RecupererAlbum( id );
    albphys.Album = alb->m_nom;
    albphys.Annee = alb->m_annee;
    albphys.Id_Album = alb->m_id;
    albphys.Poch = alb->m_pochette->m_image;
    albphys.Id_Poch = alb->m_pochette->m_id;
    albphys.Type = alb->m_type->m_id;
    albphys.Artiste = alb->m_artiste->m_nom;
    delete alb;

    //On récupère le Type
    BDDType* typ = BDDType::RecupererType( albphys.Type );
    albphys.Type_Str = typ->m_type;

    //On récupère les titres liés à l'album
    QString queryStr = "SELECT DISTINCT R.Id_Titre FROM Relations R, Titre T WHERE R.Id_Album='" + QString::number( id ) + "' AND T.Id_Titre=R.Id_Titre ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        TitresPhys titre;
        QSqlRecord rec = query.record();
        BDDTitre*  TitreEnCours = BDDTitre::RecupererTitre( rec.value( "Id_Titre" ).toInt() );

        titre.Artiste = TitreEnCours->m_artiste->m_nom;
        titre.Duree = TitreEnCours->m_duree;
        titre.id = QString::number( TitreEnCours->m_id ) ;
        titre.Num_Piste = TitreEnCours->m_num_piste;
        titre.Titre = TitreEnCours->m_nom;
        titre.MP3Phys = TitreEnCours->m_mp3 && TitreEnCours->m_phys;
        titre.MP3 = TitreEnCours->m_mp3;
        titre.Phys = TitreEnCours->m_phys;
        albphys.titres << titre;

    }
    return albphys;
}
