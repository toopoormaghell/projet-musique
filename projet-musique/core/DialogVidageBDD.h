#ifndef VIDAGEBDDDIALOG_H
#define VIDAGEBDDDIALOG_H

#include <QDialog>

namespace Ui
{
    class DialogVidageBDD;
}

class DialogVidageBDD : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVidageBDD( QWidget* parent = nullptr );
    ~DialogVidageBDD();

    bool Mp3;
    bool Phys;
    bool Config;

signals:
    void vidage();
private slots:
    void on_MP3_toggled( bool checked );
    void on_Phys_toggled( bool checked );
    void on_Config_toggled( bool checked );


    void on_buttonBox_accepted();
     void on_buttonBox_rejected();

private:
    Ui::DialogVidageBDD* ui;

};

#endif // VIDAGEBDDDIALOG_H
