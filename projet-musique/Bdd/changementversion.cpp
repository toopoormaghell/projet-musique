#include "changementversion.h"
#include "bddsingleton.h"
#include <QtSql>

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
}
