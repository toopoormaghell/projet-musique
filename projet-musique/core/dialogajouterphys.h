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

private:
    Ui::DialogAjouterPhys *ui;
};

#endif // DIALOGAJOUTERPHYS_H
