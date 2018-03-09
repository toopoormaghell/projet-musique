#include "bddtype.h"
#include <QtSql>
#include "bddsingleton.h"


BDDType* BDDType::RecupererType( const int id )
{
    return new BDDType( id );
}

BDDType::BDDType(const int id, QObject* parent):
    IdOwner(id, parent)
  , m_type()
{
    QString queryStr = "SELECT Type FROM Type WHERE Id_Type='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next())
    {
        QSqlRecord rec = query.record();
        m_type = rec.value("Type").toString();
    }
}

QList<int> BDDType::NbCategories()
{
    QList<int> cate;
    QString queryStr = "SELECT Id_Type FROM Type";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        cate << rec.value( "Id_Type" ).toInt();

    }
    return cate;
}
QStringList BDDType::RecupererListeTypes( QString Categorie )
{
    QStringList liste;
    QString queryStr;
    if ( Categorie == "MP3" )
        queryStr= "SELECT DISTINCT Type FROM Album B,Relations R, MP3 M WHERE R.Id_Album = B.Id_Album AND R.Id_Relation = M.Id_Relation ORDER BY Type";
    else {
        queryStr= "SELECT DISTINCT Type FROM Album B,Phys P WHERE P.Id_Album = B.Id_Album  ORDER BY Type";

    }

    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        liste << BDDType::RecupererType( rec.value( "Type" ).toInt() )->m_type;
        liste << rec.value( "Type" ).toString();
    }

    return liste;
}
void BDDType::ReconstruireListeCategorieMP3()
{
    //On met dans une autre catégorie les artistes qui ont moins de 10 Mp3 à leur actif
    QString queryStr = "UPDATE Album SET Type = '3' WHERE Id_Album IN ( SELECT Id_Album FROM Relations WHERE  Id_Artiste IN ( SELECT Id_Artiste FROM Relations R, MP3 M, Album B  WHERE M.Id_Relation = R.Id_Relation AND R.Id_Album = B.Id_Album AND B.Type = 1 GROUP BY R.Id_Artiste HAVING COUNT(M.Id_Relation)<10 ) ) " ;
    madatabase.exec( queryStr );

    //Les albums de ces mp3 changent aussi de categories
    queryStr = "UPDATE Album SET Type = '3' WHERE Id_Album IN ( SELECT Id_Album FROM Relations WHERE Id_Artiste IN ( SELECT Id_Artiste FROM Relations R, MP3 M, Album B            WHERE M.Id_Relation = R.Id_Relation AND R.Id_Album = B.Id_Album AND B.Type = 1 GROUP BY R.Id_Artiste HAVING COUNT(M.Id_Relation)<10 ) ) " ;
    madatabase.exec( queryStr );


    //On ajoute dans cette même catégorie les artistes qui ont qu'un seul album à leur actif
    queryStr = " UPDATE Album SET Type = '3' WHERE Id_Album IN ( SELECT Id_Album FROM Relations WHERE Id_Album IN ( SELECT R.Id_Album FROM Relations R, MP3 M, Album B  WHERE  R.Id_Album = B.Id_Album AND B.Type = 1 AND M.Id_Relation = R.Id_Relation GROUP BY R.Id_Artiste HAVING COUNT ( DISTINCT R.Id_Album) < 2 ))" ;
    madatabase.exec( queryStr );

    //Les albums de ces mp3 changent aussi de categories
    queryStr = " UPDATE Album SET Type = '3' WHERE Id_Album IN ( SELECT Id_Album FROM Relations WHERE Id_Album IN ( SELECT R.Id_Album FROM Relations R, MP3 M  WHERE  , Album B  WHERE  R.Id_Album = B.Id_Album AND B.Type = 1 AND M.Id_Relation = R.Id_Relation GROUP BY R.Id_Artiste HAVING COUNT ( DISTINCT R.Id_Album) < 2 ))" ;
    madatabase.exec( queryStr );
}
