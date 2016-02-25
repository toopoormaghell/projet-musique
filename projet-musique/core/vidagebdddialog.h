#ifndef VIDAGEBDDDIALOG_H
#define VIDAGEBDDDIALOG_H

#include <QDialog>

namespace Ui
{
    class VidageBDDDialog;
}

class VidageBDDDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VidageBDDDialog(QWidget *parent = 0);
    ~VidageBDDDialog();

    bool Mp3;
    bool Phys;
    bool Config;

signals:
    void vidage();
private slots:
    void on_MP3_toggled(bool checked);
    void on_Phys_toggled(bool checked);
    void on_Config_toggled(bool checked);


    void on_buttonBox_accepted();

private:
    Ui::VidageBDDDialog *ui;

};

#endif // VIDAGEBDDDIALOG_H
