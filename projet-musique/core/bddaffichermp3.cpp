#include "bddaffichermp3.h"
#include <QStringList>
#include <QtSql>
#include "bddtype.h"
#include "bddconfig.h"

BDDAfficherMp3::BDDAfficherMp3(QObject *parent) :
    QObject(parent)
{
}
QList<int> BDDAfficherMp3::ListeArtiste(QString type)
{

    QList<int> liste;

    if (type!="2")
    {
        QString queryStr="SELECT DISTINCT A.Id_Artiste FROM Artiste A, MP3 M,Relations R WHERE A.Id_Artiste!='01' AND R.Id_Relation=M.Id_Relation AND R.Id_Artiste=A.Id_Artiste";

        if(type!="0")
        {
            queryStr = queryStr + " AND M.Categorie='"+ type +"'";
        }
        queryStr =queryStr+ " ORDER BY Artiste";

        QSqlQuery query= madatabase.exec(queryStr);

        while (query.next() ) {
            QSqlRecord rec=query.record();

            liste << rec.value("Id_Artiste").toInt();
        }

    }

    return liste;

}

QStringList BDDAfficherMp3::listeTitresAlbumMp3(QString Album,QString Categorie)
{
    QStringList titres;
    QString queryStr="SELECT DISTINCT Titre, Duree, Num_Piste, M.Id_MP3 FROM Titre T, Mp3 M, Relations R WHERE R.Id_Titre = T.Id_Titre AND R.Id_Album="+Album+" AND R.Id_Relation=M.Id_Relation";
    if (Categorie!="0")
    {
        queryStr= queryStr+ " AND M.Categorie='"+Categorie+"'";
    }
    queryStr= queryStr+" ORDER BY Num_Piste";
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString temp;
        QString Num= rec.value("Num_Piste").toString();

        temp = Num.rightJustified(2,'0') + " - " + rec.value("Titre").toString().replace("$","'") + "(" + rec.value("Duree").toString() + ")";
        titres << temp << rec.value("Id_Mp3").toString();
    }
    return titres;

}
QList<int> BDDAfficherMp3::listeAlbums(QString Id_Artiste,QString Categorie)
{
    QList<int> albums;
    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, MP3 M,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND R.Id_Relation = M.Id_Relation";
    if (Categorie!="0")
    {
        queryStr= queryStr+ " AND M.Categorie='"+Categorie+"'";
    }
    queryStr= queryStr+" ORDER BY Al.Annee DESC";

    if (Categorie=="2")
    {
        queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, MP3 M, Relations R WHERE Al.Id_Album = R.Id_Album AND Categorie=2 AND R.Id_Relation = M.Id_Relation AND "+AnneesSwitch(Id_Artiste)+" ORDER BY Al.Annee, Al.Album";
    }
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toInt();
    }
    return albums;
}
QString BDDAfficherMp3::AnneesSwitch(QString annee)
{
    if (annee=="Avant 1980")
        return "Annee <1980";
    if ( annee=="1980-1989")
        return  " Annee >=1980 AND Annee <1990";
    if ( annee=="1990-1999")
        return " Annee >=1990 AND Annee<2000";
    if (annee=="2000-2004")
        return " Annee>=2000 AND Annee<2005";
    if (annee=="2005-2009")
        return " Annee>=2005 AND Annee<2010";
    if (annee=="2010-2014")
        return " Annee>=2010 AND Annee<2014";
    if (annee=="2015-2019")
        return " Annee>=2015";
return "faux";
}

QStringList BDDAfficherMp3::MP3Artiste(QString id_artiste)
{
    QStringList liste;
    QString queryStr="SELECT DISTINCT M.Chemin FROM Relations R,Mp3 M WHERE M.Id_Relation=R.Id_Relation AND Id_Artiste="+id_artiste;
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        liste << rec.value("Chemin").toString();
    }
    return liste;
}
QStringList BDDAfficherMp3::RecupererListeTypes(const QString categorie)
{
    QStringList liste;
    QString queryStr="SELECT DISTINCT Categorie FROM "+categorie;

    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        liste << BDDType::RecupererType( rec.value("Categorie").toInt() )->m_type;
        liste << rec.value("Categorie").toString();
    }

    return liste;
}

