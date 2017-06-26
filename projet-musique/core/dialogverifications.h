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
    explicit DialogVerifications(QWidget *parent = 0);
    ~DialogVerifications();

private slots:
    void on_pochvides_clicked();

    void on_auto_2_clicked();

    void on_mp3phys_clicked();

    void on_PochCompils_clicked();

private:
    Ui::DialogVerifications *ui;
    GestionVerifications* m_gestion;
};

#endif // DIALOGVERIFICATIONS_H
