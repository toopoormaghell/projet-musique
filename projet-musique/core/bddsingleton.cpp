#include "bddsingleton.h"
#include <QStringList>
#include <qdebug.h>
#include <QtSql>
#include <QDir>
#include <QFileInfo>
#include "bddgestionmp3.h"
#include "bddverification.h"
#include "util.h"

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
    tables << "CREATE TABLE Album ('Id_Album' INTEGER PRIMARY KEY,'Album' VARCHAR(255),'Id_Pochette' INTEGER,'Album_Formate' VARCHAR(255),'Annee' VARCHAR(255), 'Type' VARCHAR(255), 'Id_Artiste' INTEGER)";
    tables << "CREATE TABLE Titre ('Id_Titre' INTEGER PRIMARY KEY,'Titre' VARCHAR(255),'Titre_Formate' VARCHAR(255))";
    tables << "CREATE TABLE Phys ('Id_Phys' INTEGER PRIMARY KEY,'Id_Album' SMALLINT,'Categorie' VARCHAR(255),'CodeBarres' VARCHAR(255), 'Commentaire' VARCHAR(512))";
    tables << "CREATE TABLE Pochette ('Id_Pochette' INTEGER PRIMARY KEY,'Chemin' VARCHAR(512))";
    tables << "CREATE TABLE Type ('Id_Type' INTEGER PRIMARY KEY,'Type' VARCHAR(255))";
    tables << "INSERT INTO Pochette VALUES (01,'./pochettes/def.jpg')";
    tables << "INSERT INTO Artiste VALUES (01,'Artistes Divers','01','artistesdivers')";
    tables << "CREATE TABLE Relations('Id_Relation' INTEGER PRIMARY KEY,'Id_Titre' INTEGER,'Id_Album' INTEGER,'Id_Artiste' INTEGER,'Num_Piste' TINYINT,'Duree' VARCHAR(255))";
    tables << "CREATE TABLE Configuration('Intitule' TEXT,'Valeur' TEXT)";
    tables << "INSERT INTO Configuration VALUES ('DossierParDef','F:/Albums')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserAlbums','Oui')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserCompil','Oui')";
    tables << "INSERT INTO Configuration VALUES ('ActualiserLives','Non')";
    tables << "INSERT INTO Configuration VALUES ('Version', '3')";
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
    tables <<  "MP3" << "Artiste" << "Album" << "Titre" << "Phys" << "Pochette" << "Relations"  << "Configuration";
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
    /*----- POCHETTE -----*/
    //Non valide ( le chemin n'existe pas dans le système des fichiers )
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
    //Non utilisée
    madatabase.exec("DELETE FROM Pochette WHERE Id_Pochette !=1 AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Artiste ) AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Album)" );
    //Vide
    madatabase.exec("DELETE FROM Pochette WHERE Chemin = ''");
    /*----- RELATION -----*/
    //Vide
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album ='' OR Id_Artiste = '' OR Id_Titre = '' OR Id_Relation = '' ");
    //Non utilisé
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Phys) AND Id_Relation NOT IN ( SELECT DISTINCT Id_Relation FROM MP3) " );
    //Non valide
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album NOT IN (SELECT DISTINCT Id_Album FROM Album) OR Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste) OR Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Titre) OR Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette From Pochette)" );
    /*----- ALBUM -----*/
    //Vide
    madatabase.exec( "DELETE FROM Album WHERE Album = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM Album WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Relations ) " );
    //Non valide
    madatabase.exec( "UPDATE Album SET Id_Pochette = '1' WHERE Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Pochette ) " );
    madatabase.exec( "UPDATE Album SET Id_Artiste = '1' WHERE Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste ) " );
    queryStr = "SELECT Album, Id_Album, Album_Formate FROM Album";
    query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString nom = rec.value( "Album" ).toString();
        QString Id_Alb = rec.value( "Id_Album").toString();
        QString Alb = rec.value("Album_Formate").toString();
        FormaterEntiteBDD ( nom );
        if ( nom != Alb)
            madatabase.exec( "UPDATE Album SET Album_Formate = '"+ nom +"' WHERE Id_Album = "+ Id_Alb +" " );
    }
    /*----- ARTISTE -----*/
    //Vide
    madatabase.exec( "DELETE FROM Artiste WHERE Artiste = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM Artiste WHERE Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Relations ) " );
    //Non valide
    madatabase.exec( "UPDATE Artiste SET Id_Pochette = '1' WHERE Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Pochette ) " );
    queryStr = "SELECT Artiste, Id_Artiste, Artiste_Formate FROM Artiste";
    query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString nom = rec.value( "Artiste" ).toString();
        QString Id_Art = rec.value( "Id_Artiste").toString();
        QString Art = rec.value("Artiste_Formate").toString();
        FormaterEntiteBDD ( nom );
        if ( nom != Art)
            madatabase.exec( "UPDATE Artiste SET Artiste_Formate = '"+ nom +"' WHERE Id_Artiste = "+ Id_Art +" " );
    }
    /*----- TITRE -----*/
    //Vide
    madatabase.exec( "DELETE FROM Titre WHERE Titre = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM Titre WHERE Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Relations ) " );
    //Non valide
    madatabase.exec( "UPDATE Titre SET Num_Piste = '1' WHERE Num_Piste = '' " );
    queryStr = "SELECT Titre, Id_Titre, Titre_Formate FROM Titre";
    query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString nom = rec.value( "Titre" ).toString();
        QString Id_Titre = rec.value( "Id_Titre").toString();
        QString Titre_Formate = rec.value("Titre_Formate").toString();
        FormaterEntiteBDD ( nom );
        if ( nom != Titre_Formate )
            madatabase.exec( "UPDATE Titre SET Titre_Formate = '"+ nom +"' WHERE Id_Titre = "+ Id_Titre +" " );
    }

    /*----- MP3 -----*/
    //Vide
    madatabase.exec( "DELETE FROM MP3 WHERE Chemin = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM MP3 WHERE Id_Relation NOT IN (SELECT DISTINCT Id_Relation FROM Relations)" );
    //Non valide
    madatabase.exec( "UPDATE MP3 SET Categorie = '1' WHERE Categorie NOT IN ( SELECT DISTINCT Id_Type FROM Type ) " );
    /*----- PHYS -----*/
    //Vide
    madatabase.exec( "DELETE FROM Phys WHERE CodeBarres = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM Phys WHERE Id_Album NOT IN (SELECT  Id_Album FROM Relations)" );
    //Non valide
    madatabase.exec( "UPDATE Phys SET Categorie = '1' WHERE Categorie NOT IN ( SELECT DISTINCT Id_Type FROM Type ) " );

    //BDDGestionMp3::ReconstruireListeCategorie();
    //temp.ReconstruireListeCategorie();

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
    switch (version)
    {
    case 0:  madatabase.exec("INSERT INTO Configuration VALUES ('Version', '1')");
    case 1 : version2();
    case 2  : version3();
    case 3: version4();
    case 4: version5();break;
    default: break;
    }
}
void BDDSingleton::version2()
{
    //On ajoute une colonne dans la table Album
    madatabase.exec("ALTER TABLE Album ADD Id_Artiste INTEGER");
    madatabase.exec("UPDATE Album SET Id_Artiste='1' WHERE Type='2' ");
    //On crée une liste d'id d'albums et on remplit la liste
    QString queryStr = "SELECT DISTINCT Id_Album, Id_Artiste FROM Relations R ";
    QSqlQuery query = madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        madatabase.exec("UPDATE Album SET Id_Artiste='"+ rec.value("Id_Artiste").toString() +"' WHERE Type!='2' AND Id_Album='" + rec.value("Id_Album").toString() + "'");
    }
    //On change la version
    madatabase.exec("UPDATE Configuration SET Valeur='2' WHERE Intitule= 'Version' ");
}
void BDDSingleton::version3()
{
    //On ajoute une colonne commentaire dans la table physique
    madatabase.exec("ALTER TABLE Phys ADD Commentaire VARCHAR(512)");
    madatabase.exec("UPDATE Phys SET Commentaire='' ");

    //On change la version
    madatabase.exec("UPDATE Configuration SET Valeur='3' WHERE Intitule= 'Version' ");
}
void BDDSingleton::version4()
{
    //On ajoute un champ dans la table Type
    madatabase.exec("INSERT INTO Type VALUES( 11,'Inecoutes')" );

    //On change la version
    madatabase.exec("UPDATE Configuration SET Valeur='4' WHERE Intitule= 'Version' ");
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
void BDDSingleton::version5()
{

    madatabase.exec("DROP TABLE ErreurPochettes");

    //Dans la table Relations, on ajoute maintenant la durée, le num_piste, si c'est un MP3 ou si c'est un Phys
    madatabase.exec("ALTER TABLE Relations ADD Num_Piste TINYINT");
    madatabase.exec("ALTER TABLE Relations ADD Duree VARCHAR(255)"); madatabase.exec("ALTER TABLE Relations ADD MP3 TINYINT DEFAULT '0'");
    madatabase.exec("ALTER TABLE Relations ADD Phys TINYINT DEFAULT '0'");

    //On remplit la durée et le num_pisteqt
    madatabase.exec("UPDATE Relations SET Duree = (SELECT Duree FROM Titre T WHERE Relations.Id_Titre = T.Id_Titre)");
    madatabase.exec("UPDATE Relations SET Num_Piste = (SELECT Num_Piste FROM Titre T WHERE Relations.Id_Titre = T.Id_Titre)");

    //On dit si c'est un MP3
    madatabase.exec("UPDATE Relations SET MP3=1  WHERE  Id_Relation = (SELECT M.Id_Relation FROM MP3 M WHERE Relations.Id_Relation = M.Id_Relation)");
    //On dit si c'est un Phys
    madatabase.exec("UPDATE Relations SET Phys=1  WHERE Id_Album = (SELECT P.Id_Album FROM Phys P WHERE Relations.Id_Album = P.Id_Album)");

    //On supprime dans la table Titre la durée et le num_piste
    madatabase.exec("CREATE TABLE Titre_Nouveau ('Id_Titre' INTEGER PRIMARY KEY,'Titre' VARCHAR(255),'Titre_Formate' VARCHAR(255))");

    madatabase.exec("INSERT into Titre_Nouveau ( 'Id_Titre','Titre','Titre_Formate') SELECT Id_Titre,Titre,Titre_Formate FROM Titre T");
    madatabase.exec("DROP Table Titre");
    madatabase.exec("ALTER TABLE Titre_Nouveau RENAME TO Titre");

    //On supprime les 2 tables de Playlist et celle des pochettes erreurs
    madatabase.exec("DROP Table InfosPlaylist");
    madatabase.exec("DROP TABLE TitresPlaylist");
    madatabase.exec("DROP TABLE ErreurPochettes");

    BDDVersion5 * verif= new BDDVersion5;

    //On change la version
 //   madatabase.exec("UPDATE Configuration SET Valeur='5' WHERE Intitule= 'Version' ");

}
