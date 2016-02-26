#include "bddstats.h"
#include "bddsingleton.h"
#include <QtSql>

bddstats::bddstats(QObject *parent) : QObject(parent)
{
}

int bddstats::NbMp3Total()
{
    QString queryStr = "SELECT COUNT(*) AS 'Nb' FROM MP3";
    QSqlQuery query = madatabase.exec(queryStr);

    if (query.first())
    {
        QSqlRecord rec = query.record();

        return rec.value("Nb").toInt();
    }
    return -1;
}

int bddstats::NbPhysTotal()
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM Phys";
    QSqlQuery query = madatabase.exec(queryStr);

    if (query.first())
    {
        QSqlRecord rec = query.record();

        return rec.value("Nb").toInt();
    }
    return -1;
}

int bddstats::NbMp3Categorie(int type)
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM MP3  WHERE Categorie='" + QString::number(type) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    if (query.first())
    {
        QSqlRecord rec = query.record();

        return rec.value("Nb").toInt();
    }
    return -1;
}

int bddstats::NbPhysCategorie(int type)
{
    QString queryStr = "SELECT COUNT(*)AS 'Nb' FROM Phys  WHERE Categorie='" + QString::number(type) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    if (query.first())
    {
        QSqlRecord rec = query.record();

        return rec.value("Nb").toInt();
    }
    return -1;
}
int bddstats::NbChansonsPhys()
{
    QString queryStr = "SELECT COUNT(R.Id_Relation)AS 'Nb' FROM Phys P, Relations R  WHERE R.Id_Album = P.Id_Album";
    QSqlQuery query = madatabase.exec(queryStr);

    if (query.first())
    {
        QSqlRecord rec = query.record();

        return rec.value("Nb").toInt();
    }
    return -1;
}
QList<int> bddstats::ListeArtistesCompils()
{
    QList<int> artistes;

    QString queryStr = "SELECT COUNT(*) AS 'Nb', R.Id_Artiste FROM Mp3 M, Relations R, Artiste A WHERE M.Categorie = '2' AND M.Id_Relation = R.Id_Relation AND R.Id_Artiste = A.Id_Artiste GROUP BY R.Id_Artiste";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        if ( rec.value("Nb").toInt() > 4)
        {
            artistes << rec.value("Id_Artiste").toInt();
        }
    }
    return artistes;
}
QList<int> bddstats::ListeMp3ArtisteCompil(int Id_Artiste)
{
    QList<int> mp3;

    QString queryStr = "SELECT R.Id_Titre FROM Mp3 M, Relations R WHERE M.Categorie = '2' AND M.Id_Relation = R.Id_Relation AND R.Id_Artiste = '" + QString::number(Id_Artiste) + "' ";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        mp3 << rec.value("Id_Titre").toInt();
    }
    return mp3;
}
