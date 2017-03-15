#ifndef BDDTYPE_H
#define BDDTYPE_H

#include <QObject>
#include "idowner.h"

class BDDType : public IdOwner
{
    Q_OBJECT
public:
    static BDDType* RecupererType( const int id );

    QString m_type;

    static QList<int> NbCategories();
private:
    explicit BDDType(const int id, QObject* parent = NULL);

};

#endif // BDDTYPE_H
