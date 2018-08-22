#ifndef IDOWNER_H
#define IDOWNER_H

#include <QObject>
#include "bdd_global.h"
#include <handable.h>

class BDDSHARED_EXPORT IdOwner : public QObject, public Handable
{
    Q_OBJECT
public:
    explicit IdOwner(int id, QObject *parent = nullptr);
    int id() const;
    void setId(const int id);

private:
    int m_id;
};

#endif // IDOWNER_H
