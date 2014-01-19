#include "BDDcommun.h"
#include <QImage>
#include <QDir>
#include <QtSql>
#include "bddsingleton.h"
#include "util.h"
#include <ctime>
#include "barreavancement.h"

BDDCommun::BDDCommun(QObject *parent) :
    QObject(parent)
{
}
/*******************************************************
 *Permet de créer la BDD.
 *
 ******************************************************/
void BDDCommun::viderBDD()
{
    QStringList tables;
    QSqlQuery query;
    //Vidage de la base de données.
    tables <<  "MP3" << "Artiste" << "Album" << "Titre" << "Phys"<<"Pochette" << "InfosPlaylist" << "TitresPlaylist";
    int compt=0;
    while (compt<tables.size())
    {
        query = madatabase.exec("DROP Table " + tables[compt]);
        compt++;
    }
    //Création des Tables
    tables.clear();
    tables << "CREATE TABLE MP3 ('Id_MP3' INTEGER PRIMARY KEY,'Id_Titre' INTEGER, 'Chemin' VARCHAR(512),'Categorie' VARCHAR(255))";
    tables << "CREATE TABLE Artiste ('Id_Artiste' INTEGER PRIMARY KEY,'Artiste' VARCHAR(255),'Id_Pochette' INTEGER, 'NomSSAccents' VARCHAR(255))";
    tables << "CREATE TABLE Album ('Id_Album' INTEGER PRIMARY KEY,'Album' VARCHAR(255),'Id_Artiste' INTEGER,'Id_Pochette' INTEGER,'NomSSAccents' VARCHAR(255),'Annee' VARCHAR(255), 'Type' VARCHAR(255))";
    tables << "CREATE TABLE Titre ('Id_Titre' INTEGER PRIMARY KEY,'Titre' VARCHAR(255),'Id_Artiste' INTEGER,'Num_Piste' TINYINT,'Id_Pochette' INTEGER,'Id_Album' INTEGER,'TitreSSAccents' VARCHAR(255),'Duree' VARCHAR(255))";
    tables << "CREATE TABLE Phys ('Id_Phys' INTEGER PRIMARY KEY,'Id_Album' SMALLINT,'Categorie' VARCHAR(255))";
    tables << "CREATE TABLE TitresPlaylist ('Id_Playlist' SMALLINT,'Id_Titre' SMALLINT, 'Num_Piste' TINYINT)";
    tables << "CREATE TABLE InfosPlaylist ('Id_Playlist' INTEGER PRIMARY KEY,'Nom' VARCHAR(255),'Type' VARCHAR(255),'NomAlbum' VARCHAR(255),'Id_Pochette' SMALLINT)";
    tables << "CREATE TABLE Pochette ('Id_Pochette' INTEGER PRIMARY KEY,'Chemin' VARCHAR(512))";
    tables << "INSERT INTO Pochette VALUES (01,'def.jpg')";

    for (int i=0;i<tables.size();i++)
    {
        query = madatabase.exec(tables[i]);
    }
    //Vidage sur le DD du dossier Pochettes
    QString chemin=".\\Pochettes";
    removeDir(chemin, false);
}
/*******************************************************
 *Permet de supprimer les fichiers des pochettes
 *
 ******************************************************/
bool BDDCommun::removeDir(const QString &dirPath, const bool remove, const QString fichier)
{
    QDir folder(dirPath);
    folder.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    foreach(QFileInfo fileInfo, folder.entryInfoList())
    {
        if(fileInfo.isDir())
        {
            if(!removeDir(fileInfo.filePath()))
                return false;
        }
        else if(fileInfo.isFile())
        {
            if( ( fileInfo.fileName() != fichier ) && !QFile::remove(fileInfo.filePath()))
            {
                qDebug() << "Unable to remove file : " << fileInfo.filePath();
                return false;
            }
        }
        else
        {
            qDebug() << "autre chose: " << fileInfo.filePath();
        }
    }
    if(remove)
    {
        if (!QDir().rmdir(dirPath))
        {
            qDebug() << "Unable to remove folder : " << dirPath << ". Maybe this folder is not empty";
            return false;
        }
    }
    return true;
}
/*******************************************************
 *Récupère l'Id de la pochette
 *
 ******************************************************/
