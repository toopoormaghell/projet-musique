#ifndef MAINWINDOWLECTEUR_H
#define MAINWINDOWLECTEUR_H

#include <QWidget>
#include "dialogcontroles.h"
#include <QMediaPlaylist>
#include <QStringList>

namespace Ui {
class MainWindowLecteur;
}

class MainWindowLecteur : public QWidget
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

#endif // MAINWINDOWLECTEUR_H
