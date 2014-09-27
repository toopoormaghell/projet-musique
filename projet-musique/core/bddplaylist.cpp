#include "bddplaylist.h"
#include <QtSql>
#include <QDir>
#include "bddsingleton.h"

BDDPlaylist::BDDPlaylist(QObject *parent) :
    BDDMp3( parent )
{
}
PlaylistGestion BDDPlaylist::RecupererInfosPlaylist(QString Id)
{
    PlaylistGestion playlist;
    QString queryStr="SELECT Nom,Type,NomAlbum,Id_Pochette FROM InfosPlaylist WHERE Id_Playlist="+Id;
    QSqlQuery query=madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec=query.record();

    playlist.Titre=rec.value("Nom").toString();
    playlist.Id_Poch=rec.value("Id_Pochette").toInt();
    playlist.AlbumChanger=rec.value("NomAlbum").toString();
    playlist.Id_Playlist=Id.toInt();
    playlist.Pochette=afficherPochette(QString::number(playlist.Id_Poch),"Pochette");

    if(rec.value("Type").toString()=="Changement")
    {
        playlist.ChangerAlbum=true;
    } else
    {
        playlist.ChangerAlbum=false;
    }
    playlist.titres=RecupererPistesPlaylist(Id);
    playlist.NombrePistes=playlist.titres.count();
    return playlist;
}
QList<MP3Gestion> BDDPlaylist::RecupererPistesPlaylist(QString Id)
{
    QList<MP3Gestion> liste;

    QString queryStr="SELECT Id_Titre, Num_Piste From TitresPlaylist WHERE Id_Playlist='"+Id+"' ORDER BY Num_Piste";
    QSqlQuery query=madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        MP3Gestion mp3;
        mp3=RecupererInfosMp3(rec.value("Id_Titre").toInt());
        mp3.Num_Piste=rec.value("Num_Piste").toInt();
        liste << mp3;
    }
    return liste;
}
QList<PlaylistGestion> BDDPlaylist::ListesPlaylist()
{
    QList<PlaylistGestion> liste;

    QString queryStr="SELECT DISTINCT Id_Playlist FROM InfosPlaylist";
    QSqlQuery query=madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        PlaylistGestion playlist=RecupererInfosPlaylist(rec.value("Id_Playlist").toString());
        liste << playlist;
    }
    return liste;
}
QString BDDPlaylist::CreerPlaylist(PlaylistGestion play)
{
    bool verif=true;
    QString message;
    QString type;
    if(play.ChangerAlbum)
    {
        type="Changement";

    } else
    {
        type="Non";
    }

    QString queryStr="SELECT DISTINCT Nom FROM InfosPlaylist";
    QSqlQuery query=madatabase.exec(queryStr);
    while (query.next())
    {

        QSqlRecord rec=query.record();
        if(rec.value("Nom").toString()==play.Titre)
        {
            verif=false;
            message="meme nom";
        }
    }
    if (verif)
    {
        queryStr="INSERT INTO InfosPlaylist VALUES (null,'"+play.Titre+"','"+type+"','"+play.AlbumChanger+"','"+QString::number(play.Id_Poch)+"')";
        query=madatabase.exec(queryStr);
        message="fait";
    }
    return message;
}
void BDDPlaylist::AjouterMP3dansPlaylist(int IdMp3, int IdPlay)
{
    QString queryStr="SELECT DISTINCT Id_Mp3 FROM TitresPlaylist WHERE Id_Playlist='"+QString::number(IdPlay)+"'";
    QSqlQuery query=madatabase.exec(queryStr);

    if (!query.first())
    {

int Piste=NumPisteMaxPlaylist(IdPlay)+1;

        queryStr="INSERT INTO TitresPlaylist VALUES ('"+QString::number(IdPlay)+"','"+QString::number(IdMp3)+"','"+QString::number(Piste)+"')";
        query=madatabase.exec(queryStr);
    }

}
int BDDPlaylist::NumPisteMaxPlaylist(int IdPlay)
{
    QString queryStr="SELECT MAX(Num_Piste) AS 'Max' FROM TitresPlaylist WHERE Id_Playlist='"+QString::number(IdPlay)+"'";
    QSqlQuery query= madatabase.exec(queryStr);

    while (query.next())
    {
        QSqlRecord rec=query.record();
        return rec.value("Max").toInt();
    }
}
QStringList BDDPlaylist::listePlaylistMP3(QString Id)
{
    QStringList liste;
    QString queryStr;
    queryStr="SELECT P.Chemin AS 'Chemin',I.Nom AS 'Nom' FROM InfosPlaylist I, Pochette P, TitresPlaylist T WHERE P.Id_Pochette=I.Id_Pochette AND T.Id_Playlist=I.Id_Playlist AND T.Id_Titre="+Id;
    QSqlQuery query = madatabase.exec((queryStr));
    while (query.next())
    {
        QSqlRecord rec=query.record();
        QString Chemin=rec.value("Chemin").toString();
        QString Nom=rec.value("Nom").toString().replace("$","'");

        liste << Nom << Chemin;
    }
    return liste;
}
