#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bddgestionmp3.h"
#include <QProgressBar>
#include <QLabel>
#include "dialogajouterphys.h"
#include "vidagebdddialog.h"
#include <QPushButton>
#include "ongletmp3.h"
namespace Ui
{
class MainWindow;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale( QWidget* parent = 0 );
    ~FenetrePrincipale();

    void ajouterToolbar();
    void ajouterStatusBar();
signals:
    void stopper();

private slots:
    void on_actionActualiser_Mp3_triggered();
    void on_actionViderBDD_triggered();
    void on_actionAjouter_Album_triggered();
    void actionExporter();
    void actionBDD();
    void actionconfigactu();
    void ViderBDD();
    void ActualiserOngletStats();
    void changerPourcentage();
    void AfficherTexte();
    void ActualiserOngletMP3();
    void ActualiserOngletPhys();
    void stop_clique();
private:
    Ui::MainWindow* ui;
    QProgressBar* m_progressbar;
    BDDGestionMp3* m_gestionMP3;
    QLabel* m_interaction;
    DialogAjouterPhys* m_dialogajouterphys;
    VidageBDDDialog m_vidage;
    QPushButton* stop;
    OngletMP3* m_ongletMP3;

};

#endif // MAINWINDOW_H
