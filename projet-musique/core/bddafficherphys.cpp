#include "bddafficherphys.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddtype.h"

BDDAfficherPhys::BDDAfficherPhys( QObject* parent ) :
    QObject( parent )
{
}

QStringList BDDAfficherPhys::RecupererListeTypes()
{
    QStringList liste;
    liste << "Tout" << "O";

    QString queryStr = "SELECT DISTINCT B.Type AS 'Type' FROM Album B,Phys P, Type T WHERE P.Id_Album = B.Id_Album AND T.Id_Type = B.Type ORDER BY T.Id_Type";

    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {

        QSqlRecord rec = query.record();

        Handle<BDDType> tmp = BDDType::RecupererType( rec.value( "Type" ).toInt() );
        liste << tmp->m_type;
        liste << rec.value( "Type" ).toString();

    }

    return liste;

}
QList<int> BDDAfficherPhys::ListeArtiste(int categorie)
{
    QList<int> liste;
    QString queryStr ;

    switch ( categorie )
    {
    case ( 1 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =1 ORDER BY Artiste"; break;
    case ( 2 ) : queryStr = "SELECT DISTINCT (B.Id_Artiste) FROM  Album B, Phys P WHERE P.Support='2' AND B.Id_Album = P.Id_Album AND B.Type ='2' ORDER BY B.Id_Artiste";break;
    case ( 3 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =3 ORDER BY Artiste";break;
    case ( 4 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =4 ORDER BY Artiste";break;
    case ( 5 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =5 ORDER BY Artiste";break;
    case ( 6 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =6 ORDER BY Artiste";break;
    case ( 7 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =7 ORDER BY Artiste";break;
    case ( 8 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =8 ORDER BY Artiste";break;
    case ( 9 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =9 ORDER BY Artiste";break;
    case ( 10 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =10 ORDER BY Artiste";break;
    case ( 12 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support=='4' AND B.Id_Album = R.Id_Album AND B.Type =12 ORDER BY Artiste";break;
    default: queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album  ORDER BY Artiste";
    }
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Artiste" ).toInt();
    }
    return liste;
}
QList<int> BDDAfficherPhys::listeAlbums( QString Id_Artiste, int Categorie )
{
    QList<int> albums;


      QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='1' AND B.Type = "+ QString::number( Categorie ) +" ORDER BY B.Annee DESC";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }
    return albums;
}
QList<int> BDDAfficherPhys::listeLives( QString Id_Artiste )
{
    QList<int> albums;


      QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='4' ORDER BY B.Annee DESC";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }
    return albums;
}
QList<int> BDDAfficherPhys::listeSingles( QString Id_Artiste )
{
    QList<int> albums;
    QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='3'  ORDER BY B.Annee DESC";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }
    return albums;
}


QList<int> BDDAfficherPhys::listeCompils( QString Id_Artiste, int Categorie )
{
    QList<int> albums;

    QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='2' ORDER BY B.Annee DESC";
    if ( Categorie == 2 )
    {
        queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P, Relations R WHERE B.Id_Album = R.Id_Album AND P.Id_Album = R.Id_Album AND P.Support='2' AND B.Id_Artiste='" + Id_Artiste + "' ORDER By B.Annee DESC";
    }
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }
    return albums;
}
QStringList BDDAfficherPhys::ListeTitresPossibles()
{
    QStringList Titres;

    QString QueryStr = "SELECT DISTINCT Titre FROM Titre ORDER BY Titre";
    QSqlQuery query = madatabase.exec( QueryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        Titres << rec.value( "Titre" ).toString().replace( "$", "'" ) ;
    }
    return Titres;

}
QStringList BDDAfficherPhys::ListeArtistesPossibles()
{
    QStringList Artistes;

    QString QueryStr = "SELECT DISTINCT Artiste FROM Artiste ORDER BY Artiste";
    QSqlQuery query = madatabase.exec( QueryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        Artistes << rec.value( "Artiste" ).toString().replace( "$", "'" ) ;
    }
    return Artistes;

}

QList<int> BDDAfficherPhys::TitresParArtistes( QString Id_Artiste )
{
    QList<int> titres;

    QString queryStr;

    if ( Id_Artiste == "-1" && Id_Artiste == 1 && Id_Artiste.isEmpty() )
    {
        queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Phys P, Relations R WHERE P.Id_Album = R.Id_Album AND P.Support='2' ";
    } else
    {
        queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Phys P, Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND P.Id_Album=R.Id_Album";
    }

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        titres << rec.value( "NbTitres" ).toInt();
    }

    queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Phys P, Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND P.Id_Album=R.Id_Album AND R.MP3='1'";

    if ( Id_Artiste == "-1" && Id_Artiste == 1  && Id_Artiste.isEmpty() )
    {
        queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Relations Rel2, MP3 M WHERE M.Id_Relation = Rel2.Id_Relation  AND Rel2.Id_Titre IN ( SELECT R.Id_Titre FROM Phys P, Relations R WHERE P.Id_Album = R.Id_Album AND P.Support ='2' AND Rel2.Id_Artiste = R.Id_Artiste)  ";
    }

    query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        titres << rec.value( "NbTitres" ).toInt();
    }


    return titres;
}

QList<int> BDDAfficherPhys::AlbSansMP3( QString Id_Artiste, int Categorie )
{
    QList<int> albums;
    albums << 0;


    QString queryStr = "SELECT R.Id_Album FROM Relations R, Phys P, Album B WHERE R.Id_Album = B.Id_Album AND R.Id_Album = P.Id_Album AND P.Support='1' AND R.Id_Artiste = " + Id_Artiste +" AND B.Type = "+ QString::number(Categorie) +" GROUP BY R.Id_Album HAVING SUM(R.MP3) < 1 ";
    if ( Categorie == 2 )
    {
        queryStr = "SELECT  R.Id_Album FROM Relations R, Phys P, Album B  WHERE R.Id_Album = P.Id_Album AND P.Support='2' AND B.Id_Artiste=" + Id_Artiste +" AND B.Id_Album = P.Id_Album GROUP BY R.Id_Album HAVING SUM(R.MP3) < 1";
    }

    if ( Id_Artiste == "-1" && Categorie == -1 )
    {
        queryStr = "SELECT R.Id_Album FROM Relations R, Phys P, Album B, Artiste A WHERE R.Id_Album = B.Id_Album AND R.Id_Album = P.Id_Album AND R.Id_Artiste = A.Id_Artiste AND P.Support='1' GROUP BY R.Id_Album HAVING SUM(R.MP3) < 1 ORDER BY B.Type, A.Artiste, B.Album";
    }
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }

    return albums;
}
