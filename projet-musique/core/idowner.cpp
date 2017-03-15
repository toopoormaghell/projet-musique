#include "idowner.h"

IdOwner::IdOwner(int id, QObject *parent):
    QObject(parent)
  , m_id(id)
{

}
