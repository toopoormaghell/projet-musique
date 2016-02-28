#include "bddrech.h"
#include <QtSql>
#include "bddconfig.h"
#include "util.h"

BDDRech::BDDRech( QObject* parent ) :
    QObject( parent )
{

}

QList<int> BDDRech::RechTitres( QString rech )
{
    QList<int> liste;
    FormaterEntiteBDD( rech );
    QString queryStr = "SELECT DISTINCT Id_Titre FROM Titre WHERE Titre_Formate LIKE '%" + rech + "%'";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Titre" ).toInt();

    }
    return liste;
}

QList<int> BDDRech::RechAlb( QString rech )
{
    QList<int> liste;
    FormaterEntiteBDD( rech );
    QString queryStr = "SELECT DISTINCT Id_Album FROM Album WHERE Album_Formate LIKE '%" + rech + "%'";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Album" ).toInt();

    }
    return liste;
}
QList<int> BDDRech::RechArt( QString rech )
{
    QList<int> liste;
    FormaterEntiteBDD( rech );
    QString queryStr = "SELECT DISTINCT Id_Artiste FROM Artiste WHERE Artiste_Formate LIKE '%" + rech + "%'";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Artiste" ).toInt();

    }
    return liste;
}
