#include "bddartiste.h"
#include "bddsingleton.h"
#include "bddpoch.h"
#include <QtSql>
#include <QtGui>
#include "util.h"

BDDArtiste::BDDArtiste(const QString& artiste, const BDDPoch& pochette, QObject* parent) :
    QObject( parent ),
    m_id( -1 ),
    m_nom( artiste ),
    m_pochette( &pochette ),
    m_nomFormate( artiste ),
    m_isPochetteSelfCreated( false )
{
    QString art = artiste;
    TrouverId( art );

    if ( m_id == -1 )
        ajouterBDD();
    else
        updateBDD();

}

BDDArtiste::~BDDArtiste()
{
    if ( m_isPochetteSelfCreated )
        delete m_pochette;
}

void BDDArtiste::recupererId()
{

    QString queryStr = "Select Id_Artiste As 'Artiste', Id_Pochette AS 'Poch' from Artiste WHERE Artiste_Formate='" + m_nomFormate + "'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Artiste" ).toInt();
        m_pochette = BDDPoch::recupererBDD(rec.value("Poch").toInt());
        m_isPochetteSelfCreated = true;
    }
    else
    {
        m_id = -1;
    }
}

void BDDArtiste::ajouterBDD()
{

    QString queryStr = "INSERT INTO Artiste VALUES (null,'" + m_nom + "','" + QString::number( m_pochette->m_id ) + "','" + m_nomFormate + "')";
    QSqlQuery query = madatabase.exec( queryStr );
    m_id = query.lastInsertId().toInt();
}

BDDArtiste* BDDArtiste::RecupererArtiste( const int id )
{
    return new BDDArtiste( id );
}

BDDArtiste::BDDArtiste( const int id , QObject* parent ):
    QObject( parent ),
    m_id( id ),
    m_nom(),
    m_pochette(),
    m_nomFormate()
{
    QString queryStr = "SELECT Artiste, Artiste_Formate, Id_Pochette FROM Artiste WHERE Id_Artiste='" + QString::number( id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        m_nom = rec.value( "Artiste" ).toString().replace( "$", "'" );;
        m_nomFormate = rec.value( "Artiste_Formate" ).toString();
        m_pochette = BDDPoch::recupererBDD( rec.value( "Id_Pochette" ).toInt() );
        m_isPochetteSelfCreated = true;
    }
}
BDDArtiste::BDDArtiste( const QString& artiste, QObject* parent ):
    QObject( parent ),
    m_id( 0 ),
    m_nom( artiste ),
    m_pochette(),
    m_nomFormate( artiste )
{
    TrouverId( m_nom );
    QString queryStr = "SELECT Artiste, Artiste_Formate, Id_Pochette FROM Artiste WHERE Id_Artiste='" + QString::number( m_id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        m_nom = rec.value( "Artiste" ).toString().replace( "$", "'" );;
        m_nomFormate = rec.value( "Artiste_Formate" ).toString();
        m_pochette = BDDPoch::recupererBDD( rec.value( "Id_Pochette" ).toInt() );
        m_isPochetteSelfCreated = true;
    }

}

BDDArtiste* BDDArtiste::RecupererArtparNom( QString& nom )
{
    return new BDDArtiste( nom );
}

void BDDArtiste::TrouverId( QString& nom )
{
    m_id = -1;
    ChoisirArtisteEchange( nom );
    m_nomFormate = nom;
    FormaterEntiteBDD( m_nomFormate );
    recupererId();
}

void BDDArtiste::updateBDD()
{
    QString queryStri = " UPDATE Artiste SET Artiste ='" + m_nom + "', Artiste_Formate='" + m_nomFormate + "', Id_Pochette='" + QString::number( m_pochette->m_id ) + "' WHERE Id_Artiste='" + QString::number( m_id ) + "'";
    madatabase.exec( queryStri );

}

void BDDArtiste::supprimerenBDD() const
{
    //On vérifie si l'artiste existe ou non dans la table des relations
    QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Artiste='" + QString::number( m_id ) + "'" ;
    QSqlQuery  query2 = madatabase.exec( queryStri );

    //si la requête ne renvoie pas de résultat, on efface du coup l'artiste
    if ( !query2.first() )
    {

        madatabase.exec( "DELETE FROM Artiste WHERE Id_Artiste='" + QString::number( m_id ) + "'" );

    }
    m_pochette->supprimerenBDD();
}

void BDDArtiste::EchangerArtiste( QString& nom )
{
    QStringList temp = nom.split( " " );
    if ( temp.size() == 2 )
    {
        nom = temp[1] + " " + temp[0];
    }
    if ( temp.size() == 3 )
    {
        nom = temp[1] + " " + temp[2] + " " + temp[0];
    }

}
void BDDArtiste::ChoisirArtisteEchange( QString& nom )
{
    QString temp = nom;
    FormaterEntiteBDD( nom );
    QString queryStri = "SELECT Artiste FROM Artiste WHERE Artiste_Formate='" + nom + "'";
    QSqlQuery query = madatabase.exec( queryStri );

    if ( !query.first() )
    {
        nom = temp;
        EchangerArtiste( nom );
        FormaterEntiteBDD( nom );
        queryStri = "SELECT Artiste FROM Artiste WHERE Artiste_Formate='" + nom + "'";
        query = madatabase.exec( queryStri );
        if ( query.first() )
        {
            QSqlRecord rec = query.record();
            m_nom = rec.value( "Artiste" ).toString();
            m_nomFormate = nom;
        }
    }
}

void BDDArtiste::deleteArtiste()
{
    delete m_pochette;

}
