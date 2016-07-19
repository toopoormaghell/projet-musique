#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogcontroles.h"
#include <QMediaPlaylist>
#include <QStringList>

namespace Ui {
class MainWindowLecteur;
}

class MainWindowLecteur : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLecteur(QWidget *parent = 0);
    ~MainWindowLecteur();
    QStringList m_playlist;



private:
    Ui::MainWindowLecteur *ui;
    DialogControles* m_controles;

};

#endif // MAINWINDOW_H
