#include "idowner.h"

IdOwner::IdOwner(int id, QObject *parent):
    QObject(parent)
  , m_id(id)
{

}

int IdOwner::id() const
{
    return m_id;
}

void IdOwner::setId(const int id)
{
    m_id = id;
}
