#ifndef MODELECTURE_H
#define MODELECTURE_H

#include <QWidget>

namespace Ui {
class ModeLecture;
}

class ModeLecture : public QWidget
{
    Q_OBJECT

public:
    explicit ModeLecture(QWidget *parent = 0);
    ~ModeLecture();

private:
    Ui::ModeLecture *ui;
};

#endif // MODELECTURE_H
