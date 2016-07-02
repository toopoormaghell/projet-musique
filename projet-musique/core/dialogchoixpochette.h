#ifndef DIALOGCHOIXPOCHETTE_H
#define DIALOGCHOIXPOCHETTE_H

#include <QDialog>
#include "bddaffichermp3.h"
#include <QStandardItemModel>
namespace Ui {
class DialogChoixPochette;
}

class DialogChoixPochette : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChoixPochette(QString artiste, QWidget *parent = 0);
    ~DialogChoixPochette();
    int m_selection;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::DialogChoixPochette *ui;
    void AfficherPochettes();
    QStandardItemModel m_pochettes;
    QString m_artiste;
    int RecupererPochetteSelectionnee();
};

#endif // DIALOGCHOIXPOCHETTE_H
