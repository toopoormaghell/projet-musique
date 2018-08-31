#ifndef HANDABLE_H
#define HANDABLE_H

#include "helpers_global.h"
#include <cstddef>

class HELPERSSHARED_EXPORT Handable
{
public:
    // Adds a reference to an instance
    void ref();

    // Removes a reference from an instance. If reference counter falls
    // to 0, deletes the instance
    void unref();

    // Retuns reference counter value
    size_t getRefcount() const;

protected:
    // Default constructor
    Handable();

    // Copy constructor that explicitly DOES NOT copy the reference counter
    explicit Handable(const Handable&);

    // Assignment operator that explicitly DOES NOT copy the reference counter
    Handable& operator=(const Handable&);

    // Destructor
    virtual ~Handable();

private:
    // Reference count
    size_t m_refcount;
};

#endif // HANDABLE_H
