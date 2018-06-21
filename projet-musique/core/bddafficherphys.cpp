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

    QString queryStr = "SELECT DISTINCT Type FROM Album B,Phys P WHERE P.Id_Album = B.Id_Album  ORDER BY Type";

    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        if ( rec.value( "Type" ).toInt() != 11 )
        {
            liste << BDDType::RecupererType( rec.value( "Type" ).toInt() )->m_type;
            liste << rec.value( "Type" ).toString();
        }
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
    case ( 2 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A WHERE A.Id_Artiste=='01'";break;
    case ( 3 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =3 ORDER BY Artiste";break;
    case ( 4 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =4 ORDER BY Artiste";break;
    case ( 5 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =5 ORDER BY Artiste";break;
    case ( 6 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =6 ORDER BY Artiste";break;
    case ( 7 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =7 ORDER BY Artiste";break;
    case ( 8 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =8 ORDER BY Artiste";break;
    case ( 9 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =9 ORDER BY Artiste";break;
    case ( 10 ) : queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =10 ORDER BY Artiste";break;
    case ( 11 ) : queryStr = "SELECT DISTINCT A.Id_Artiste , A.Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE  R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =11 AND A. Id_Artiste NOT IN ( SELECT DISTINCT A1.Id_Artiste FROM Artiste A1, Album B1, Phys P1,Relations R1 WHERE  R1.Id_Album=P1.Id_Album AND R1.Id_Artiste=A1.Id_Artiste AND P1.Support!='2' AND B1.Id_Album = R1.Id_Album AND B1.Type =1 ORDER BY Artiste) ORDER BY Artiste";break;
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
QList<int> BDDAfficherPhys::listeAlbums( QString Id_Artiste )
{
    QList<int> albums;
    QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='1'  ORDER BY B.Annee DESC";


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
    QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='3' AND B.Type = '11'  ORDER BY B.Annee DESC";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }
    return albums;
}

void BDDAfficherPhys::exporterHTML()
{
    for ( int i = 1; i < 5; i++ )
    {
        QStringList albart = ListeAlbumSauvegarde( i );
        QString chemin = "H:/Dropbox/Projet Musique/Tout.html";
        switch ( i )
        {
        case 1 :
            chemin = "H:/Dropbox/Projet Musique/Albums.html";
            break;
        case 2 :
            chemin = "H:/Dropbox/Projet Musique/Compils.html";
            break;
        case 3 :
            chemin = "H:/Dropbox/Projet Musique/Singles.html";
            break;
        case 4 :
            chemin = "H:/Dropbox/Projet Musique/Chansons.html";
            break;
        }

        //Récupère le fichier et l'ouvre avec lecture lignes par lignes
        QString fileName = chemin;
        QFile fichier( fileName );
        fichier.open( QIODevice::WriteOnly | QIODevice::Text );
        // Création d'un objet QTextStream à partir de notre objet QFile
        QTextStream flux( &fichier );
        // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
        flux << "<Table>";
        int compcouleur = 0;
        if ( i != 4  )
        {
            for ( int cpt = 0; cpt < albart.count(); cpt = cpt + 2 )
            {
                if ( compcouleur % 2 == 0 )
                {
                    flux << "<tr bgcolor='beige'><td>" << QString::number( ( cpt / 2 ) + 1 ).rightJustified( 3, '0' ) << "</td><td>" << albart[cpt + 1] << "</td><td>"  << albart[cpt] << "</td></tr>" << endl;
                }
                else
                {
                    flux << "<tr bgcolor='coral'><td>" << QString::number( cpt / 2 + 1 ).rightJustified( 3, '0' ) << "</td><td>" << albart[cpt + 1] << "</td><td>"  << albart[cpt] << "</td></tr>" << endl;
                }
                compcouleur++;
            }
        }
        else
        {
            for ( int cpt = 0; cpt < albart.count(); cpt = cpt + 3 )
            {
                if ( compcouleur % 2 == 0 )
                {
                    flux << "<tr bgcolor='beige'><td>" << QString::number( ( cpt / 2 ) + 1 ).rightJustified( 3, '0' ) << "</td><td>" << albart[cpt] << "</td><td>"  << albart[cpt + 2] << "</td><td>" << albart[cpt + 1] << "</td></tr>" << endl;
                }
                else
                {
                    flux << "<tr bgcolor='coral'><td>" << QString::number( ( cpt / 2 ) + 1 ).rightJustified( 3, '0' ) << "</td><td>" << albart[cpt] << "</td><td>"  << albart[cpt + 2] << "</td><td>" << albart[cpt + 1] << "</td></tr>" << endl;
                }
                compcouleur++;
            }
        }


        flux << "</Table>";
    }
}

QStringList BDDAfficherPhys::ListeAlbumSauvegarde( int Cate )
{
    QStringList albart;
    QString QueryStr;

    switch ( Cate )
    {
    case 1 :
        QueryStr = "SELECT  DISTINCT B.Album, Ar.Artiste FROM Phys P,Album B, Artiste Ar, Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album AND R.Id_Artiste = Ar.Id_Artiste AND P.Support='1' ORDER BY  B.Type, Ar.Artiste, B.Album";
        break;
    case 2 :
        QueryStr = "SELECT  DISTINCT B.Album, B.Annee FROM Phys P,Album B,Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album  AND P.Support='2' GROUP BY Album ORDER BY B.Annee DESC, B.Album";
        break;
    case 3 :
        QueryStr = "SELECT DISTINCT B.Album, Ar.Artiste FROM Phys P,Album B, Artiste Ar, Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album AND R.Id_Artiste = Ar.Id_Artiste AND P.Support='3' ORDER BY Ar.Artiste, B.Album";
        break;
    case 4 :
        QueryStr = "SELECT DISTINCT Album, Titre, Artiste FROM Phys P,Album B,Relations R, Titre T, Artiste Ar WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album  AND P.Support='2' AND T.Id_Titre=R.Id_Titre AND Ar.Id_Artiste=R.Id_Artiste GROUP BY Titre ORDER BY Artiste, Titre";
        break;
    }

    QSqlQuery query = madatabase.exec( QueryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        switch ( Cate )
        {
        case 1:
            albart <<  rec.value( "Album" ).toString().replace( "$", "'" ) << rec.value( "Artiste" ).toString().replace( "$", "'" );
            break;
        case 2 :
            albart << rec.value( "Album" ).toString().replace( "$", "'" ) << rec.value( "Annee" ).toString() ;
            break;
        case 3:
            albart << rec.value( "Album" ).toString().replace( "$", "'" ) << rec.value( "Artiste" ).toString().replace( "$", "'" );
            break;
        case 4:
            albart << rec.value( "Artiste" ).toString().replace( "$", "'" ) << rec.value( "Album" ).toString().replace( "$", "'" ) << rec.value( "Titre" ).toString().replace( "$", "'" );
            break;
        default:
            albart << rec.value( "Album" ).toString().replace( "$", "'" ) << rec.value( "Artiste" ).toString().replace( "$", "'" );

        }

    }
    return albart;

}

QList<int> BDDAfficherPhys::listeCompils( QString Id_Artiste, int Categorie )
{
    QList<int> albums;

    QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='2' ORDER BY B.Annee DESC";
    if ( Categorie == 2 )
    {

        queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P, Relations R WHERE B.Id_Album = R.Id_Album AND P.Id_Album = R.Id_Album AND P.Support='2' ORDER By B.Annee DESC";
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

QList<int> BDDAfficherPhys::TitresParArtistes(QString Id_Artiste)
{
    QList<int> titres;

    QString queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Phys P, Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND P.Id_Album=R.Id_Album";

    if ( Id_Artiste == "-1" )
    {
        queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Phys P, Relations R WHERE P.Id_Album = R.Id_Album AND P.Support='2' ";
    }

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        titres << rec.value( "NbTitres" ).toInt();
    }

    queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Phys P, Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND P.Id_Album=R.Id_Album AND R.MP3='1'";

    if ( Id_Artiste == "-1" )
    {
        queryStr = "SELECT COUNT (*) AS 'NbTitres' FROM Relations Rel2, Titre T2, MP3 M WHERE Rel2.Id_Titre = T2.Id_Titre AND M.Id_Relation = Rel2.Id_Relation   AND T2.Titre_Formate IN (  SELECT T.Titre_Formate  FROM Phys P, Relations R, Titre T  WHERE P.Id_Album = R.Id_Album  AND P.Support ='2' AND T.Id_Titre = R.Id_Titre AND Rel2.Id_Artiste = R.Id_Artiste) ";
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

        queryStr = "SELECT  R.Id_Album FROM Relations R, Phys P  WHERE R.Id_Album = P.Id_Album AND P.Support='2' GROUP BY R.Id_Album HAVING SUM(R.MP3) < 1";
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
