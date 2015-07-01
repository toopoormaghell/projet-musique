#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bddgestionmp3.h"
#include <QProgressBar>
#include <QTextBrowser>
#include "dialogajouterphys.h"
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
 void ActualiserOngletMP3();
    void on_actionViderBDD_triggered();
void ActualiserOngletPhys();

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
    DialogAjouterPhys* m_dialogajouterphys;
};

#endif // MAINWINDOW_H