QString BDDCommun::lireIDPoch(const QString &ArtAlb)
{
    QString IdPoch;
    //On vérifie si la pochette existe ou non
    QString queryStr = "Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='" + ArtAlb+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Pochette VALUES (null,'" + ArtAlb+"')";
        query = madatabase.exec(queryStr);

        queryStr = "Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='" + ArtAlb+"'" ;
        query = madatabase.exec(queryStr);
        query.next();
    }

    QSqlRecord rec = query.record();
    IdPoch = rec.value( "Poch" ).toString();
    return IdPoch;
}
/*******************************************************
 *Récupère l'Id de l'artiste
 *
 ******************************************************/
QString BDDCommun::lireIDArtiste(const QStringList &Artiste)
{
    QString NomArt = Artiste[0];
    QString IdPoch = Artiste[1];
    QString IdArtiste;
    QString SansAccents = NomArt;
    EnleverAccents(SansAccents);
    QString Echange=EchangerArtiste(SansAccents);
    //On vérifie si l'artiste existe ou non
    QString queryStr = "Select Id_Artiste As 'Artiste' from Artiste WHERE NomSSAccents='" + SansAccents+"' OR NomSSACCENTS='" + Echange+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Artiste VALUES (null,'" + NomArt+ "','" + IdPoch + "','" + SansAccents +"')";
        query = madatabase.exec(queryStr);

        queryStr = "Select Id_Artiste As 'Artiste' from Artiste WHERE NomSSAccents='" + SansAccents+"'" ;
        query = madatabase.exec(queryStr);
        query.next();
    }
    QSqlRecord  rec = query.record();
    IdArtiste = rec.value( "Artiste" ).toString();

    return IdArtiste;
}
/*******************************************************
 *Récupère l'Id de l'album
 *
 ******************************************************/
QString BDDCommun::lireIDAlbum(const QStringList &Album)
{
    QString NomAlb = Album[0];
    QString IdPoch = Album[2];
    QString IdArtiste = Album[1];
    QString Annee= Album[4];
    QString IdAlbum;
    QString Albssaccent = NomAlb;
    EnleverAccents(Albssaccent);
    QString Type="Album";

    //On vérifie si l'album existe ou non
    QString queryStr =  " Select Id_Album As 'Album' from Album WHERE NomSSAccents='" + Albssaccent+"' AND Id_Artiste='"+ IdArtiste+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Album VALUES (null,'"+ NomAlb+ "','" + IdArtiste + "','" + IdPoch + "','" + Albssaccent +"','" + Annee+"','"+Type+"')";
        query = madatabase.exec(queryStr);

        queryStr = " Select Id_Album As 'Album' from Album WHERE NomSSAccents='" + Albssaccent+"' AND Id_Artiste='"+ IdArtiste+"'" ;
        query = madatabase.exec(queryStr);
        query.next();
    }
    QSqlRecord rec = query.record();
    IdAlbum = rec.value( "Album" ).toString();

    return IdAlbum;
}
/*******************************************************
 *Récupère l'Id du titre
 *
 ******************************************************/
QString BDDCommun::lireIDTitre(const QStringList& Titre)
{
    QString Tit= Titre[0];
    Tit.replace("'","$");
    QString NomTitre = Tit;
    EnleverAccents(NomTitre);
    QString IdAlb = Titre[1];
    QString IdArtiste = Titre[2];
    QString IdPoch = Titre[3];
    QString NumPiste= Titre[4];
    QString Duree=Titre[5];
    QString IdTitre;


    //On vérifie si l'album existe ou non
    QString queryStr =  "Select Id_Titre As 'Titre' from Titre WHERE TitreSSAccents='" + NomTitre +"' AND Id_Artiste='"+ IdArtiste+"' AND Id_Album='"+ IdAlb+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Titre VALUES (null,'"+ Tit+ "','"+ IdArtiste +"','"+ NumPiste +"','"+ IdPoch +"','"+ IdAlb +"','"+ NomTitre+"','"+ Duree +"')";
        query = madatabase.exec(queryStr);

        queryStr = "Select Id_Titre As 'Titre' from Titre WHERE TitreSSAccents='" + NomTitre +"' AND Id_Artiste='"+ IdArtiste+"' AND Id_Album='"+ IdAlb+"'" ;
        query = madatabase.exec(queryStr);
        query.next();
    }

    QSqlRecord rec = query.record();
    IdTitre = rec.value( "Titre" ).toString();

    return IdTitre;
}
/****************************************************
 *La fonction va vérifier si l'album a encore des
 *titres présents dans la BDD ou non
 *Param[0]= Id de l'album
 *Param[1]= Chemin de la pochette
 **************************************************/
