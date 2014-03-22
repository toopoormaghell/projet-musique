#include "dialogajouterplaylistmp3.h"
#include "ui_dialogajouterplaylistmp3.h"
#include "dialogajoutplaylist.h"

DialogAjouterPlaylistMp3::DialogAjouterPlaylistMp3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjouterPlaylistMp3)
{
    ui->setupUi(this);
    afficherListePlaylists();
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
        QListWidgetItem *mediaCell=new QListWidgetItem;
        mediaCell=affi.afficherPochetteList(&play.Pochette);
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
