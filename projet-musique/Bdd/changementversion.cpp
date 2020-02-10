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

void ChangementVersion::Version2()
{
    //On change le type 11
    QString  queryStr = " UPDATE Album SET Type =12 WHERE Type =11 ";
    madatabase.exec( queryStr );


    //On change le type 10
    queryStr = " UPDATE Album SET Type =11 WHERE Type =10 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='Reprise' WHERE Id_Type =11 ";
    madatabase.exec( queryStr );

    //On change le type 09
    queryStr = " UPDATE Album SET Type =10 WHERE Type =09 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='Associatif' WHERE Id_Type =10 ";
    madatabase.exec( queryStr );

    //On change le type 08
    queryStr = " UPDATE Album SET Type =09 WHERE Type =08 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='Classique' WHERE Id_Type =09 ";
    madatabase.exec( queryStr );
    //On change le type 07
    queryStr = " UPDATE Album SET Type =08 WHERE Type =07 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='New Age' WHERE Id_Type =08 ";
    madatabase.exec( queryStr );

    //On change le type 06
    queryStr = " UPDATE Album SET Type =07 WHERE Type =06 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='Télé Réalité' WHERE Id_Type =07 ";
    madatabase.exec( queryStr );

    //On change le type 05
    queryStr = " UPDATE Album SET Type =06 WHERE Type =05 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='Musicale' WHERE Id_Type =06 ";
    madatabase.exec( queryStr );

    //On change le type 04
    queryStr = " UPDATE Album SET Type =05 WHERE Type =04 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='BOF' WHERE Id_Type =05 ";
    madatabase.exec( queryStr );

    //On change le type 12
    queryStr = " UPDATE Album SET Type =04 WHERE Type =12 ";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Type SET Type='Live' WHERE Id_Type =04 ";
    madatabase.exec( queryStr );

   //on supprime le type 12
    queryStr = " DELETE FROM Type  WHERE Id_Type =12 ";
    madatabase.exec( queryStr );

   queryStr = " UPDATE Configuration SET 'Valeur' = 3 WHERE Intitule ='Version' ";
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
