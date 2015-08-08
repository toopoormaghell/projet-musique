#include "modifieralbumdialog.h"
#include "ui_modifieralbumdialog.h"

ModifierAlbumDialog::ModifierAlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierAlbumDialog)
{
    ui->setupUi(this);
}

ModifierAlbumDialog::~ModifierAlbumDialog()
{
    delete ui;
}
