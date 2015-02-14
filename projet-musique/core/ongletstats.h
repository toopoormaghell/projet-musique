#ifndef ONGLETSTATS_H
#define ONGLETSTATS_H

#include <QWidget>
#include "bddinterface.h"

namespace Ui {
class OngletStats;
}

class OngletStats : public QWidget
{
    Q_OBJECT

public:
    explicit OngletStats(QWidget *parent = 0);
    ~OngletStats();

    void Chiffres();
private:
    Ui::OngletStats *ui;
    BDDInterface m_bddInterface;
};

#endif // ONGLETSTATS_H
