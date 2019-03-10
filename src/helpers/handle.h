#ifndef HANDLE_H
#define HANDLE_H

#include "helpers_global.h"

template <class T>
class HELPERSSHARED_EXPORT Handle
{
public:
    // Default constructor
    Handle();

    // Copy constructor
    Handle(const Handle<T>& other);

    // Constructor from raw pointer
    Handle(T* rawPointer);

    // Destructor
    ~Handle();

    // Default assignment operator
    Handle<T>& operator=(const Handle<T>& rhs);

    // Assignment operator from a raw pointer
    Handle<T>& operator=(T* rhs);

    // Cast operator to raw pointer
    operator T*() const;

    // Dereference operator
    T& operator*() const;

    // Dereference operator
    T* operator->() const;

    // Returns managed pointer
    T* ptr() const;

private:
    // Managed pointer
    T* m_pointer;
};

#include "handle_impl.h"

#endif // HANDLE_H
