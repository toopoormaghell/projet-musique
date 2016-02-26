#include "bddrelation.h"
#include "util.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddtitre.h"
#include "bddalbum.h"
#include "bddartiste.h"

BDDRelation::BDDRelation( const BDDAlbum& album, const BDDArtiste& artiste, const BDDTitre& titre, QObject* parent ) :
    QObject( parent ),
    m_id( -1 ),
    m_id_artiste( artiste.m_id ),
    m_id_album( album.m_id ),
    m_id_titre( titre.m_id )
{

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
void BDDRelation::recupererId()
{
    //on vérifie si la relation existe ou non
    QString queryStr = "SELECT Id_Relation from Relations WHERE Id_Titre='" + QString::number( m_id_titre ) + "' AND Id_Artiste='" + QString::number( m_id_artiste ) + "' AND Id_Album='" + QString::number( m_id_album ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Id_Relation" ).toInt();
    }
    else
    {
        m_id = -1;
    }
}
void BDDRelation::updateBDD()
{

}

BDDRelation* BDDRelation::RecupererRelation( const int id )
{
    return new BDDRelation( id );
}

BDDRelation::BDDRelation( const int id, QObject* parent ):
    QObject( parent ),
    m_id( id ),
    m_id_artiste(),
    m_id_album(),
    m_id_titre()
{
    QString queryStr = "SELECT Id_Titre, Id_Album, Id_Artiste FROM Relations WHERE Id_Relation='" + QString::number( id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        m_id_album = rec.value( "Id_Album" ).toInt();
        m_id_artiste = rec.value( "Id_Artiste" ).toInt();
        m_id_titre = rec.value( "Id_Titre" ).toInt();
    }
}

void BDDRelation::ajouterBDD()
{
    QString  queryStr = "INSERT INTO Relations VALUES (null,'" + QString::number( m_id_titre ) + "','" + QString::number( m_id_album ) + "','" + QString::number( m_id_artiste ) + "')";

    QSqlQuery query =     madatabase.exec( queryStr );
    m_id = query.lastInsertId().toInt();

}

void BDDRelation::supprimerenBDDMP3() const
{

    QString queryStr = "SELECT Id_Phys FROM Phys WHERE Id_Album='" + QString::number( m_id_album ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );

    if ( !query.first() )
    {

        madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( m_id ) + "'" );
    }

}
void BDDRelation::supprimerenBDDPhys() const
{

    QString queryStr = "SELECT Id_Mp3 FROM MP3 WHERE Id_Relation='" + QString::number( m_id ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );

    if ( !query.first() )
    {

        madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( m_id ) + "'" );
    }

}