void BDDCommun::supprimerAlbum( const QStringList& Param)
{
    //On vérifie si l'album existe ou non dans la table des titres
    QString queryStri =  "Select Id_Titre As 'Titre' from Titre WHERE Id_Album='"+ Param[0]+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la deuxième requête ne renvoie pas de résultat, on efface du coup l'album
    if (!query2.first()) {

        queryStri =  "DELETE FROM Album WHERE Id_Album='"+Param[0]+"'";
        query2 = madatabase.exec(queryStri);

        bool valid = QFile::remove(Param[1]);
    }
}
/****************************************************
 *La fonction va vérifier si l'artiste a encore des
 *albums présents dans la BDD
 *Param[0]=Id de l'artiste
 *Param[1]=Nom de l'artiste
 **************************************************/
void BDDCommun::supprimerArtiste(const QStringList &Param)
{

    //On vérifie si l'artiste existe ou non dans la table des albums
    QString queryStri =  "Select Id_Album As 'Alb' from Titre WHERE Id_Artiste='"+ Param[0]+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la requête ne renvoie pas de résultat, on efface du coup l'artiste
    if (!query2.first()) {

        queryStri =  "DELETE FROM Artiste WHERE Id_Artiste='"+Param[0]+"'";
        query2 = madatabase.exec(queryStri);

        QString nomArtiste( Param[1] );
        EnleverAccents( nomArtiste );
        QString artiste="./Pochettes/"+nomArtiste;
        qDebug() << artiste;
        QDir().rmdir(artiste);
    }
}
/****************************************************
 *La fonction va vérifier si le logiciel peut effacer
 *le titre sans poser de soucis.
 *Selon, la source de la suppression, les infos à transmettre seront différentes:
 *-----------Si le titre vient d'un MP3 viré-------------
 *infos[1]=Id_Titre
 *infos[2]=Id_Album
 *infos[0]= MP3
 *----------Si le titre vient d'un album Phys viré-----------
 *infos[1]=Id_Titre
 *infos[0]= Phys
 **************************************************/
void BDDCommun::supprimerTitre( const QStringList& infos)
{
    QString Id_Titre = infos[1];
    QString Param = infos[0];

    if (Param=="MP3") {
        QString Id_Alb=infos[2];
        //On va faire une première requête qui va donner les ID des artistes
        QString queryStr =  "Select Id_Phys As 'Id' from Phys WHERE Id_Album='"+Id_Alb+"'" ;
        QSqlQuery  query = madatabase.exec(queryStr);
        if (!query.first()) {

            queryStr =  "DELETE FROM Titre WHERE Id_Titre='"+Id_Titre+"'";

            query = madatabase.exec(queryStr);

            queryStr="DELETE FROM TitresPlaylist WHERE Id_Titre='"+Id_Titre+"'";
        }
    }
    if (Param=="Phys") {

        //On va faire une première requête qui va donner les ID des artistes
        QString queryStr =  "Select Id_MP3 As 'Id' from MP3 WHERE Id_Titre='"+Id_Titre+"'" ;
        QSqlQuery  query = madatabase.exec(queryStr);
        if (!query.first()) {

            queryStr =  "DELETE FROM Titre WHERE Id_Titre='"+Id_Titre+"'";

            query = madatabase.exec(queryStr);

        }
    }
}

/****************************************************
 *La fonction va vérifier si la pochette a encore des
 *titres présents dans la BDD
 **************************************************/
void BDDCommun::supprimerPoch(const QString& IdPoch)
{
    //On vérifie si l'artiste existe ou non dans la table des albums
    QString queryStri =  "Select Id_Titre As 'Tit' from Titre WHERE Id_Pochette='"+ IdPoch+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la requête ne renvoie pas de résultat, on efface du coup la pochette
    if (!query2.first()) {

        queryStri =  "DELETE FROM Pochette WHERE Id_Pochette='"+IdPoch+"'";
        query2 = madatabase.exec(queryStri);
    }
}

void BDDCommun::enregistrerObservateur(BarreAvancement *obs)
{
    obs->init();
    m_observateurs.insert( obs );
}

void BDDCommun::desenregistrerObservateur(BarreAvancement *obs)
{
    m_observateurs.remove( obs );
    obs->init();
}

void BDDCommun::notifierObservateurs(const QString &chemin, const float pourcentage)
{
    foreach ( BarreAvancement* obs, m_observateurs )
    {
        qDebug() << chemin << " " << pourcentage;
        obs->notifierPouah( chemin, pourcentage );
    }
}
