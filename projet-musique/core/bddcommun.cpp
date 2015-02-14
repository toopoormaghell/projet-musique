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
    tables <<  "MP3" << "Artiste" << "Album" << "Titre" << "Phys"<<"Pochette" << "InfosPlaylist" << "TitresPlaylist" << "Relations"<< "ErreurPochettes";
    int compt=0;
    while (compt<tables.size())
    {
        query = madatabase.exec("DROP Table " + tables[compt]);
        compt++;
    }

    //Création des Tables
    tables.clear();
    tables << "CREATE TABLE MP3 ('Id_MP3' INTEGER PRIMARY KEY,'Id_Relation' INTEGER, 'Chemin' VARCHAR(512),'Categorie' VARCHAR(255))";
    tables << "CREATE TABLE Artiste ('Id_Artiste' INTEGER PRIMARY KEY,'Artiste' VARCHAR(255),'Id_Pochette' INTEGER, 'ArtisteSSAccents' VARCHAR(255))";
    tables << "CREATE TABLE Album ('Id_Album' INTEGER PRIMARY KEY,'Album' VARCHAR(255),'Id_Pochette' INTEGER,'AlbumSSAccents' VARCHAR(255),'Annee' VARCHAR(255), 'Type' VARCHAR(255))";
    tables << "CREATE TABLE Titre ('Id_Titre' INTEGER PRIMARY KEY,'Titre' VARCHAR(255),'Num_Piste' TINYINT,'TitreSSAccents' VARCHAR(255),'Duree' VARCHAR(255))";
    tables << "CREATE TABLE Phys ('Id_Phys' INTEGER PRIMARY KEY,'Id_Album' SMALLINT,'Categorie' VARCHAR(255),'CodeBarres' VARCHAR(255))";
    tables << "CREATE TABLE TitresPlaylist ('Id_Playlist' SMALLINT,'Id_Relation' SMALLINT, 'Num_Piste' TINYINT)";
    tables << "CREATE TABLE InfosPlaylist ('Id_Playlist' INTEGER PRIMARY KEY,'Nom' VARCHAR(255),'Type' VARCHAR(255),'NomAlbum' VARCHAR(255),'Id_Pochette' SMALLINT)";
    tables << "CREATE TABLE Pochette ('Id_Pochette' INTEGER PRIMARY KEY,'Chemin' VARCHAR(512))";
    tables << "INSERT INTO Pochette VALUES (01,'./pochettes/def.jpg')";
    tables << "INSERT INTO Artiste VALUES (01,'Divers','01','divers')";
    tables << "CREATE TABLE ErreurPochettes('Id_Erreur' INTEGER PRIMARY KEY,'Id_Pochette' SMALLINT,'Chemin' VARCHAR(255))";
    tables << "CREATE TABLE Relations('Id_Relation' INTEGER PRIMARY KEY,'Id_Titre' INTEGER,'Id_Album' INTEGER,'Id_Artiste' INTEGER,'Id_Pochette' INTEGER)";
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
QString BDDCommun::getdossierpardef()
{
    QString queryStr = "Select Valeur from Configuration WHERE Intitule='DossierParDef'" ;
    QSqlQuery  query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();

    return rec.value("Valeur").toString();

}
//Vérifie si la pochette existe
bool BDDCommun::verifPoch(const QString &ArtAlb)
{
    //On vérifie si la pochette existe ou non
    QString queryStr = "Select Id_Pochette from Pochette WHERE Chemin='" + ArtAlb+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first())
    {
        return false ;
    } else
    {
        return true;
    }
}

void BDDCommun::verifierBDD()
{
    //On vérifie si la table MP3 est conforme
    madatabase.exec("DELETE FROM Titre WHERE Titre = ''");
    madatabase.exec("DELETE FROM Artiste WHERE Artiste = ''");
    madatabase.exec("DELETE FROM Album WHERE Album = ''");
    madatabase.exec("DELETE FROM Pochette WHERE Chemin = ''");

    madatabase.exec("DELETE FROM Relations WHERE Id_Album NOT IN (SELECT DISTINCT Id_Album FROM Album) OR Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste) OR Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Titre) OR Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette From Pochette)");
    madatabase.exec("DELETE FROM Relations WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Phys) AND Id_Relation NOT IN ( SELECT DISTINCT Id_Relation FROM MP3) ");

    madatabase.exec("DELETE FROM MP3 WHERE Id_Relation NOT IN (SELECT DISTINCT Id_Relation FROM Relations)");
    madatabase.exec("DELETE FROM Phys WHERE Id_Album NOT IN (SELECT  Id_Album FROM Relations)");
}


