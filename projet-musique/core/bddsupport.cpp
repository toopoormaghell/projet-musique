#include "bddsupport.h"
#include <QtSql>
#include "bddsingleton.h"


BDDSupport* BDDSupport::RecupererSupport( const int id )
{
    return new BDDSupport( id );
}

BDDSupport::BDDSupport( const int id, QObject* parent ):
    IdOwner(id, parent)
  , m_support()
{
    QString queryStr = "SELECT Support FROM Support WHERE Id_Support='" + QString::number( id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        m_support = rec.value( "Support" ).toString();

    }

}
QList<int> BDDSupport::NbSupport()
{
    QList<int> supp;
    QString queryStr = "SELECT Id_Support FROM Support";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        supp << rec.value( "Id_Support" ).toInt();

    }
    return supp;
}
