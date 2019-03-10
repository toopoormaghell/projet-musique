template <typename T>
Handle<T>::Handle():
    m_pointer(nullptr)
{
}

template <typename T>
Handle<T>::Handle(const Handle<T>& other):
    m_pointer(other.m_pointer)
{
    if (m_pointer != nullptr)
        m_pointer->ref();
}

template <typename T>
Handle<T>::Handle(T* rawPointer):
    m_pointer(rawPointer)
{
    if (m_pointer != nullptr)
        m_pointer->ref();
}

template <typename T>
Handle<T>::~Handle()
{
    if (m_pointer != nullptr)
    {
        T* pointerToUnref = m_pointer;
        m_pointer = nullptr;
        pointerToUnref->unref();
    }
}

template <typename T>
Handle<T>& Handle<T>::operator=(const Handle<T>& rhs)
{
    T* tmp = m_pointer;
    m_pointer = rhs.m_pointer;
    if (m_pointer != nullptr)
        m_pointer->ref();
    if (tmp != nullptr)
        tmp->unref();
    return *this;
}

template <typename T>
Handle<T>& Handle<T>::operator=(T* rhs)
{
    T* tmp = m_pointer;
    m_pointer = rhs;
    if (m_pointer != nullptr)
        m_pointer->ref();
    if (tmp != nullptr)
        tmp->unref();
    return *this;
}

template <typename T>
Handle<T>::operator T*() const
{
    return m_pointer;
}

template <typename T>
T& Handle<T>::operator*() const
{
    return *m_pointer;
}

template <typename T>
T* Handle<T>::operator->() const
{
    return m_pointer;
}

template <typename T>
T* Handle<T>::ptr() const
{
    return m_pointer;
}
