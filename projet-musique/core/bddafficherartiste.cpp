#include "bddafficherartiste.h"
#include <QtSql>
#include "bddsingleton.h"

BddAfficherArtiste::BddAfficherArtiste()
{

}

QList<int> BddAfficherArtiste::ListeArtiste()
{
    QList<int> liste;

    QString queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A ORDER By Artiste";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Artiste" ).toInt();
    }


    return liste;

}

QList<int> BddAfficherArtiste::TitresPourArt(QString rech)
{
    QList<int> liste;
    QString queryStr = "SELECT R.Id_Titre, R.Id_Relation FROM Relations R, Titre T WHERE R.Id_Artiste = '" + rech + "' AND T.Id_Titre = R.Id_Titre ORDER BY T.Titre ";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        liste << rec.value( "Id_Titre" ).toInt();
        liste << rec.value( "Id_Relation" ).toInt();

    }
    return liste;
}

QList<int> BddAfficherArtiste::AlbumsPourArt(QString rech)
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
QList<int> BddAfficherArtiste::AlbPourTitre(QString rech)
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
QList<int> BddAfficherArtiste::TitresPourAlbum( int id )
{
    QList<int> liste;
    QString queryStr = "SELECT DISTINCT Id_Relation FROM Relations WHERE  Id_Album = "+ QString::number( id ) +" ORDER BY Num_Piste ";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Relation" ).toInt();

    }
    return liste;
}
