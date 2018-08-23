#include "bddphys.h"
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddsupport.h"
#include "bddrelation.h"
#include <QtSql>


BDDPhys::BDDPhys(const int id, const Handle<BDDAlbum>& album, const QString& ean, const BDDSupport* support, const QString& Commentaires,  QObject* parent):
    IdOwner( id , parent)
  , m_album( album )
  , m_support( support )
  , m_ean( ean )
  , m_commentaires( Commentaires )

{

}

BDDPhys::~BDDPhys()
{
    delete m_support;
}

void BDDPhys::supprimerBDD()
{
    if ( id() != 0 )
    {
        QString queryStr = "DELETE FROM Phys WHERE Id_Album='" + QString::number( m_album->id() ) + "'";

        madatabase.exec( queryStr );

        m_album->supprimerenBDD();
    }
}

Handle<BDDPhys> BDDPhys::RecupererBDD( const int id )
{
    Handle<BDDAlbum> alb(nullptr);
    BDDSupport* supp = nullptr;
    QString ean;
    QString commentaires;
    int id_Phys = -1;

    QString queryStr = "SELECT * FROM Phys WHERE Id_Album='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    if (query.first())
    {
        QSqlRecord rec = query.record();

        alb = BDDAlbum::recupererBDD( rec.value ( "Id_Album" ).toInt() );
        supp = BDDSupport::RecupererSupport( rec.value ( "Support").toInt() );
        ean = rec.value("EAN").toString();
        commentaires = rec.value("Commentaire").toString();
        id_Phys = rec.value("Id_Phys").toInt();
    }

    return Handle<BDDPhys>(new BDDPhys( id_Phys, alb, ean, supp, commentaires ));
}

Handle<BDDPhys> BDDPhys::RecupererBDD(const Handle<BDDAlbum>& album, const QString& ean, const BDDSupport& support, const QString& Commentaires)
{
    const int id = recupererId( album->id() );

    return Handle<BDDPhys>(new BDDPhys( id, album, ean, &support, Commentaires ));
}

int BDDPhys::recupererId(const int id_alb )
{
    QString queryStr = "Select Id_Phys As 'Phys' from Phys WHERE Id_Album='" + QString::number( id_alb ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    int id = -1;

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id = rec.value( " Id_Phys " ).toInt();

    }
    return id;
}


void BDDPhys::updateBDD()
{
    if ( id() == -1 )
    {
        QString queryStr = "INSERT INTO Phys VALUES (null,'" + QString::number( m_album->id() ) + "','" + QString::number( m_support->id() ) + "','" + m_ean + "','" + m_commentaires + "')";
        QSqlQuery query =  madatabase.exec( queryStr );
        setId(query.lastInsertId().toInt());
    }
    else
    {
        QString queryStr = "UPDATE Phys SET CodeBarres = '" + m_ean + "', Commentaire = '" + m_commentaires + "', Support = '"+ QString::number( m_support->id() ) +"' WHERE Id_Album ='" + QString::number(m_album->id() ) +"' ";
        madatabase.exec( queryStr );
    }
}
