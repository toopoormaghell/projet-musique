#include "bddgestionmodifnomartiste.h"
#include <QtSql>
#include "bddsingleton.h"

bddgestionmodifnomartiste::bddgestionmodifnomartiste()
{

}

QList<int> bddgestionmodifnomartiste::ListeArtiste()
{
    QList<int> liste;

    QString queryStr = "SELECT DISTINCT R.Id_Artiste FROM Relations R, Album B, Artiste A WHERE A.Id_Artiste = R.Id_Artiste AND B.Id_Album = R.Id_Album AND B.Type !=2 ORDER BY A.Artiste";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Artiste").toInt();
    }


    return liste;
}