//Récupère l'Id de la pochette
int BDDCommun::lireIDPoch(const QString &ArtAlb)
{
    //On vérifie si la pochette existe ou non
    QString queryStr = "Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='" + ArtAlb+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Pochette VALUES (null,'" + ArtAlb+"')";
        madatabase.exec(queryStr);

        return query.lastInsertId().toInt();
    } else
    {
        QSqlRecord rec = query.record();
        return rec.value( "Poch" ).toInt();
    }

}
//Récupère l'Id de l'artiste
int BDDCommun::lireIDArtiste(const QString &Artiste,const int &IdPoch)
{

    QString SansAccents = Artiste;
    EnleverAccents(SansAccents);
    QString Echange=EchangerArtiste(SansAccents);
    //On vérifie si l'artiste existe ou non
    QString queryStr = "Select Id_Artiste As 'Artiste' from Artiste WHERE ArtisteSSAccents='" + SansAccents+"' OR ArtisteSSACCENTS='" + Echange+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Artiste VALUES (null,'" + Artiste+ "','" + QString::number(IdPoch) + "','" + SansAccents +"')";
        madatabase.exec(queryStr);

        return query.lastInsertId().toInt();
    } else
    {
        QSqlRecord  rec = query.record();
        return rec.value( "Artiste" ).toInt();
    }

}
/*******************************************************
 *Récupère l'Id de l'album
 *
 ******************************************************/
int BDDCommun::lireIDAlbum(const QString &Album, int Id_Poch, int Id_Artiste, QString Annee, QString Type)
{
    QString Albssaccent = Album;
    EnleverAccents(Albssaccent);

    //On vérifie si l'album existe ou non
    QString queryStr = "Select A.Id_Album As 'Album' from Album A, Relations R WHERE AlbumSSAccents='" + Albssaccent+"' AND A.Type='"+Type+"' AND R.Id_Album=A.Id_Album AND R.Id_Pochette='"+ QString::number(Id_Poch)+"'" ;
    //  qDebug() << queryStr;
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Album VALUES (null,'"+ Album+ "','" +QString::number(Id_Poch) + "','" + Albssaccent +"','" + Annee+"','"+Type+"')";
        //   qDebug() << queryStr;
        madatabase.exec(queryStr);

        return query.lastInsertId().toInt();
    } else
    {
        QSqlRecord rec = query.record();

        return rec.value( "Album" ).toInt();
    }}

/*******************************************************
 *Récupère l'Id du titre
 *
 ******************************************************/
int BDDCommun::lireIDTitre(const QString &Titre, int IdAlb, int IdArtiste, int IdPoch,int NumPiste, QString Duree)
{
    QString TitreSSAccents = Titre;
    FormaterEntiteBDD(TitreSSAccents);

    //On vérifie si l'album existe ou non
    QString queryStr =  "Select T.Id_Titre As 'Titre' from Titre T, Relations R WHERE TitreSSAccents='" + TitreSSAccents +"' AND R.Id_Titre=T.Id_Titre AND R.Id_Artiste='"+QString::number(IdArtiste)+"' AND R.Id_Album='"+QString::number(IdAlb)+"'" ;

    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Titre VALUES (null,'"+ Titre+ "','"+QString::number(NumPiste) +"','"+ TitreSSAccents+"','"+ Duree +"')";

        madatabase.exec(queryStr);

        return query.lastInsertId().toInt();
    }

    QSqlRecord rec = query.record();

    return  rec.value( "Titre" ).toInt();
}

