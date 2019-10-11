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

    QString queryStr = "CREATE TABLE BoiteInfos ('Id_Boite' INTEGER PRIMARY KEY, 'Nom_Boite' VARCHAR(255) )";

    madatabase.exec( queryStr );

    queryStr = "CREATE TABLE BoiteAlb ( 'Id_Boite' INTEGER, 'Id_Album' INTEGER)";
    madatabase.exec( queryStr );

    queryStr = " UPDATE Configuration SET 'Valeur' = 2 WHERE Intitule ='Version' ";

    madatabase.exec( queryStr );


    //On en profite pour scaler toutes les images
    queryStr = "Select DISTINCT Id_Pochette FROM Pochette";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        Handle<BDDPoch> poch = BDDPoch::recupererBDD( rec.value( "Id_Pochette" ).toInt() );

        poch->sauverImage();

    }
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
