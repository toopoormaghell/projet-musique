#include "bddafficherliste.h"
#include <QtSql>

BddAfficherListe::BddAfficherListe(QObject* parent):
    QObject( parent )
{

}

int BddAfficherListe::EnregistrerBoite(QString nom_boite)
{
    QString queryStr = " INSERT INTO BoiteInfos VALUES(null, '" + nom_boite + "' ) " ;
    qDebug() << queryStr;
    QSqlQuery query = madatabase.exec( queryStr );

    return query.lastInsertId().toInt();
}

void BddAfficherListe::EnregistrerSelection( QList<int> liste, int boite )
{
    for ( int i = 0; i < liste.count() ; i++ )
    {
        QString queryStr = " INSERT INTO BoiteAlb VALUES(" + QString::number( boite )+ ", " + QString::number( liste[i] ) + " ) " ;
        qDebug() << queryStr;
        madatabase.exec( queryStr );
    }
}
QStringList BddAfficherListe::AfficherBoites()
{
    QStringList liste;
    QString queryStr = " SELECT * FROM BoiteInfos ";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Boite").toString();
        liste << rec.value( "Nom_Boite").toString();
    }

    return liste;
}
QList<int> BddAfficherListe::listeAlbums()
{
    QList<int> albums;


    QString queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R, Artiste A WHERE B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND R.Id_Artiste = A.Id_Artiste AND R.Id_Album NOT IN ( SELECT Id_Album FROM BoiteAlb )  ORDER BY P.Support, A.Artiste, B.Annee DESC";


    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }




    return albums;
}
QList<int> BddAfficherListe::listeAlbums ( int Id_Boite )
{

    QList<int> albums;

    QString queryStr;
    if ( Id_Boite == 0 )
    {
   queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R, Artiste A, BoiteAlb BA WHERE B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND R.Id_Artiste = A.Id_Artiste  AND R.Id_Album = BA.Id_Album  ORDER BY P.Support, A.Artiste, B.Annee DESC";
    } else
    {
        queryStr = "SELECT DISTINCT B.Id_Album FROM Album B, Phys P,Relations R, Artiste A, BoiteAlb BA WHERE B.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND R.Id_Artiste = A.Id_Artiste  AND R.Id_Album = BA.Id_Album AND  BA.Id_Boite =" + QString::number( Id_Boite ) + " ORDER BY P.Support, A.Artiste, B.Annee DESC";
    }

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        albums << rec.value( "Id_Album" ).toInt();
    }




    return albums;
}
