#include "bddaffichermp3.h"
#include <QStringList>
#include <QtSql>
#include "bddtype.h"
#include "bddconfig.h"


BDDAfficherMp3::BDDAfficherMp3( QObject* parent ) :
    QObject( parent )
{
}
QList<int> BDDAfficherMp3::ListeArtiste( QString type )
{

    QList<int> liste;

    if ( type != "2" )
    {
        QString queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B,Relations R WHERE A.Id_Artiste!='01' AND R.Id_Album=B.Id_Album AND R.Id_Artiste=A.Id_Artiste";

        if ( type != "0" )
        {
            queryStr = queryStr + " AND B.Type='" + type + "'";
        }
        queryStr = queryStr + " ORDER BY Artiste";

        QSqlQuery query = madatabase.exec( queryStr );

        while ( query.next() )
        {
            QSqlRecord rec = query.record();

            liste << rec.value( "Id_Artiste" ).toInt();
        }

    }

    return liste;

}

QStringList BDDAfficherMp3::listeTitresAlbumMp3( QString Id_Album, QString Categorie )
{
    QStringList titres;
    QString queryStr = "SELECT DISTINCT Titre, Duree, Num_Piste, M.Id_MP3 FROM Titre T, Album B, MP3 M, Relations R WHERE R.Id_Titre = T.Id_Titre AND R.Id_Album=" + Id_Album + " AND R.Id_Album=B.Id_Album AND R.Id_Relation = M.Id_Relation";
    if ( Categorie != "0" )
    {
        queryStr = queryStr + " AND B.Type='" + Categorie + "'";
    }
    queryStr = queryStr + " ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        QString temp;
        QString Num = rec.value( "Num_Piste" ).toString();

        temp = Num.rightJustified( 2, '0' ) + " - " + rec.value( "Titre" ).toString().replace( "$", "'" ) + "(" + rec.value( "Duree" ).toString() + ")";
        titres << temp << rec.value( "Id_Mp3" ).toString();
    }
    return titres;

}
QList<int> BDDAfficherMp3::listeAlbums( QString Id_Artiste, QString Categorie )
{
    QList<int> albums;
    QString queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND Al.Id_Album = R.Id_Album ";
    if ( Categorie != "0" )
    {
        queryStr = queryStr + " AND Al.Type='" + Categorie + "'";
    }
    queryStr = queryStr + " ORDER BY Al.Annee DESC";

    if ( Categorie == "2" )
    {
        queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, MP3 M, Relations R WHERE Al.Id_Album = R.Id_Album AND Categorie=2 AND R.Id_Relation = M.Id_Relation AND " + AnneesSwitch( Id_Artiste.toInt() ) + " ORDER BY Al.Annee, Al.Album";
    }
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }
    return albums;
}
QString BDDAfficherMp3::AnneesSwitch( int annee )
{
    switch ( annee )
    {
        case 0 :
            return "Annee <1980";
        case 1 :
            return " Annee >=1980 AND Annee <1990";
        case 2 :
            return " Annee >=1990 AND Annee<2000";
        case 3 :
            return " Annee>=2000 AND Annee<2005";
        case 4 :
            return " Annee>=2005 AND Annee<2010";
        case 5 :
            return " Annee>=2010 AND Annee<2015";
        case 6 :
            return " Annee>=2015";
        default :
            return " Annee>=2015";
    }
}

QStringList BDDAfficherMp3::MP3Artiste( QString id_artiste )
{
    QStringList liste;
    QString queryStr = "SELECT DISTINCT M.Chemin FROM Relations R,Mp3 M WHERE M.Id_Relation=R.Id_Relation AND Id_Artiste=" + id_artiste;
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        liste << rec.value( "Chemin" ).toString();
    }
    return liste;
}
QStringList BDDAfficherMp3::RecupererListeTypes( QString Categorie )
{
    QStringList liste;
    QString queryStr;
    if ( Categorie == "MP3" )
    queryStr= "SELECT DISTINCT Type FROM Album B,Relations R WHERE R.Id_Album = B.Id_Album AND R.Mp3=1 ORDER BY Type";

    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        liste << BDDType::RecupererType( rec.value( "Type" ).toInt() )->m_type;
        liste << rec.value( "Type" ).toString();
    }

    return liste;
}
