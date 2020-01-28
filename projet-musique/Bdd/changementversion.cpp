#include "changementversion.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddpoch.h"
#include <QImage>
#include "util.h"

ChangementVersion::ChangementVersion()
{

}

void ChangementVersion::Version()
{
    //On change le support 4 ( Single ) en support Live
    QString queryStr = "UPDATE Support SET Support ='Live' WHERE Id_Support =4 ";
    madatabase.exec( queryStr );

    //On change le type 3 pour Single
    queryStr = " UPDATE Type SET Type ='Single' WHERE Id_Type =3 ";
    madatabase.exec( queryStr );

    //On change le type 11 pour Live
    queryStr = " UPDATE Type SET Type ='Live' WHERE Id_Type =11 ";
    madatabase.exec( queryStr );

    //On change le type 5 pour Musicale
    queryStr = " UPDATE Type SET Type ='Musicale' WHERE Id_Type =5 ";
    madatabase.exec( queryStr );

    //On change le type 11 pour le 3 pour les singles dans les albums
    queryStr = " UPDATE Album SET Type =3 WHERE Type =11 ";
    madatabase.exec( queryStr );

    //On change le type 12 pour le 11 pour les lives dans les albums
    queryStr = " UPDATE Album SET Type =11 WHERE Type =12  ";
    madatabase.exec( queryStr );

    //On change le support en 4 ( phys) pour les lives dans les albums
    queryStr = " UPDATE Phys SET Support =4 WHERE Id_Album IN ( SELECT Id_Album FROM Album WHERE Type=11) ";
    madatabase.exec( queryStr );

    //On change la version de la BDD
    queryStr = " UPDATE Configuration SET 'Valeur' =1  WHERE Intitule ='Version' ";
    madatabase.exec( queryStr );
}


void ChangementVersion::Version3()
{
    int id_art=0;
    QString   queryStr = " UPDATE Configuration SET 'Valeur' = 3 WHERE Intitule ='Version' ";
    madatabase.exec( queryStr );

    queryStr = "SELECT Id_Artiste FROM Artiste ORDER BY Id_Artiste DESC LIMIT 1";
    QSqlQuery query = madatabase.exec( queryStr );

    if  ( query.first() )
    {
        QSqlRecord rec = query.record();
        id_art = rec.value( "Id_Artiste" ).toInt() + 1;
    }

    QStringList liste;
    liste << "Annees 1980" << "Annees 1990" << "Annees 2000" << "Annees 2010" << "Annees 2015" <<"Rock"<<"Périodes Diverses";

    for ( int i=0; i< liste.count() ; i++ )
    {
        queryStr = "UPDATE Artiste SET Id_Artiste='" + QString::number( id_art) + "' WHERE Id_Artiste='"+ QString::number( i+2 ) + "'";
        madatabase.exec( queryStr );

        queryStr = "UPDATE Album SET Id_Artiste='" + QString::number( id_art) + "' WHERE Id_Artiste='"+ QString::number( i+2 ) + "'";
        madatabase.exec( queryStr );

        queryStr = "UPDATE Relations SET Id_Artiste='" + QString::number( id_art) + "' WHERE Id_Artiste='"+ QString::number( i+2 ) + "'";
        madatabase.exec( queryStr );

        QString NomFormate=liste[i];
        FormaterEntiteBDD( NomFormate );

        queryStr = "INSERT INTO Artiste VALUES ("+ QString::number( i+2 )+ ",'" + liste[i] + "','" + QString::number( 1 ) + "','" + NomFormate + "')";
        madatabase.exec( queryStr );

        id_art++;
    }
}
void ChangementVersion::Version4()
{
    QString   queryStr = " UPDATE Configuration SET 'Valeur' = 4 WHERE Intitule ='Version' ";
    madatabase.exec( queryStr );
    queryStr = "CREATE TABLE ListePlaylist ( 'Id_ListePlaylist' INTEGER PRIMARY KEY, 'Nom_ListePlaylist' VARCHAR(255) )";
    madatabase.exec( queryStr );

    queryStr = "CREATE TABLE RelPlaylist ( 'Id_Rel_Playlist' INTEGER PRIMARY KEY, 'Id_ListePlaylist' INTEGER, 'Id_Relation' INTEGER)";
    madatabase.exec( queryStr );
}
void ChangementVersion::Version5()
{
    QString   queryStr = "INSERT INTO Type VALUES(12,'Live')";
    madatabase.exec( queryStr );
}