int BDDCommun::lireIDRelation(const int &Id_Alb, const int &Id_Artiste, const int &Id_Titre, const int &Id_Pochette)
{
    //on vérifie si la relation existe ou non
    QString queryStr= "SELECT Id_Relation from Relations WHERE Id_Titre='"+QString::number(Id_Titre)+"' AND Id_Artiste='"+QString::number(Id_Artiste)+"' AND Id_Album='"+QString::number(Id_Alb)+"' AND Id_Pochette='"+QString::number(Id_Pochette)+"'";

    QSqlQuery query = madatabase.exec(queryStr);

    if (!query.first())
    {
        queryStr="INSERT INTO Relations VALUES (null,'"+QString::number(Id_Titre)+"','"+QString::number(Id_Alb)+"','"+QString::number(Id_Artiste)+"','"+QString::number(Id_Pochette)+"')";
        madatabase.exec(queryStr);

        queryStr= "SELECT Id_Relation from Relations WHERE Id_Titre='"+QString::number(Id_Titre)+"' AND Id_Artiste='"+QString::number(Id_Artiste)+"' AND Id_Album='"+QString::number(Id_Alb)+"' AND Id_Pochette='"+QString::number(Id_Pochette)+"'";
        query = madatabase.exec(queryStr);
        query.next();

    }
    QSqlRecord rec= query.record();
    return rec.value("Id_Relation").toInt();
}
void BDDCommun::supprimerRelation(const int &Id_Relation)
{
    madatabase.exec("DELETE FROM Relations WHERE Id_Relation='"+QString::number(Id_Relation)+"'");
}

/****************************************************
 *La fonction va vérifier si l'album a encore des
 *titres présents dans la BDD ou non
 **************************************************/
bool BDDCommun::supprimerAlbum(const int &Id_Alb)
{
    bool supprimer=false;
    //On vérifie si l'album existe ou non dans la table des titres
    QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Album='"+QString::number(Id_Alb)+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la deuxième requête ne renvoie pas de résultat, on efface du coup l'album
    if (!query2.first()) {

        queryStri =  "DELETE FROM Album WHERE Id_Album='"+QString::number(Id_Alb)+"'";
        query2 = madatabase.exec(queryStri);

        supprimer=true;
    }
    return supprimer;
}
/****************************************************
 *La fonction va vérifier si l'artiste a encore des
 *albums présents dans la BDD
 **************************************************/
bool BDDCommun::supprimerArtiste(const int &Id_Artiste)
{
    bool supprimer=false;
    //On vérifie si l'artiste existe ou non dans la table des albums
    QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Artiste='"+QString::number(Id_Artiste)+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la requête ne renvoie pas de résultat, on efface du coup l'artiste
    if (!query2.first()) {

        queryStri =  "DELETE FROM Artiste WHERE Id_Artiste='"+QString::number(Id_Artiste)+"'";
        query2 = madatabase.exec(queryStri);

        supprimer=true;
    }
    return supprimer;
}
/****************************************************
 *La fonction va vérifier si le logiciel peut effacer
 *le titre sans poser de soucis.
 **************************************************/
bool BDDCommun::supprimerTitredePhys(const int &Id_Titre, const int &Id_Relation)
{
    bool supprimer=false;
    //On va faire une première requête qui va donner les ID des artistes
    QString queryStr =  "Select Id_MP3 As 'Id' from MP3 WHERE Id_Relation='"+QString::number(Id_Relation)+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);
    if (!query.first()) {
        queryStr =  "DELETE FROM Titre WHERE Id_Titre='"+QString::number(Id_Titre)+"'";
        madatabase.exec(queryStr);
        queryStr =  "DELETE FROM TitresPlaylist WHERE Id_Titre='"+QString::number(Id_Titre)+"'";
        query = madatabase.exec(queryStr);
        supprimerRelation(Id_Relation);

        supprimer=true;
    }
    return supprimer;
}
bool BDDCommun::supprimerTitredeMp3(const int Id_Album, const int Id_Titre, const int Id_Relation)
{
    bool supprimer=false;
    //On va faire une première requête qui va donner les ID des artistes
    QString queryStr =  "Select Id_Phys from Phys WHERE Id_Album='"+QString::number(Id_Album)+"'" ;
    QSqlQuery  query = madatabase.exec(queryStr);
    if (!query.first()) {
        queryStr =  "DELETE FROM Titre WHERE Id_Titre='"+QString::number(Id_Titre)+"'";
        madatabase.exec(queryStr);
        queryStr="DELETE FROM TitresPlaylist WHERE Id_Titre='"+QString::number(Id_Titre)+"'";
        query = madatabase.exec(queryStr);
        supprimerRelation(Id_Relation);
        supprimer=true;
    }
    return supprimer;
}
/****************************************************
 *La fonction va vérifier si la pochette a encore des
 *titres présents dans la BDD
 **************************************************/
