#include "handable.h"

void Handable::ref()
{
    m_refcount++;
}

void Handable::unref()
{
    m_refcount--;
    if (m_refcount <= 0)
        delete this;
}

size_t Handable::getRefcount() const
{
    return m_refcount;
}

Handable::Handable():
    m_refcount(0)
{
}

Handable::Handable(const Handable&):
    m_refcount(0)
{
}

Handable&Handable::operator=(const Handable&)
{
    return *this;
}

Handable::~Handable()
{
}
