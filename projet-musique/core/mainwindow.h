#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bddgestionmp3.h"
#include <QProgressBar>
#include <QLabel>
#include "DialogAjouterPhys.h"
#include "DialogVidageBDD.h"
#include <QPushButton>
#include "ongletmp3.h"
#include "mainwindowlecteur.h"
#ifdef Q_OS_WIN
#include <QWinTaskbarButton>
#endif

namespace Ui
{
class MainWindow;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(const QStringList &couleurs, QWidget* parent = 0 );
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
    void showEvent(QShowEvent *e);

private:
    Ui::MainWindow* ui;
    QProgressBar* m_progressbar;
    BDDGestionMp3* m_gestionMP3;
    QLabel* m_interaction;
    OngletMP3* m_ongletMP3;
    MainWindowLecteur* m_lecteur;
    DialogAjouterPhys* m_dialogajouterphys;
    DialogVidageBDD m_vidage;
    QPushButton* stop;
    QStringList m_couleurs;
#ifdef Q_OS_WIN
    QWinTaskbarButton* m_taskbarButton;
#endif
};

#endif // MAINWINDOW_H
