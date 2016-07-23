#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogcontroles.h"
#include <QMediaPlaylist>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStringList m_playlist;



private:
    Ui::MainWindow *ui;
    DialogControles* m_controles;

};

#endif // MAINWINDOW_H