void BDDCommun::supprimerPoch(const int& IdPoch, const QString Artiste, const QString Album)
{
    //On vérifie si l'artiste existe ou non dans la table des albums
    QString queryStri =  "Select Id_Titre As 'Tit' from Titre WHERE Id_Pochette='"+QString::number(IdPoch)+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la requête ne renvoie pas de résultat, on efface du coup la pochette
    if (!query2.first()) {

        queryStri =  "DELETE FROM Pochette WHERE Id_Pochette='"+QString::number(IdPoch)+"'";
        madatabase.exec(queryStri);

        queryStri="SELECT Nom from InfosPlaylist WHERE Id_Pochette='"+QString::number(IdPoch)+"'";
        query2 = madatabase.exec(queryStri);

        if (!query2.first())
        {
            QFile::remove(Album);
            QDir().rmdir(Artiste);
        }
    }
}
QString BDDCommun::AjouterPochette(AlbumGestion album)
{
    EnleverAccents(album.Artiste);
    EnleverAccents(album.Album);
    QDir dossier;
    QString chemin="./pochettes/"+album.Artiste;
    dossier.mkdir(chemin);
    chemin+="/"+album.Album+".jpg";
    album.Pochette.save(chemin);
    return chemin;
}
QString BDDCommun::AjouterPochette(CompilGestion album)
{
    EnleverAccents(album.Album);
    QDir dossier;
    QString chemin="./pochettes/Compils";
    dossier.mkdir(chemin);
    chemin+="/"+album.Album+".jpg";
    album.Pochette.save(chemin);
    return chemin;
}
QString BDDCommun::AjouterPochette(MP3Gestion mp3)
{
    EnleverAccents(mp3.Artiste);
    EnleverAccents(mp3.Album);
    QDir dossier;
    QString chemin="./pochettes/"+mp3.Artiste;
    dossier.mkdir(chemin);
    chemin+="/"+mp3.Album+".jpg";
    mp3.Pochette.save(chemin);
    return chemin;
}
QString BDDCommun::AjouterPochette(QString Type,QString Nom,QImage Image)
{
    EnleverAccents(Nom);
    QDir dossier;
    QString chemin="./pochettes/"+Type;
    dossier.mkdir(chemin);
    chemin+="/"+Nom+".jpg";
    Image.save(chemin);
    int temp= lireIDPoch(chemin);
    return QString::number(temp);
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
        //   qDebug() << chemin << " " << pourcentage;
        obs->notifierPouah( chemin, pourcentage );
    }
}
/*******************************************************
 *Permet de récupérer la pochette
 *
 ******************************************************/
