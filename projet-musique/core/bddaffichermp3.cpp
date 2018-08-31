#include "bddaffichermp3.h"
#include <QStringList>
#include <QtSql>
#include "bddtype.h"
#include "bddconfig.h"
#include "bddtitre.h"
#include "util.h"

BDDAfficherMp3::BDDAfficherMp3( QObject* parent ) :
    QObject( parent )
{
}
QList<int> BDDAfficherMp3::ListeArtiste( QString type )
{

    QList<int> liste;

    if ( type != "2" )
    {
        QString queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Relations R, MP3 M WHERE A.Id_Artiste!='01' AND R.Id_Album=B.Id_Album AND R.Id_Artiste=A.Id_Artiste AND M.Id_Relation = R.Id_Relation ";

        if ( type != "0" )
        {
            queryStr = queryStr + " AND B.Type='" + type + "'";
        }
        if ( type == "1" )
        {
            queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Relations R, MP3 M WHERE A.Id_Artiste!='01' AND R.Id_Album=B.Id_Album AND R.Id_Artiste=A.Id_Artiste AND M.Id_Relation = R.Id_Relation AND M.Support = '1'";
        }
        if ( type == "2" )
        {
            queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Relations R, MP3 M WHERE A.Id_Artiste!='01' AND R.Id_Album=B.Id_Album AND R.Id_Artiste=A.Id_Artiste AND M.Id_Relation = R.Id_Relation AND M.Support = '2'";
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
    if ( Categorie != "0" && Categorie != "1"  )
    {
        queryStr = queryStr + " AND B.Type='" + Categorie + "'";
    }
    if ( Categorie == "1" )
    {
        queryStr = queryStr + " AND ( B.Type='" + Categorie + "' OR  B.Type='11' )";
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
    QString queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, Relations R, MP3 M WHERE R.Id_Artiste=" + Id_Artiste + " AND Al.Id_Album = R.Id_Album AND M.Id_Relation = R.Id_Relation AND M.Support=1 ";

    if ( Categorie != "0" && Categorie != "1" )
    {
        queryStr = queryStr + " AND Al.Type='" + Categorie + "'";

    }
    if ( Categorie == "1" )
    {
        queryStr = queryStr + " AND ( Al.Type='" + Categorie + "'  OR Al.Type='11' )";
    }
    queryStr = queryStr + " ORDER BY Al.Type, Al.Annee DESC";

    if (Categorie == "0" )
    {
        queryStr = " SELECT DISTINCT B.Id_Album FROM Album B, Relations R WHERE R.Id_Artiste = " + Id_Artiste + " AND B.Id_Album = R.Id_Album ORDER BY B.Type, B.Annee DESC";
    }
    if ( Categorie == "2" )
    {
        queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, MP3 M, Relations R WHERE Al.Id_Album = R.Id_Album AND M.Support = 2 AND R.Id_Relation = M.Id_Relation AND " + AnneesSwitch( Id_Artiste.toInt() ) + " ORDER BY Al.Annee, Al.Album";
    }

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }
    return albums;
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
QStringList BDDAfficherMp3::RecupererListeTypes( )
{
    QStringList liste;
    liste << "Tout" << "O";

    QString  queryStr= "SELECT DISTINCT Type, Support FROM Album B,Relations R, MP3 M WHERE R.Id_Album = B.Id_Album AND R.Id_Relation = M.Id_Relation ORDER BY Type";

    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        if ( rec.value( "Type" ).toInt() != 11 )
        {

            if ( rec.value( "Type" ).toInt() == 2 && rec.value( "Support" ).toInt() == 2 )
            {
                Handle<BDDType> tmp = BDDType::RecupererType( rec.value( "Type" ).toInt() );
                liste << tmp->m_type;
                liste << rec.value( "Type" ).toString();
            }
            if ( rec.value( "Type" ).toInt() != 2 && rec.value( "Support" ).toInt() == 1 )
            {
                Handle<BDDType> tmp = BDDType::RecupererType( rec.value( "Type" ).toInt() );
                liste << tmp->m_type;
                liste << rec.value( "Type" ).toString();
            }
        }
    }
    return liste;
}
QList<int> BDDAfficherMp3::RecupererSimilaires( const int id )
{
    return BDDTitre::Similaires( id );
}

