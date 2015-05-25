#include "bddaffichermp3.h"
#include <QStringList>
#include <QtSql>
#include "bddtype.h"
BDDAfficherMp3::BDDAfficherMp3(QObject *parent) :
    QObject(parent)
{
}
QList<int> BDDAfficherMp3::ListeArtiste()
{
    QList<int> liste;

    QString queryStr="SELECT DISTINCT A.Id_Artiste FROM Artiste A, MP3 M,Relations R WHERE A.Id_Artiste!='01' AND R.Id_Relation=M.Id_Relation AND R.Id_Artiste=A.Id_Artiste ORDER BY Artiste";

    QSqlQuery query= madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        liste << rec.value("Id_Artiste").toInt();
    }
    return liste;
}

QStringList BDDAfficherMp3::listeTitresAlbumMp3(QString Album)
{
    QStringList titres;
    QString queryStr="SELECT DISTINCT Titre, Duree, Num_Piste, M.Id_Relation FROM Titre T, Mp3 M, Relations R WHERE R.Id_Titre = T.Id_Titre AND R.Id_Album="+Album+" AND R.Id_Relation=M.Id_Relation AND M.Categorie='1' ORDER BY Num_Piste";
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString temp;
        QString Num= rec.value("Num_Piste").toString();

        temp = Num.rightJustified(2,'0') + " - " + rec.value("Titre").toString().replace("$","'") + "(" + rec.value("Duree").toString() + ")";
        titres << temp << rec.value("Id_Relation").toString();
    }
    return titres;

}
QList<int> BDDAfficherMp3::listeAlbums(QString Id_Artiste)
{
    QList<int> albums;
    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, MP3 M,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND R.Id_Relation = M.Id_Relation AND M.Categorie='1' ORDER BY Al.Annee DESC";

    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toInt();
    }
    return albums;
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
    }
    return liste;
}
