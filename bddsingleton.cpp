#include "bddsingleton.h"
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>

BDDSingleton BDDSingleton::s_singleton;

BDDSingleton::BDDSingleton():
    m_database()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setHostName("localhost");
    m_database.setDatabaseName("Musique.db");
    m_database.setUserName("root");
    m_database.setPassword("");

    //Si la BDD n'est pas ouverte,elle affiche une erreur
    if(!m_database.open())
    {
        qDebug() << "Impossible d'ouvrir la base de données !";
    }
    QStringList tables = m_database.tables();
    if (tables.count()==0)
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
QSqlDatabase &BDDSingleton::getDataBase()
{
    return m_database;
}
void BDDSingleton::creationBase()
{
    QStringList tables;
    QSqlQuery query;
    tables << "CREATE TABLE MP3 ('Id_MP3' INTEGER PRIMARY KEY,'Id_Titre' INTEGER, 'Chemin' VARCHAR(512),'Categorie' VARCHAR(255))";
    tables << "CREATE TABLE Artiste ('Id_Artiste' INTEGER PRIMARY KEY,'Artiste' VARCHAR(255),'Id_Pochette' INTEGER, 'NomSSAccents' VARCHAR(255))";
    tables << "CREATE TABLE Album ('Id_Album' INTEGER PRIMARY KEY,'Album' VARCHAR(255),'Id_Artiste' INTEGER,'Id_Pochette' INTEGER,'NomSSAccents' VARCHAR(255),'Annee' VARCHAR(255), 'Type' VARCHAR(255))";
    tables << "CREATE TABLE Titre ('Id_Titre' INTEGER PRIMARY KEY,'Titre' VARCHAR(255),'Id_Artiste' INTEGER,'Num_Piste' TINYINT,'Id_Pochette' INTEGER,'Id_Album' INTEGER,'TitreSSAccents' VARCHAR(255),'Duree' VARCHAR(255))";
    tables << "CREATE TABLE Phys ('Id_Phys' INTEGER PRIMARY KEY,'Id_Album' SMALLINT,'Categorie' VARCHAR(255),'CodeBarres' VARCHAR(255))";
    tables << "CREATE TABLE TitresPlaylist ('Id_Playlist' SMALLINT,'Id_Titre' SMALLINT, 'Num_Piste' TINYINT)";
    tables << "CREATE TABLE InfosPlaylist ('Id_Playlist' INTEGER PRIMARY KEY,'Nom' VARCHAR(255),'Type' VARCHAR(255),'NomAlbum' VARCHAR(255),'Id_Pochette' SMALLINT)";
    tables << "CREATE TABLE Pochette ('Id_Pochette' INTEGER PRIMARY KEY,'Chemin' VARCHAR(512))";
    tables << "INSERT INTO Pochette VALUES (01,'./pochettes/def.jpg')";
    tables << "INSERT INTO Artiste VALUES (01,'Divers','01','divers')";
    tables << "CREATE TABLE Configuration('Intitule' TEXT,'Valeur' TEXT)";
    tables << "INSERT INTO Configuration VALUES ('DossierParDef','F:/Albums')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserAlbums','Oui')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserCompil','Non')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserLives','Non')";
    for (int i=0;i<tables.size();i++)
    {
        query = madatabase.exec(tables[i]);
    }
}
