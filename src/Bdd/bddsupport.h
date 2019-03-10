#ifndef BDDSUPPORT_H
#define BDDSUPPORT_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"
#include "handle.h"

class BDDSHARED_EXPORT BDDSupport : public IdOwner
{
    Q_OBJECT
public:
    static Handle<BDDSupport> RecupererSupport( const int id );

    QString m_support;

    static QList<int> NbSupport();

   static Handle<BDDSupport> RecupererSupportAlb( int Id, QString Categorie);
private:
    BDDSupport( const int id, QObject* parent = nullptr );
};

#endif // BDDSUPPORT_H
