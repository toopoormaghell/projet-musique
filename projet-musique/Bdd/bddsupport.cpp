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
BDDSupport* BDDSupport::RecupererSupportAlb(int Id , QString Categorie)
{
    QString queryStr;
    if ( Categorie == "MP3" )
    {
        queryStr = "SELECT Support FROM MP3 M, Relations R WHERE M.Id_Relation = R.Id_Relation AND R.Id_Album ='"+ QString::number( Id) +"'";
    } else
    {
        queryStr = " SELECT Support FROM Phys WHERE Id_Album ='"+ QString::number( Id) +"'";
    }
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        return RecupererSupport( rec.value( "Support" ).toInt() );
    }
    return RecupererSupport(-1);
}
