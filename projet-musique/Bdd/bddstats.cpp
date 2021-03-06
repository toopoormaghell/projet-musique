#include "bddstats.h"
#include "bddsingleton.h"
#include "bddstats.h"
#include <QtSql>
#include "util.h"

bddstats::bddstats( QObject* parent ) : QObject( parent )
{
}

int bddstats::NbMp3Total()
{
    QString queryStr = "SELECT COUNT(*) AS 'Nb' FROM MP3";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}

int bddstats::NbPhysTotal()
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM Phys";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}

int bddstats::NbMp3Categorie( int type )
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM MP3 M, Album B, Relations R  WHERE M.Id_Relation = R.Id_Relation AND  B.Id_Album = R.Id_Album AND B.Type='" + QString::number( type ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}

int bddstats::NbCompilCategorie( int type )
{



    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM MP3 M, Album B, Relations R  WHERE M.Id_Relation = R.Id_Relation AND  B.Id_Album = R.Id_Album AND B.Type='2' AND " + AnneesSwitch( type ) ;
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}
int bddstats::NbPhysCategorie( int support )
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM Phys WHERE  Support='" + QString::number( support ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}
int bddstats::NbPhysType( int type )
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM Phys P, Album B  WHERE P.Support = 1 AND  B.Id_Album = P.Id_Album AND B.Type='" + QString::number( type ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}

int bddstats::NbChansonsPhys()
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM Phys P, Relations R  WHERE R.Id_Album = P.Id_Album";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}
QList<int> bddstats::ListeArtistesCompils()
{
    QList<int> artistes;

    QString queryStr = "SELECT COUNT(*) AS 'Nb', R.Id_Artiste FROM Mp3 M, Relations R,Album B, Artiste A WHERE R.Id_Album = B.Id_Album AND B.Type = 2 AND M.Id_Relation = R.Id_Relation  AND R.Id_Artiste = A.Id_Artiste GROUP BY R.Id_Artiste";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        if ( rec.value( "Nb" ).toInt() > 9 )
        {
            artistes << rec.value( "Id_Artiste" ).toInt();
        }
    }
    return artistes;
}
QList<int> bddstats::ListeMp3ArtisteCompil( int Id_Artiste )
{
    QList<int> mp3;

    QString queryStr = "SELECT R.Id_Titre FROM Mp3 M, Relations R, Album B WHERE R.Id_Album = B.Id_Album AND B.Type = 2  AND M.Id_Relation = R.Id_Relation AND R.Id_Artiste = '" + QString::number( Id_Artiste ) + "' ";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        mp3 << rec.value( "Id_Titre" ).toInt();
    }
    return mp3;
}
int bddstats::NbTotalMp3Phys()
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM Relations WHERE Mp3=1 AND Phys=1";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}
int bddstats::NbTotalAlbumMP3Phys()
{
    QString queryStr = "SELECT COUNT( DISTINCT R.Id_Album )AS 'Nb' FROM Relations R,Phys P WHERE R.Mp3=1 AND R.Phys=1 AND R.Id_Album = P.Id_Album";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value( "Nb" ).toInt();
    }
    return -1;
}

QList<int> bddstats::ListeMP3Doublons()
{
    QList<int> mp3;

    QString queryStr = "SELECT Id_Relation FROM MP3 GROUP BY Id_Relation HAVING COUNT(*) >1";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {

        QSqlRecord rec = query.record();
        queryStr = "SELECT Id_MP3 FROM MP3 WHERE Id_Relation = '" + rec.value( "Id_Relation" ).toString()+"'";

        QSqlQuery query2 = madatabase.exec( queryStr );
        while ( query2.next() )
        {
            QSqlRecord rec2 = query2.record();
            mp3 << rec2.value("Id_MP3").toInt();
        }
    }
    return mp3;
}

