#include "bddtype.h"
#include <QtSql>
#include "bddsingleton.h"


BDDType *BDDType::RecupererType(const int id)
{
    return new BDDType(id);
}

BDDType::BDDType(const int id, QObject *parent):
    QObject(parent),
    m_id(id),
    m_type()
{
    QString queryStr="SELECT Type FROM Type WHERE Id_Type='"+QString::number(id)+"'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        m_type=rec.value("Type").toString();

    }

}

