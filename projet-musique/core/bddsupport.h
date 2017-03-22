#ifndef BDDSUPPORT_H
#define BDDSUPPORT_H

#include <QObject>
#include "idowner.h"

class BDDSupport : public IdOwner
{
    Q_OBJECT
public:
    static BDDSupport* RecupererSupport( const int id );

    QString m_support;

    static QList<int> NbSupport();
private:
    BDDSupport( const int id, QObject* parent = NULL );
};

#endif // BDDSUPPORT_H
