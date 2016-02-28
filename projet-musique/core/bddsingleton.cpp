#include "bddsingleton.h"

#include <QStringList>
#include <qdebug.h>
#include <QtSql>
#include <QDir>
#include <QFileInfo>

BDDSingleton BDDSingleton::s_singleton;

BDDSingleton::BDDSingleton():
    m_database()
{
    m_database = QSqlDatabase::addDatabase( "QSQLITE" );
    m_database.setHostName( "localhost" );
    m_database.setDatabaseName( "Musique.db" );
    m_database.setUserName( "root" );
    m_database.setPassword( "" );

    //Si la BDD n'est pas ouverte,elle affiche une erreur
    if ( !m_database.open() )
    {
        qDebug() << "Impossible d'ouvrir la base de données !";
    }

    QStringList tables = m_database.tables();
    if ( tables.count() == 0 )
    {

        creationBase();
    }
}

BDDSingleton::~BDDSingleton()
{
    m_database.close();
}

BDDSingleton& BDDSingleton::getInstance()
{
    return s_singleton;
}
QSqlDatabase& BDDSingleton::getDataBase()
{
    return m_database;
}
void BDDSingleton::creationBase()
{
    QStringList tables;
    QSqlQuery query;
    tables << "CREATE TABLE MP3 ('Id_MP3' INTEGER PRIMARY KEY,'Id_Relation' INTEGER, 'Chemin' VARCHAR(512),'Categorie' VARCHAR(255))";
    tables << "CREATE TABLE Artiste ('Id_Artiste' INTEGER PRIMARY KEY,'Artiste' VARCHAR(255),'Id_Pochette' INTEGER, 'Artiste_Formate' VARCHAR(255))";
    tables << "CREATE TABLE Album ('Id_Album' INTEGER PRIMARY KEY,'Album' VARCHAR(255),'Id_Pochette' INTEGER,'Album_Formate' VARCHAR(255),'Annee' VARCHAR(255), 'Type' VARCHAR(255))";
    tables << "CREATE TABLE Titre ('Id_Titre' INTEGER PRIMARY KEY,'Titre' VARCHAR(255),'Num_Piste' TINYINT,'Titre_Formate' VARCHAR(255),'Duree' VARCHAR(255))";
    tables << "CREATE TABLE Phys ('Id_Phys' INTEGER PRIMARY KEY,'Id_Album' SMALLINT,'Categorie' VARCHAR(255),'CodeBarres' VARCHAR(255))";
    tables << "CREATE TABLE TitresPlaylist ('Id_Playlist' SMALLINT,'Id_Relation' SMALLINT, 'Num_Piste' TINYINT)";
    tables << "CREATE TABLE InfosPlaylist ('Id_Playlist' INTEGER PRIMARY KEY,'Nom' VARCHAR(255),'Type' VARCHAR(255),'NomAlbum' VARCHAR(255),'Id_Pochette' SMALLINT)";
    tables << "CREATE TABLE Pochette ('Id_Pochette' INTEGER PRIMARY KEY,'Chemin' VARCHAR(512))";
    tables << "CREATE TABLE Type ('Id_Type' INTEGER PRIMARY KEY,'Type' VARCHAR(255))";
    tables << "INSERT INTO Pochette VALUES (01,'./pochettes/def.jpg')";
    tables << "INSERT INTO Artiste VALUES (01,'Divers','01','divers')";
    tables << "CREATE TABLE ErreurPochettes('Id_Erreur' INTEGER PRIMARY KEY,'Id_Pochette' SMALLINT,'Chemin' VARCHAR(255))";
    tables << "CREATE TABLE Relations('Id_Relation' INTEGER PRIMARY KEY,'Id_Titre' INTEGER,'Id_Album' INTEGER,'Id_Artiste' INTEGER)";
    tables << "CREATE TABLE Configuration('Intitule' TEXT,'Valeur' TEXT)";
    tables << "INSERT INTO Configuration VALUES ('DossierParDef','F:/Albums')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserAlbums','Oui')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserCompil','Non')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserLives','Non')";
    tables << "INSERT INTO Type VALUES(01,'Album')";
    tables << "INSERT INTO Type VALUES(02,'Compil')";
    tables << "INSERT INTO Type VALUES(03,'Single')";
    tables << "INSERT INTO Type VALUES(04,'BOF')";
    tables << "INSERT INTO Type VALUES(05,'Spectacle musical')";
    tables << "INSERT INTO Type VALUES(06,'Télé Réalités')";
    tables << "INSERT INTO Type VALUES(07,'New Age')";
    tables << "INSERT INTO Type VALUES(08,'Classique')";
    tables << "INSERT INTO Type VALUES(09,'Générique')";
    tables << "INSERT INTO Type VALUES(10,'Reprises')";
    for ( int i = 0; i < tables.size(); i++ )
    {
        query = madatabase.exec( tables[i] );
    }
}
void BDDSingleton::viderBDD()
{
    QStringList tables;
    QSqlQuery query;
    //Vidage de la base de données.
    tables <<  "MP3" << "Artiste" << "Album" << "Titre" << "Phys" << "Pochette" << "InfosPlaylist" << "TitresPlaylist" << "Relations" << "ErreurPochettes" << "Configuration";
    int compt = 0;
    while ( compt < tables.size() )
    {
        query = madatabase.exec( "DROP Table " + tables[compt] );
        compt++;
    }

    //Vidage sur le DD du dossier Pochettes
    QString chemin = ".\\Pochettes";
    removeDir( chemin, false );

    creationBase();

}
/*******************************************************
 *Permet de supprimer les fichiers des pochettes
 *
 ******************************************************/
