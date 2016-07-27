#include "bddlecteur.h"
#include <QtSql>

BDDLecteur::BDDLecteur(QObject *parent) : QObject(parent)
{

}

QStringList BDDLecteur::listeTitresAlbum(QString Album)
{
    QStringList titres;
    QString queryStr = "SELECT DISTINCT M.Chemin  AS 'Chemin' FROM Mp3 M, Relations R WHERE  R.Id_Album=" + Album + " AND R.Id_Relation=M.Id_Relation";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        QString Chemin = rec.value ("Chemin").toString().replace( "$","'");
        titres << Chemin;
    }

    return titres;

}

QStringList BDDLecteur::listeTitresArtiste(QString Artiste)
{
    QStringList titres;
    QString queryStr = "SELECT DISTINCT M.Chemin AS 'Chemin' FROM Mp3 M, Relations R WHERE R.Id_Artiste=" + Artiste + " AND R.Id_Relation=M.Id_Relation";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        QString Chemin = rec.value ("Chemin").toString().replace( "$","'");
        titres << Chemin;
    }

    return titres;

}

QStringList BDDLecteur::listeTitresAnnee(QString Annee)
{
    QStringList titres;
    QString queryStr = "SELECT DISTINCT M.Chemin AS 'Chemin' FROM Mp3 M, Relations R, Album B WHERE B.Annee=" + Annee + " AND R.Id_Relation=M.Id_Relation AND R.Id_Album = B.Id_Album";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        QString Chemin = rec.value ("Chemin").toString().replace( "$","'");
        titres << Chemin;
    }

    return titres;

}
