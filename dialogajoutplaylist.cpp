#include "dialogajoutplaylist.h"
#include "ui_dialogajoutplaylist.h"
#include "util.h"
#include "QDebug"
#include "dialogchangerpochette.h"

DialogAjoutPlaylist::DialogAjoutPlaylist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjoutPlaylist)
{
    ui->setupUi(this);
}
DialogAjoutPlaylist::~DialogAjoutPlaylist()
{
    delete ui;
}
void DialogAjoutPlaylist::ajouterPlaylist()
{
    PlaylistGestion play;
    play.Titre=ui->Titre->text();
    play.AlbumChanger=ui->AlbumChanger->text();
    play.ChangerAlbum=ui->PlaylistenAlbum->isChecked();
    play.Id_Poch=1;
    QString mess=m_bddInterface.CreerPlaylist(play);
    qDebug() << mess;
}
void DialogAjoutPlaylist::on_buttonBox_accepted()
{
    ajouterPlaylist();
}
void DialogAjoutPlaylist::on_pushButton_clicked()
{
    DialogChangerPochette tmp(this);
    tmp.exec();
qDebug() << tmp.getId();
}
