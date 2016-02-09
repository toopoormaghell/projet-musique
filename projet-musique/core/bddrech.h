#ifndef BDDRECH_H
#define BDDRECH_H

#include <QObject>
#include "bddsingleton.h"
class BDDRech : public QObject
{
public:
    BDDRech(QObject *parent);

    QList<int> RechTitres(QString rech);
    QList<int> RechAlb(QString rech);
    QList<int> RechArt(QString rech);
};

#endif // BDDRECH_H
