#ifndef BDDOBJECT_H
#define BDDOBJECT_H

#include <QObject>

class BDDObject : public QObject
{
    Q_OBJECT
public:
    explicit BDDObject(QObject *parent = nullptr);

    template<typename ... T> void update(T ... args);
    template<typename ... T> void remove(T ... args);
};

template<typename ... T>
BDDObject::BDDObject(QObject *parent):
    QObject(parent)
{
}

template<typename ... T>
void BDDObject::update(T ... args)
{

}

#endif // BDDOBJECT_H
