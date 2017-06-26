#include "DialogVidageBDD.h"
#include "ui_DialogVidageBDD.h"
#include "bddsingleton.h"
#include "bddgestionmp3.h"
DialogVidageBDD::DialogVidageBDD( QWidget* parent ) :
    QDialog( parent ),
    Mp3( true ),
    Phys( true ),
    Config( true ),
    ui( new Ui::DialogVidageBDD )
{
    ui->setupUi( this );
}

DialogVidageBDD::~DialogVidageBDD()
{
    delete ui;
}

void DialogVidageBDD::on_MP3_toggled( bool checked )
{
    Q_UNUSED( checked );
    Mp3 = ui->MP3->isChecked();
}

void DialogVidageBDD::on_Phys_toggled( bool checked )
{
    Q_UNUSED( checked );
    Phys = ui->Phys->isChecked();
}

void DialogVidageBDD::on_Config_toggled( bool checked )
{
    Q_UNUSED( checked );
    Config = ui->Config->isChecked();
}

void DialogVidageBDD::on_buttonBox_accepted()
{
    Mp3 = ui->MP3->isChecked();
    Phys = ui->Phys->isChecked();
    Config = ui->Config->isChecked();
    emit vidage();
}
