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
    QString queryStr = "SELECT DISTINCT Id_Relation FROM Titre T, Relations R WHERE T.Titre_Formate LIKE '%" + rech + "%' AND R.Id_Titre= T.Id_Titre ORDER BY T.Titre";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Relation" ).toInt();

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
    QString queryStr = "SELECT DISTINCT Id_Relation FROM Relations WHERE Id_Album = '" + rech + "'  ORDER BY Num_Piste";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Relation" ).toInt();

    }
    return liste;
}

QStringList BDDRech::TitresPourArt(QString rech)
{
    QStringList liste;
    QString queryStr = "SELECT T.Titre AS 'Titre', group_concat (B.Album) AS concat_titre FROM Relations R, Titre T, Album B WHERE R.Id_Artiste ='"+ rech +"'  AND T.Id_Titre = R.Id_Titre AND R.Id_Album = B.Id_Album GROUP BY T.Id_Titre  ORDER BY T.Titre ";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        QString temp = rec.value( "Titre" ).toString().replace("$", "'") + " ( " + rec.value("concat_titre").toString().replace("$", "'") + " )";

        liste << temp;

    }
    return liste;
}

QList<int> BDDRech::AlbumsPourArt(QString rech)
{
    QList<int> liste;
    QString queryStr = "SELECT DISTINCT A.Id_Album FROM Album A, Relations R WHERE R.Id_Artiste = '" + rech + "' AND A.Id_Album = R.Id_Album ORDER BY A.Type, A.Album ";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Album" ).toInt();

    }
    return liste;
}
QList<int> BDDRech::AlbPourTitre(QString rech)
{
    QList<int> listeAlbums;
    QString queryStr = "SELECT DISTINCT Id_Album FROM Relations WHERE Id_Titre = '" + rech + "' ";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        listeAlbums << rec.value( "Id_Album" ).toInt();
    }
    return listeAlbums;
}
