#include "bddsingleton.h"
#include <QStringList>
#include <QtSql>
#include <QDir>
#include <QFileInfo>

#include <util.h>
#include "outilsbdd.h"
#include "changementversion.h"

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

QSqlQuery BDDSingleton::exec(const QString& query) const
{
    return m_database.exec(query);
}

void BDDSingleton::creationBase()
{
    QStringList tables;
    QSqlQuery query;
    tables << "CREATE TABLE MP3 ('Id_MP3' INTEGER PRIMARY KEY,'Id_Relation' INTEGER, 'Chemin' VARCHAR(512),'Support' VARCHAR(255))";
    tables << "CREATE TABLE Artiste ('Id_Artiste' INTEGER PRIMARY KEY,'Artiste' VARCHAR(255),'Id_Pochette' INTEGER, 'Artiste_Formate' VARCHAR(255))";
    tables << "CREATE TABLE Album ('Id_Album' INTEGER PRIMARY KEY,'Album' VARCHAR(255),'Id_Pochette' INTEGER,'Album_Formate' VARCHAR(255),'Annee' VARCHAR(255), 'Type' VARCHAR(255), 'Id_Artiste' INTEGER)";
    tables << "CREATE TABLE Titre ('Id_Titre' INTEGER PRIMARY KEY,'Titre' VARCHAR(255),'Titre_Formate' VARCHAR(255))";
    tables << "CREATE TABLE Phys ('Id_Phys' INTEGER PRIMARY KEY,'Id_Album' SMALLINT,'Support' VARCHAR(255),'CodeBarres' VARCHAR(255), 'Commentaire' VARCHAR(512))";
    tables << "CREATE TABLE Pochette ('Id_Pochette' INTEGER PRIMARY KEY,'Chemin' VARCHAR(512))";
    tables << "CREATE TABLE Type ('Id_Type' INTEGER PRIMARY KEY,'Type' VARCHAR(255))";
    tables << "CREATE TABLE Support ('Id_Support' INTEGER PRIMARY KEY,'Support' VARCHAR(255))";
    tables << "INSERT INTO Pochette VALUES (01,'./pochettes/def.jpg')";
    tables << "INSERT INTO Artiste VALUES (01,'Artistes Divers','01','artistesdivers')";
    tables << "CREATE TABLE Relations('Id_Relation' INTEGER PRIMARY KEY,'Id_Titre' INTEGER,'Id_Album' INTEGER,'Id_Artiste' INTEGER,'Num_Piste' TINYINT,'Duree' VARCHAR(255),'MP3' INTEGER,'Phys' INTEGER)";
    tables << "CREATE TABLE Configuration('Intitule' TEXT,'Valeur' TEXT)";
    tables << "INSERT INTO Configuration VALUES ('DossierParDef','F:/Albums')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserAlbums','Oui')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserCompil','Oui')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserLives','Non')";
    tables << "INSERT INTO Configuration VALUES ('Version', '3')";
    tables << "INSERT INTO Type VALUES(01,'Album')";
    tables << "INSERT INTO Type VALUES(02,'Compil')";
    tables << "INSERT INTO Type VALUES(03,'Single')";
    tables << "INSERT INTO Type VALUES(04,'Live')";
    tables << "INSERT INTO Type VALUES(05,'BOF')";
    tables << "INSERT INTO Type VALUES(06,'Musicale')";
    tables << "INSERT INTO Type VALUES(07,'Télé Réalité')";
    tables << "INSERT INTO Type VALUES(08,'New Age')";
    tables << "INSERT INTO Type VALUES(09,'Classique')";
    tables << "INSERT INTO Type VALUES(10,'Associatif')";
    tables << "INSERT INTO Type VALUES(11,'Reprise')";

    tables << "INSERT INTO Support VALUES(01,'Album')";
    tables << "INSERT INTO Support VALUES(02,'Compil')";
    tables << "INSERT INTO Support VALUES(03,'Single')";
    tables << "INSERT INTO Support VALUES(04,'Live')";

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
    tables <<  "MP3" << "Artiste" << "Album" << "Titre" << "Phys" << "Pochette" << "Relations"  << "Configuration";
    int compt = 0;
    while ( compt < tables.size() )
    {
        query = madatabase.exec( "DROP Table " + tables[compt] );
        compt++;
    }

    //Vidage sur le DD du dossier Pochettes
    QString chemin = ".\\Pochettes";
    m_outils->removeDir( chemin, false );

    creationBase();
}

void BDDSingleton::changementversion()
{
    QString queryStr = "SELECT Valeur FROM Configuration WHERE Intitule= 'Version' ";
    QSqlQuery query = madatabase.exec(queryStr);
    int version=0;
    //selon la version, certaines requêtes sont lancées
    query.next();
    version = query.record().value("Valeur").toInt();
    query.finish();
    ChangementVersion* temp = new ChangementVersion;
    switch ( version )
    {
    case 4:  temp->Version();break;
    case 1:  temp->Version2();break;
    default:break;
    }

}


