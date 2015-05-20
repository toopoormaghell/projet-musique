#ifndef DIALOGAJOUTERPHYS_H
#define DIALOGAJOUTERPHYS_H

#include <QDialog>

namespace Ui {
class DialogAjouterPhys;
}

class DialogAjouterPhys : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjouterPhys(QWidget *parent = 0);
    ~DialogAjouterPhys();

    QString recupererEAN() const;
private slots:
    void on_buttonBox_accepted();

    void on_ChercherEAN_clicked();

private:
    Ui::DialogAjouterPhys *ui;
};

#endif // DIALOGAJOUTERPHYS_H
