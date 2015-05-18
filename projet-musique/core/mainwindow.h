#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bddgestionmp3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionActualiser_Mp3_triggered();

    void on_actionViderBDD_triggered();

    void on_actionAjouter_Album_triggered();

private:
    Ui::MainWindow *ui;

    BDDGestionMp3* m_gestionMP3;
};

#endif // MAINWINDOW_H
