#ifndef BDDTYPE_H
#define BDDTYPE_H

#include <QObject>

class BDDType : public QObject
{
    Q_OBJECT
public:
    static BDDType* RecupererType(const int id);

    int m_id;
    QString m_type;

   static QList<int> NbCategories();
private:
    BDDType(const int id,QObject* parent= NULL);

};

#endif // BDDTYPE_H
