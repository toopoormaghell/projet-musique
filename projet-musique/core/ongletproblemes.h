#ifndef ONGLETPROBLEMES_H
#define ONGLETPROBLEMES_H

#include <QWidget>

namespace Ui {
    class OngletProblemes;
}

class OngletProblemes : public QWidget
{
    Q_OBJECT

public:
    explicit OngletProblemes(QWidget *parent = nullptr);
    ~OngletProblemes();

private:
    Ui::OngletProblemes *ui;
};

#endif // ONGLETPROBLEMES_H
