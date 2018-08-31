#include "bddafficherartiste.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddartiste.h"

BddAfficherArtiste::BddAfficherArtiste()
{

}

QStringList BddAfficherArtiste::ListeArtiste()
{
    QStringList liste;

    QString queryStr = "SELECT DISTINCT Artiste FROM Artiste ORDER By Artiste";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Artiste").toString();
    }


    return liste;

}

QStringList BddAfficherArtiste::TitresPourArt(QString rech)
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
int BddAfficherArtiste::RecupererIdArtisteNom( QString Nom_Artiste )
{
    return Handle<BDDArtiste>(BDDArtiste::recupererBDD( Nom_Artiste ))->id();
}
