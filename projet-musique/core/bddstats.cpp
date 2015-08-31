#include "bddstats.h"
#include "bddsingleton.h"
#include <QtSql>

bddstats::bddstats(QObject *parent) : QObject(parent)
{
}

int bddstats::NbMp3Total()
{
    QString queryStr="SELECT COUNT(*) AS 'Nb' FROM MP3";
    QSqlQuery query= madatabase.exec(queryStr);

    if(query.first()) {
        QSqlRecord rec=query.record();

        return rec.value("Nb").toInt();
    }

}

int bddstats::NbPhysTotal()
{
    QString queryStr="SELECT COUNT(*)AS 'Nb' FROM Phys";
    QSqlQuery query= madatabase.exec(queryStr);

    if(query.first()) {
        QSqlRecord rec=query.record();

        return rec.value("Nb").toInt();
    }
}
