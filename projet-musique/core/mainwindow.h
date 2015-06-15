#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bddgestionmp3.h"
#include <QProgressBar>
#include <QTextBrowser>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ajouterToolbar();

private slots:
    void on_actionActualiser_Mp3_triggered();

    void on_actionViderBDD_triggered();

    void on_actionAjouter_Album_triggered();
    void actionExporter();
    void actionartistesinverses();
    void actionBDD();
    void actionconfigactu();
 //    void afficherinteraction();
    void changerPourcentage();

private:
    Ui::MainWindow *ui;
    QProgressBar* m_progressbar;
    BDDGestionMp3* m_gestionMP3;
    QTextBrowser* m_interaction;
};

#endif // MAINWINDOW_H
