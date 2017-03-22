#ifndef IDOWNER_H
#define IDOWNER_H

#include <QObject>

class IdOwner : public QObject
{
    Q_OBJECT
public:
    explicit IdOwner(int id, QObject *parent = 0);
    int id() const;
    void setId(const int id);

private:
    int m_id;
};

#endif // IDOWNER_H
