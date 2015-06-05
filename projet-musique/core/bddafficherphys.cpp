#include "bddafficherphys.h"
#include <QtSql>
#include "bddsingleton.h"

BDDAfficherPhys::BDDAfficherPhys(QObject *parent) :
    QObject(parent)
{
}
QList<int> BDDAfficherPhys::ListeArtiste()
{
    QList<int> liste;

    QString queryStr="SELECT DISTINCT A.Id_Artiste FROM Artiste A, Phys P,Relations R WHERE A.Id_Artiste!='01' AND R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste ORDER BY Artiste";

    QSqlQuery query= madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        liste << rec.value("Id_Artiste").toInt();
    }
    return liste;
}
QList<int> BDDAfficherPhys::listeAlbums(QString Id_Artiste)
{
    QList<int> albums;
    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Categorie='1' ORDER BY Al.Annee DESC";

    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toInt();
    }
    return albums;
}
QList<int> BDDAfficherPhys::listeCompils(QString Id_Artiste)
{
    QList<int> albums;
    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Categorie='2' ORDER BY Al.Annee DESC";

    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toInt();
    }
    return albums;
}
