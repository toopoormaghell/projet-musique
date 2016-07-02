#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

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
    void on_Lecture_clicked();

    void on_Arret_clicked();

    void on_Volume_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    void AfficherIcones();
    QMediaPlayer* player;
    QString titre;
};

#endif // MAINWINDOW_H
