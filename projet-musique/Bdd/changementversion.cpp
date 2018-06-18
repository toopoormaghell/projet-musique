#include "changementversion.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddpoch.h"
#include <QImage>


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

        BDDPoch* poch = BDDPoch::recupererBDD( rec.value( "Id_Pochette" ).toInt() );

        poch->sauverImage();

        delete poch;

    }
}
