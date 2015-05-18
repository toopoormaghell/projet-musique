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
    ui->Id_Poch->setText(QString::number(1));

    QImage poch=m_bddInterface.afficherPochette("1","Pochette");
    ui->Pochette->setPixmap(affi.afficherPochetteLabel(poch));
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
    play.Id_Poch=ui->Id_Poch->text().toInt();
    QString mess=m_bddInterface.CreerPlaylist(play);

}
void DialogAjoutPlaylist::on_buttonBox_accepted()
{
    ajouterPlaylist();
}
void DialogAjoutPlaylist::on_pushButton_clicked()
{
    DialogChangerPochette tmp(25,this);
    tmp.exec();

    QImage poch=m_bddInterface.afficherPochette(tmp.getId(),"Pochette");
    ui->Pochette->setPixmap(affi.afficherPochetteLabel(poch));

    ui->Id_Poch->setText(tmp.getId());
}
