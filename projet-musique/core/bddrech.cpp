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
    QString queryStr = "SELECT DISTINCT Id_Titre FROM Titre WHERE Titre_Formate LIKE '%" + rech + "%' ORDER BY Titre";

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
    QString queryStr = "SELECT DISTINCT Id_Album FROM Album WHERE Album_Formate LIKE '%" + rech + "%' ORDER BY Album ";

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
    QString queryStr = "SELECT DISTINCT Id_Artiste FROM Artiste WHERE Artiste_Formate LIKE '%" + rech + "%' ORDER BY Artiste";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Artiste" ).toInt();

    }
    return liste;
}

QList<int> BDDRech::TitresPourAlb(QString rech)
{
    QList<int> liste;
    QString queryStr = "SELECT DISTINCT R.Id_Titre FROM Relations R, Titre T WHERE R.Id_Album = '" + rech + "' AND R.Id_Titre = T.Id_Titre ORDER BY T.Num_Piste";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Titre" ).toInt();

    }
    return liste;
}

QList<int> BDDRech::AlbumsPourArt(QString rech)
{
    QList<int> liste;
    QString queryStr = "SELECT DISTINCT A.Id_Album FROM Album A, Relations R WHERE R.Id_Artiste = '" + rech + "' AND A.Id_Album = R.Id_Album ORDER BY A.Album ";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Album" ).toInt();

    }
    return liste;
}
QString BDDRech::AlbPourTitre(QString rech)
{
    QString queryStr = "SELECT Id_Album FROM Relations WHERE Id_Titre = '" + rech + "' ";

    QSqlQuery query = madatabase.exec( queryStr );

    query.next();
    QSqlRecord rec = query.record();

    return rec.value( "Id_Album" ).toString();

}
