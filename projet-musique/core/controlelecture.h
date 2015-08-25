#ifndef CONTROLELECTURE_H
#define CONTROLELECTURE_H

#include <QWidget>

namespace Ui {
class ControleLecture;
}

class ControleLecture : public QWidget
{
    Q_OBJECT

public:
    explicit ControleLecture(QWidget *parent = 0);
    ~ControleLecture();

signals:
    void playPauseClicked();

private:
    Ui::ControleLecture *ui;
};

#endif // CONTROLELECTURE_H
