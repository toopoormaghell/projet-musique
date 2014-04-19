#ifndef DIALOGVIDERMP3_H
#define DIALOGVIDERMP3_H

#include <QDialog>
#include "bddinterface.h"

namespace Ui {
class DialogViderMp3;
}

class DialogViderMp3 : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogViderMp3(QWidget *parent = 0);
    ~DialogViderMp3();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogViderMp3 *ui;
     BDDInterface m_bddInterface;
};

#endif // DIALOGVIDERMP3_H
