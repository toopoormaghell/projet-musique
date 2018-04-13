#ifndef BDDSUPPORT_H
#define BDDSUPPORT_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"

class BDDSHARED_EXPORT BDDSupport : public IdOwner
{
    Q_OBJECT
public:
    static BDDSupport* RecupererSupport( const int id );

    QString m_support;

    static QList<int> NbSupport();

   static BDDSupport* RecupererSupportAlb( int Id, QString Categorie);
private:
    BDDSupport( const int id, QObject* parent = NULL );
};

#endif // BDDSUPPORT_H
