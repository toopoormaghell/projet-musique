#include "ongletplaylist.h"
#include "ui_ongletplaylist.h"
#include "util.h"
#include "dialogajoutplaylist.h"
OngletPlaylist::OngletPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OngletPlaylist)
{
    ui->setupUi(this);
    afficherListePlaylists();

}
OngletPlaylist::~OngletPlaylist()
{
    delete ui;
}
void OngletPlaylist::afficherInfosPlaylist()
{
    nettoyer();

    PlaylistGestion play=m_bddInterface.RecupererInfosPlaylist(choixPlaylist());

    //On affiche la pochette
    ui->Pochette->setPixmap(affi.afficherPochetteLabel(&play.Pochette));

    //On affiche le titre
    ui->TitrePlaylist->setText(play.Titre);

    //On affiche si on doit changer le titre de l'album ou non
    if (play.ChangerAlbum)
    {
        ui->Oui->setChecked(true);

        //On affiche le nom de l'album si il doit changer
        ui->NomChange->setText(play.AlbumChanger);
    } else {
        ui->Non->setChecked(true);
        ui->NomChange->hide();
    }
    //On affiche le nombre de pistes
    ui->NombrePistes->setText(QString::number(play.NombrePistes));

    //On affiche les mp3
    for (int cpt=0;cpt<play.titres.count();cpt++)
    {
        afficherTitrePlaylist(play.titres[cpt]);
    }
}
void OngletPlaylist::nettoyer()
{
    ui->Pochette->clear();
    ui->TitrePlaylist->clear();
    ui->Oui->setChecked(false);
    ui->Non->setChecked(false);
    ui->NomChange->clear();
    ui->NombrePistes->clear();
    ui->Playlist->clear();
}

QString OngletPlaylist::choixPlaylist()
{
    QListWidgetItem *item=ui->ListePlaylists->currentItem();
    if (item==NULL)
    {
        item=ui->ListePlaylists->item(0);
    }
    return item != NULL ? item->data(Qt::UserRole).toString() : QString();
}

void OngletPlaylist::afficherTitrePlaylist(MP3Gestion mp3)
{
    QListWidgetItem *mediaCell= affi.afficherPochetteList(&mp3.Pochette);
    //On s'occupe du nom du mp3
    if(mp3.Type=="Album")
    {
       mediaCell->setText((QString::number(mp3.Num_Piste)).rightJustified(2,'0')+" - "+mp3.Titre+" de "+mp3.Artiste+("(")+mp3.Album+")");
    } else {
        mediaCell->setText((QString::number(mp3.Num_Piste)).rightJustified(2,'0')+" - "+mp3.Titre+" de "+mp3.Artiste);
    }

    mediaCell->setData(Qt::UserRole,mp3.Id_Titre);
    ui->Playlist->addItem(mediaCell);
}
void OngletPlaylist::afficherListePlaylists()
{
    ui->ListePlaylists->clear();
    QList<PlaylistGestion> liste=m_bddInterface.ListesPlaylist();
    for(int cpt=0;cpt<liste.count();cpt++)
    {
        PlaylistGestion play=liste[cpt];
        QListWidgetItem *mediaCell=affi.afficherPochetteList(&play.Pochette);
        //On s'occupe du nom
        mediaCell->setText(play.Titre);
        mediaCell->setData(Qt::UserRole,play.Id_Playlist);
        ui->ListePlaylists->addItem(mediaCell);
    }
    ui->ListePlaylists->setCurrentRow(0);
}

void OngletPlaylist::on_ListePlaylists_currentRowChanged(int currentRow)
{
    afficherInfosPlaylist();
}

void OngletPlaylist::on_Ajouter_clicked()
{
    DialogAjoutPlaylist temp(this);
    temp.exec();
    afficherListePlaylists();
}
