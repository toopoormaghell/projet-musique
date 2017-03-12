#ifndef BDDSUPPORT_H
#define BDDSUPPORT_H

#include <QObject>

class BDDSupport : public QObject
{
    Q_OBJECT
public:
    static BDDSupport* RecupererSupport( const int id );

    int m_id;
    QString m_support;

    static QList<int> NbSupport();
private:
    BDDSupport( const int id, QObject* parent = NULL );
};

#endif // BDDSUPPORT_H