QImage BDDCommun::afficherPochette(const QString &Id,const QString &Type)
{
    QString queryStr;
    if (Type=="Album")
    {
        queryStr="SELECT P.Chemin FROM Album Al,Pochette P WHERE Al.Id_Pochette=P.Id_Pochette AND Al.Id_Album='"+Id+"'";
    }
    if (Type=="Artiste")
    {
        queryStr="SELECT P.Chemin FROM Artiste Ar,Pochette P WHERE Ar.Id_Pochette=P.Id_Pochette AND Ar.Id_Artiste='"+Id+"'";
    }
    if (Type=="Titre")
    {
        queryStr="SELECT P.Chemin FROM Titre T,Pochette P WHERE T.Id_Pochette=P.Id_Pochette AND T.Id_Titre='"+Id+"'";
    }
    if (Type=="Pochette")
    {
        queryStr="SELECT Chemin FROM Pochette WHERE Id_Pochette='"+Id+"'";
    }

    QSqlQuery query= madatabase.exec(queryStr);

    query.next();
    QSqlRecord rec=query.record();

    QString Chemin=rec.value("Chemin").toString();

    QImage* image2=new QImage(Chemin);
    QImage image=*image2;
    return image;
}
bool BDDCommun::verifierTitreMp3Phys(int Id_Titre)
{
    bool TitreenMp3etPhys=false;

    QString queryStri =  "SELECT R.Id_Titre FROM MP3 M, Phys P, Relations R WHERE R.Id_Relation = M.Id_Relation AND R.Id_Album=P.Id_Album AND R.Id_Titre="+QString::number(Id_Titre);
    QSqlQuery  query = madatabase.exec(queryStri);

    //si la requête ne renvoie pas de résultat, on efface du coup la pochette
    if (query.first()) {
        TitreenMp3etPhys=true;
    }
    return TitreenMp3etPhys;
}
QStringList BDDCommun::ListeArtistes()
{
    QStringList liste;
    QString queryStri ="SELECT Id_Artiste, Artiste FROM Artiste ORDER BY NomSSAccents";
    QSqlQuery query= madatabase.exec(queryStri);

    while( query.next() )
    {
        QSqlRecord rec=query.record();
        liste << rec.value("Artiste").toString().replace("$","'");
        liste << rec.value("Id_Artiste").toString();
    }
    QStringList liste2mots=Artistea2mots(liste);
    return liste2mots;
}
QStringList BDDCommun::Artistea2mots(QStringList Artistes)
{
    QStringList art2mots;

    for(int cpt=0;cpt<Artistes.count();cpt=cpt+2)
    {
        QStringList temp=Artistes[cpt].split(" ");
        if (temp.size()==2)
        {
            art2mots << Artistes[cpt] << Artistes[cpt+1];
        }
    }
    return art2mots;
}
QStringList BDDCommun::ListeArtistesInvers()
{
    QStringList liste=ListeArtistes();
    QStringList resultat;
    for(int cpt=0;cpt<liste.count();cpt=cpt+2)
    {
        resultat << EchangerArtiste(liste[cpt]) << liste[cpt+1];
    }
    return resultat;
}
void BDDCommun::EnregistrerDossierParDef(QString doss)
{
    QString queryStri ="Update Configuration SET Valeur='"+doss+"' WHERE Intitule='DossierParDef'";
    QSqlQuery query= madatabase.exec(queryStri);
}
void BDDCommun::CopierBDD()
{
    QString cheminBDD="./Musique.db";
    QFile temp(cheminBDD);
    QString cheminCopie="../Musique.db";
    temp.copy(cheminCopie);
}
void BDDCommun::ChargerBDD()
{
    QString cheminBDD="../Musique.db";
    QFile temp(cheminBDD);
    QString cheminCopie="./Musique.db";
    temp.copy(cheminCopie);
}
QList<Pochette> BDDCommun::ListePochettes()
{
    QList<Pochette> liste;

    Pochette poch;

    //Ajout de la pochette par défaut, au début de la liste
    poch.Id_Poch=1;
    poch.Nom="def.jpg";
    poch.Pochette=afficherPochette(QString::number(poch.Id_Poch),"Pochette");
    liste << poch;

    QString queryStr="SELECT Id_Pochette, Chemin FROM Pochette WHERE Id_Pochette!='1' ORDER BY Chemin";
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next())
    {
        QSqlRecord rec=query.record();

        poch;
        poch.Id_Poch = rec.value("Id_Pochette").toInt();
        QStringList temp=(rec.value("Chemin").toString()).split("./pochettes/");
        poch.Nom=temp[1];
        poch.Pochette=afficherPochette(QString::number(poch.Id_Poch),"Pochette");

        liste << poch;
    }
    return liste;
}
void BDDCommun::EchangerArtistes(QString Artiste, QString Id_Artiste)
{
    QString SansAccents = Artiste;
    EnleverAccents(SansAccents);

    QString queryStr="SELECT Id_Artiste from Artiste WHERE NomSSAccents='"+ SansAccents+"'";
    QSqlQuery query= madatabase.exec(queryStr);

    if(!query.first())
    {
        queryStr="UPDATE Artiste SET NomSSAccents='"+SansAccents+"', Artiste='"+Artiste+"' WHERE Id_Artiste="+Id_Artiste;
        query =madatabase.exec(queryStr);
    }
}
