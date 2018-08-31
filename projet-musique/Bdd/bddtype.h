#ifndef BDDTYPE_H
#define BDDTYPE_H

#include <QObject>
#include "idowner.h"
#include "bdd_global.h"
#include "handle.h"

class BDDSHARED_EXPORT BDDType : public IdOwner
{
    Q_OBJECT
public:
    static Handle<BDDType> RecupererType( const int id );

    QString m_type;

    static QList<int> NbCategories();
    static QStringList RecupererListeTypes(QString Categorie);
    static void ReconstruireListeCategorieMP3();

private:
    explicit BDDType(const int id, QObject* parent = nullptr);

};

#endif // BDDTYPE_H
