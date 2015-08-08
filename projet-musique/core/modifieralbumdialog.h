#ifndef MODIFIERALBUMDIALOG_H
#define MODIFIERALBUMDIALOG_H

#include <QDialog>

namespace Ui {
class ModifierAlbumDialog;
}

class ModifierAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierAlbumDialog(QWidget *parent = 0);
    ~ModifierAlbumDialog();

private:
    Ui::ModifierAlbumDialog *ui;
};

#endif // MODIFIERALBUMDIALOG_H
