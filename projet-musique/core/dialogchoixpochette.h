#ifndef DIALOGCHOIXPOCHETTE_H
#define DIALOGCHOIXPOCHETTE_H

#include <QDialog>
#include "bddaffichermp3.h"
#include <QListWidgetItem>

namespace Ui {
    class DialogChoixPochette;
}

class DialogChoixPochette : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChoixPochette(QString artiste, QWidget *parent = nullptr);
    ~DialogChoixPochette();
    int m_selection;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_ListePoch_itemClicked(QListWidgetItem *item);

    void on_NewPoch_clicked();
    void RelancePochettes();
private:
    Ui::DialogChoixPochette *ui;
    void AfficherPochettes();
    QString m_artiste;
    QString m_nom_artiste;
};

#endif // DIALOGCHOIXPOCHETTE_H
