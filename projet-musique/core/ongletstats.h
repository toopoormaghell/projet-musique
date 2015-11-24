#ifndef ONGLETSTATS_H
#define ONGLETSTATS_H
#include "bddstats.h"
#include <QWidget>

namespace Ui {
class OngletStats;
}

class OngletStats : public QWidget
{
    Q_OBJECT

public:
    explicit OngletStats(QWidget *parent = 0);
    ~OngletStats();
  void AfficherInfos();
private:
    Ui::OngletStats *ui;
    bddstats m_bddInterface;

    void AfficherInfosCategoriesMP3();
    void AfficherInfosCategoriesPhys();
};

#endif // ONGLETSTATS_H
