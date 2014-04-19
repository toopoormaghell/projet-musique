#ifndef APIMUSICPRO_H
#define APIMUSICPRO_H
#include <QObject>
#include "bddinterface.h"

class ApiMusicPro : public QObject
{
    Q_OBJECT
public:
    explicit ApiMusicPro(QObject *parent=0);

    QStringList Requete();

private:
//   BDDInterface m_bddInterface;
};

#endif // APIMUSICPRO_H
