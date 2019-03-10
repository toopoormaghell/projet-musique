#ifndef DIALOGVERIFICATIONS_H
#define DIALOGVERIFICATIONS_H

#include <QDialog>
#include "gestionverifications.h"

namespace Ui {
    class DialogVerifications;
}

class DialogVerifications : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVerifications(QWidget *parent = nullptr);
    ~DialogVerifications();

public slots:
    void EcrireMessage(QString texte);
private slots:
    void on_pochvides_clicked();

    void on_auto_2_clicked();

    void on_mp3phys_clicked();

    void on_Reformatage_clicked();

    void on_majuscules_clicked();

    void on_ArtisteCompilAlbum_clicked();

    void on_Virgule_clicked();

    void on_doublontitre_clicked();

    void on_doublonealbum_clicked();

    void on_doublonartiste_clicked();

    void on_integritetout_clicked();

    void on_integritepoch_clicked();

    void on_integriterelations_clicked();

    void on_integritemp3_clicked();

    void on_integritephys_clicked();

    void on_integritealbums_clicked();

    void on_integriteartistes_clicked();

    void on_integritetitres_clicked();

private:
    Ui::DialogVerifications *ui;
    GestionVerifications* m_gestion;

};

#endif // DIALOGVERIFICATIONS_H
