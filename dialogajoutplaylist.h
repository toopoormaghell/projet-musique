#ifndef DIALOGAJOUTPLAYLIST_H
#define DIALOGAJOUTPLAYLIST_H

#include <QDialog>
#include "bddinterface.h"
namespace Ui {
class DialogAjoutPlaylist;
}

class DialogAjoutPlaylist : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAjoutPlaylist(QWidget *parent = 0);
    ~DialogAjoutPlaylist();
    
    void ajouterPlaylist();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::DialogAjoutPlaylist *ui;
    BDDInterface m_bddInterface;
};

#endif // DIALOGAJOUTPLAYLIST_H
