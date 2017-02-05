#include "bddphys.h"
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddtype.h"
#include "bddrelation.h"
#include <QtSql>


BDDPhys::BDDPhys(const BDDAlbum& album, const QString& ean, const int& type, const QString& Commentaires, QObject* parent ):
    QObject( parent ),
    m_id( -1 ),
    m_album( &album ),
    m_artiste( NULL ),
    m_relations(),
    m_type( BDDType::RecupererType( type ) ),
    m_ean( ean ),
    m_commentaires ( Commentaires),
    m_membersAreSelfCreatad( false )
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
BDDPhys::~BDDPhys()
{
    if ( m_membersAreSelfCreatad )
    {
        m_id = 0;
        m_ean = "";
        delete m_artiste;
        delete m_album;
        delete m_type;
        for ( int i = 0; i < m_relations.count(); ++i )
            delete m_relations[i];
        m_relations.clear();
    }
}

void BDDPhys::deleteBDD()
{
    QString queryStr = "DELETE FROM Phys WHERE Id_Album='" + QString::number( m_id ) + "'";

    madatabase.exec( queryStr );

    for ( int i = 0; i < m_relations.count(); i++ )
    {
        if ( !m_relations[i]->m_mp3 )
        {
     /*       BDDRelation rel( *m_album, *m_artiste, *m_relations[i],  );
            rel.supprimerenBDDPhys();
            m_relations[i]->supprimerenBDD();
     */   }
    }
    m_album->supprimerenBDD();
    m_artiste->supprimerenBDD();

}

BDDPhys* BDDPhys::RecupererPhys( const int id )
{
    return new BDDPhys( id );
}

void BDDPhys::ajouterBDD()
{
    QString queryStr = "INSERT INTO Phys VALUES (null,'" + QString::number( m_album->m_id ) + "','" + QString::number( m_type->m_id ) + "','" + m_ean + "','" + m_commentaires + "')";
    QSqlQuery query =  madatabase.exec( queryStr );
    m_id = query.lastInsertId().toInt();
}

void BDDPhys::recupererId()
{
    QString queryStr = "Select Id_Phys As 'Phys' from Phys WHERE Id_Album='" + QString::number( m_album->m_id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( " Id_Phys " ).toInt();

    }
    else
    {
        m_id = -1;
    }
}

BDDPhys::BDDPhys( const int id, QObject* parent ):
    QObject( parent ),
    m_id( id ),
    m_album( NULL ),
    m_artiste( NULL ),
    m_relations(),
    m_type(),
    m_ean( -1 ),
    m_commentaires()
{
    Q_UNUSED( parent );
    QString queryStr = "SELECT * FROM Phys WHERE Id_Album='" + QString::number( id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        m_type = BDDType::RecupererType( rec.value( "Categorie" ).toInt() );
        m_album = BDDAlbum::RecupererAlbum( rec.value( "Id_Album" ).toInt() );
        m_commentaires = rec.value("Commentaire").toString();
        RecupererTitres();
        m_membersAreSelfCreatad = true;
    }
}
void BDDPhys::RecupererTitres()
{
    QString queryStr = " SELECT Id_Relation, Id_Artiste FROM Relations  WHERE Id_Album='" + QString::number( m_album->m_id ) + "' ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        delete m_artiste;
        m_artiste = BDDArtiste::RecupererArtiste( rec.value( "Id_Artiste" ).toInt() );
        m_relations <<   BDDRelation::RecupererRelation( rec.value( "Id_Relation" ).toInt() );

    }
}
void BDDPhys::updateBDD()
{

    QString queryStr = "UPDATE Phys SET CodeBarres = '" + m_ean + "', Commentaire = '" + m_commentaires + "', Categorie = '"+ QString::number( m_type->m_id ) +"' WHERE Id_Album ='" + QString::number(m_album->m_id ) +"' ";
    madatabase.exec( queryStr );

}
