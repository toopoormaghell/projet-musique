#include "bddafficherphys.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddalbum.h"


BDDAfficherPhys::BDDAfficherPhys( QObject* parent ) :
    QObject( parent )
{
}
QList<int> BDDAfficherPhys::ListeArtiste()
{
    QList<int> liste;

    QString queryStr = "SELECT DISTINCT A.Id_Artiste FROM Artiste A, Album B, Phys P,Relations R WHERE A.Id_Artiste!='01' AND R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Support!='2' AND B.Id_Album = R.Id_Album AND B.Type =1 ORDER BY Artiste";

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
    QString queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='1' ORDER BY Al.Annee DESC";

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
    QString queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='3' ORDER BY Al.Annee DESC";

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
        QString chemin = "F:/Tout.html";
        switch ( i )
        {
        case 1 :
            chemin = "F:/Albums.html";
            break;
        case 2 :
            chemin = "F:/Compils.html";
            break;
        case 3 :
            chemin = "F:/Singles.html";
            break;
        case 4 :
            chemin = "F:/Chansons.html";
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
        if ( i != 4 )
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
        QueryStr = "SELECT DISTINCT Al.Album, Ar.Artiste FROM Phys P,Album Al, Artiste Ar, Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=Al.Id_Album AND R.Id_Artiste = Ar.Id_Artiste AND P.Support='1' ORDER BY Ar.Artiste, Al.Album";
        break;
    case 2 :
        QueryStr = "SELECT DISTINCT Al.Album FROM Phys P,Album Al,Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=Al.Id_Album  AND P.Support='2' GROUP BY Album ORDER BY Al.Album";
        break;
    case 3 :
        QueryStr = "SELECT DISTINCT Al.Album, Ar.Artiste FROM Phys P,Album Al, Artiste Ar, Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=Al.Id_Album AND R.Id_Artiste = Ar.Id_Artiste AND P.Support='3' ORDER BY Ar.Artiste, Al.Album";
        break;
    case 4 :
        QueryStr = "SELECT DISTINCT Album, Titre, Artiste FROM Phys P,Album Al,Relations R, Titre T, Artiste Ar WHERE P.Id_Album=R.Id_Album AND R.Id_Album=Al.Id_Album  AND P.Support='2' AND T.Id_Titre=R.Id_Titre AND Ar.Id_Artiste=R.Id_Artiste GROUP BY Titre ORDER BY Artiste, Titre";
        break;
    }

    QSqlQuery query = madatabase.exec( QueryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        if ( Cate == 2 )
        {
            albart << rec.value( "Album" ).toString().replace( "$", "'" ) << "Compil" ;
        }
        else if ( Cate == 4 )
        {
            albart << rec.value( "Artiste" ).toString().replace( "$", "'" ) << rec.value( "Album" ).toString().replace( "$", "'" ) << rec.value( "Titre" ).toString().replace( "$", "'" );
        }
        else
        {
            albart << rec.value( "Album" ).toString().replace( "$", "'" ) << rec.value( "Artiste" ).toString().replace( "$", "'" );
        }
    }
    return albart;

}

QList<int> BDDAfficherPhys::listeCompils( QString Id_Artiste )
{
    QList<int> albums;

    QString queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste=" + Id_Artiste + " AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Support='2' ORDER BY Al.Annee DESC";
    if ( Id_Artiste == "-1" )
    {

        queryStr = "SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P, Relations R WHERE Al.Id_Album = R.Id_Album AND P.Id_Album = R.Id_Album AND P.Support='2' ORDER By Al.Annee DESC";
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

    if ( Id_Artiste == "-1" )
    {
        queryStr = "SELECT T2.Titre AS 'Titre', A.Album AS 'Album' FROM Relations Rel2, Titre T2, MP3 M, Album A WHERE Rel2.Id_Titre = T2.Id_Titre AND M.Id_Relation = Rel2.Id_Relation AND A.Id_Album = Rel2.Id_Album  AND T2.Titre_Formate IN (  SELECT T.Titre_Formate  FROM Phys P, Relations R, Titre T  WHERE P.Id_Album = R.Id_Album  AND P.Support ='2' AND T.Id_Titre = R.Id_Titre AND Rel2.Id_Artiste = R.Id_Artiste) ";


        query = madatabase.exec( queryStr );

        while ( query.next() )
        {
            QSqlRecord rec = query.record();

            qDebug() << rec.value("Album").toString() << rec.value( "Titre").toString();
        }
    }

    return titres;
}

QList<int> BDDAfficherPhys::AlbSansMP3( QString Id_Artiste )
{
    QList<int> albums;
    albums <<0;

    QString queryStr = "SELECT R.Id_Album FROM Relations R, Phys P WHERE R.Id_Album = P.Id_Album AND P.Support='1' AND R.Id_Artiste = " + Id_Artiste +" GROUP BY R.Id_Album HAVING SUM(R.MP3) < 1 ";
     if ( Id_Artiste == "-1" )
    {

        queryStr = "SELECT  R.Id_Album FROM Relations R, Phys P  WHERE R.Id_Album = P.Id_Album AND P.Support='2' GROUP BY R.Id_Album HAVING SUM(R.MP3) < 1";
    }
   QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }

    return albums;
}
