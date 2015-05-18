#ifndef ONGLETPHYS_H
#define ONGLETPHYS_H

#include <QWidget>

namespace Ui {
class OngletPhys;
}

class OngletPhys : public QWidget
{
    Q_OBJECT

public:
    explicit OngletPhys(QWidget *parent = 0);
    ~OngletPhys();

private:
    Ui::OngletPhys *ui;
};

#endif // ONGLETPHYS_H