bool BDDSingleton::removeDir( const QString& dirPath, const bool remove, const QString fichier )
{
    QDir folder( dirPath );
    folder.setFilter( QDir::NoDotAndDotDot | QDir::AllEntries );
    foreach ( QFileInfo fileInfo, folder.entryInfoList() )
    {
        if ( fileInfo.isDir() )
        {
            if ( !removeDir( fileInfo.filePath() ) )
                return false;
        }
        else if ( fileInfo.isFile() )
        {
            if ( ( fileInfo.fileName() != fichier ) && !QFile::remove( fileInfo.filePath() ) )
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
    if ( remove )
    {
        if ( !QDir().rmdir( dirPath ) )
        {
            qDebug() << "Unable to remove folder : " << dirPath << ". Maybe this folder is not empty";
            return false;
        }
    }
    return true;
}

void BDDSingleton::verifierBDD()
{
    madatabase.exec( "DELETE FROM Titre WHERE Titre = ''" );
    madatabase.exec( "DELETE FROM Artiste WHERE Artiste = ''" );
    madatabase.exec( "DELETE FROM Album WHERE Album = ''" );

    madatabase.exec( "DELETE FROM Relations WHERE Id_Album NOT IN (SELECT DISTINCT Id_Album FROM Album) OR Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste) OR Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Titre) OR Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette From Pochette)" );
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Phys) AND Id_Relation NOT IN ( SELECT DISTINCT Id_Relation FROM MP3) " );
    madatabase.exec( "DELETE FROM MP3 WHERE Id_Relation NOT IN (SELECT DISTINCT Id_Relation FROM Relations)" );
    madatabase.exec( "DELETE FROM Phys WHERE Id_Album NOT IN (SELECT  Id_Album FROM Relations)" );

    //Vérification que la pochette existe toujours
    QString queryStr = "SELECT Id_Pochette, Chemin FROM POCHETTE";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();

        QString chemin = rec.value("Chemin").toString();

        if ( !QFile::exists( chemin ) )
        {
            QString quer = "DELETE FROM Pochette WHERE Id_Pochette= '"+rec.value("Id_Pochette").toString()+"'";
            madatabase.exec(quer);
        }
    }
    //Pochette non utilisée
    madatabase.exec("DELETE FROM Pochette WHERE Id_Pochette !=1 AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Artiste ) AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Album)" );
    //Pochette non valide ( pas de chemin)
    madatabase.exec("DELETE FROM Pochette WHERE Chemin = ''");



}
void BDDSingleton::supprimerdossiersvides()
{
    QDir folder( ".\\Pochettes" );
    folder.setFilter( QDir::NoDotAndDotDot | QDir::AllDirs );
    foreach ( QFileInfo fileInfo, folder.entryInfoList() )
    {
        if ( fileInfo.isDir() )
        {
            QDir().rmdir( fileInfo.absoluteFilePath() );
        }
    }
}
