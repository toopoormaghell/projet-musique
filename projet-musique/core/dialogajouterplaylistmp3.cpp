#include "dialogajouterplaylistmp3.h"
#include "ui_dialogajouterplaylistmp3.h"
#include "dialogajoutplaylist.h"
#include <QDebug>
DialogAjouterPlaylistMp3::DialogAjouterPlaylistMp3(QString Id_Mp3, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjouterPlaylistMp3)
{
    ui->setupUi(this);
    afficherListePlaylists();
    Mp3= Id_Mp3;

}
DialogAjouterPlaylistMp3::~DialogAjouterPlaylistMp3()
{
    delete ui;
}
void DialogAjouterPlaylistMp3::afficherListePlaylists()
{
    ui->ListePlaylists->clear();
    QList<PlaylistGestion> liste=m_bddInterface.ListesPlaylist();
    for(int cpt=0;cpt<liste.count();cpt++)
    {
        PlaylistGestion play=liste[cpt];
        QListWidgetItem *mediaCell=affi.afficherPochetteList(play.Pochette);
        //On s'occupe du nom
        mediaCell->setText(play.Titre);
        mediaCell->setData(Qt::UserRole,play.Id_Playlist);
        ui->ListePlaylists->addItem(mediaCell);
    }
    ui->ListePlaylists->setCurrentRow(0);
}
void DialogAjouterPlaylistMp3::on_NouvellePlaylist_clicked()
{
    DialogAjoutPlaylist temp(this);
    temp.exec();
    afficherListePlaylists();
}
void DialogAjouterPlaylistMp3::ajouterMp3dansPlaylist()
{

m_bddInterface.AjouterMP3dansPlaylist(Mp3.toInt(),choixPlaylist().toInt());

}
QString DialogAjouterPlaylistMp3::choixPlaylist()
{
    QListWidgetItem *item=ui->ListePlaylists->currentItem();
    if (item==NULL)
    {
        item=ui->ListePlaylists->item(0);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}

void DialogAjouterPlaylistMp3::on_buttonBox_accepted()
{
    ajouterMp3dansPlaylist();

}
