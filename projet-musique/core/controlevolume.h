#ifndef CONTROLEVOLUME_H
#define CONTROLEVOLUME_H

#include <QWidget>

namespace Ui {
class ControleVolume;
}

class ControleVolume : public QWidget
{
    Q_OBJECT

public:
    explicit ControleVolume(QWidget *parent = 0);
    ~ControleVolume();

private:
    Ui::ControleVolume *ui;
};

#endif // CONTROLEVOLUME_H
