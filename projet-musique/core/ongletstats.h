#ifndef ONGLETSTATS_H
#define ONGLETSTATS_H

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

private:
    Ui::OngletStats *ui;
};

#endif // ONGLETSTATS_H
