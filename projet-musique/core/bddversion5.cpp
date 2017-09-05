#include "bddversion5.h"
#include <QStringList>
#include <qdebug.h>
#include <QtSql>
#include <QDir>
#include <QFileInfo>
#include "util.h"
#include "bddsingleton.h"

BDDVersion5::BDDVersion5()
{


}
void BDDVersion5::passageversion5()
{
    VirguleArtistes();
    ReformatageCompletEntites();

    CompilsPhysiqueMp3();
    ChangerArtisteDansCompilAlbum();
    DoublonsTitresEnlever();
    SupprimerDoublonsAlbum();
    SupprimerDoublonsArtiste();
}

void BDDVersion5::ModificationBDD()
{
    madatabase.exec("DROP TABLE ErreurPochettes");

    //Dans la table Relations, on ajoute maintenant la durée, le num_piste, si c'est un MP3 ou si c'est un Phys
    madatabase.exec("ALTER TABLE Relations ADD Num_Piste TINYINT");
    madatabase.exec("ALTER TABLE Relations ADD Duree VARCHAR(255)");
    madatabase.exec("ALTER TABLE Relations ADD MP3 TINYINT DEFAULT '0'");
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
}

void BDDVersion5::VirguleArtistes()
{
    qDebug() << "VirguleArtistes";
    //On enlève les virgules des noms d'artistes
    QList<int> artistes;
    QSqlQuery query =  madatabase.exec("SELECT Id_Artiste FROM Artiste WHERE Artiste LIKE '%,%' ");
    while (query.next() ) {
        QSqlRecord rec=query.record();
        artistes << rec.value("Id_Artiste").toInt();
    }

    //On enlève la partie à laquelle on doit enlever une virgule
    madatabase.exec("UPDATE Artiste SET Artiste = SUBSTR(Artiste,0, instr(Artiste,',' ) ) WHERE Artiste LIKE '%,%'");

}
void BDDVersion5::CompilsPhysiqueMp3()
{
    qDebug() << "CompilsPhysiqueMp3";
    //Pour les compils physiques, deux choses à faire:
    //Première chose, on fait en sorte que les titres existants dans la compil et qui existent aussi en MP3 soient bien marqués MP3 dans la relation avec la compil:
    madatabase.exec("UPDATE Relations SET MP3 = 1 WHERE Id_Album IN ( SELECT DISTINCT P.Id_Album FROM Phys P WHERE P.Categorie='2' ) AND Id_Titre =( SELECT DISTINCT Id_Titre FROM Relations R WHERE R.MP3=1 AND Relations.Id_Artiste = R.Id_Artiste)");
    //Deuxième chose, les mêmes titres doivent être marqués Phys dans la relation avec le mp3:
    madatabase.exec("UPDATE Relations SET Phys = 1  WHERE  Id_Titre = ( SELECT DISTINCT Id_Titre FROM Relations R WHERE R.Phys=1 AND Relations.Id_Artiste = R.Id_Artiste)");

}
void BDDVersion5::SupprimerDoublonsArtiste()
{
    qDebug() << "SupprimerDoublonsArtiste";
    //Le but, c'est d'enlever tous les artistes qui sont en double
    //Première requete: on récupère les artistes et un Id_Artiste des doubles
    QString queryStr = "SELECT Id_Artiste, Artiste_Formate FROM Artiste GROUP BY Artiste_Formate HAVING COUNT(*) > 1";
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString artiste_formate = rec.value( "Artiste_Formate" ).toString();
        QString Id_Artiste = rec.value( "Id_Artiste" ).toString();

        //On récupère maintenant l'id des titres en double
        queryStr = "SELECT Id_Artiste FROM Artiste WHERE Artiste_Formate = '"+ artiste_formate +"' And Id_Artiste != " + Id_Artiste + " ORDER BY Artiste_Formate";

        QSqlQuery  query2 = madatabase.exec(queryStr);

        while (query2.next() ) {
            QSqlRecord rec2=query2.record();
            QString Id_double = rec2.value( "Id_Artiste" ).toString();
            madatabase.exec("UPDATE Relations SET Id_Artiste = " + Id_Artiste + " WHERE Id_Artiste = " + Id_double + "" );
            madatabase.exec("UPDATE Album SET Id_Artiste = " + Id_Artiste + " WHERE Id_Artiste = " + Id_double + "" );
            madatabase.exec( "DELETE FROM Artiste WHERE Id_Artiste = " + Id_double + "" );
        }
    }

    //Deuxième période : on vérifie si il y a pas eu des soucis lors d'échanges dans les noms
    queryStr = "SELECT Id_Artiste, Artiste FROM Artiste";
    query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString ArtisteASupprimer = rec.value("Id_Artiste").toString();
        QString Artiste = rec.value("Artiste").toString();
        QString ArtisteEchange = EchangerArtiste(Artiste);
        FormaterEntiteBDD(ArtisteEchange);
        FormaterEntiteBDD(Artiste);
        madatabase.exec("UPDATE Artiste SET Artiste_Formate ='" + Artiste + "' WHERE Id_Artiste= " + ArtisteASupprimer + "" );
        queryStr = " SELECT Id_Artiste FROM Artiste WHERE Artiste_Formate ='" + ArtisteEchange + "' AND Id_Artiste !='"+ ArtisteASupprimer+"'";
        QSqlQuery  query2 = madatabase.exec(queryStr);

        while (query2.next() ) {
            QSqlRecord rec2=query2.record();
            QString Id_double = rec2.value( "Id_Artiste" ).toString();

            madatabase.exec("UPDATE Relations SET Id_Artiste = " + Id_double + " WHERE Id_Artiste = " + ArtisteASupprimer + "" );
            madatabase.exec("UPDATE Album SET Id_Artiste = " + Id_double + " WHERE Id_Artiste = " + ArtisteASupprimer + "" );
            madatabase.exec("DELETE FROM Artiste WHERE Id_Artiste = " + ArtisteASupprimer + "" );
        }
    }

}
void BDDVersion5::SupprimerDoublonsAlbum()
{
    qDebug() << "SupprimerDoublonsAlbum";

    //Le but, c'est d'enlever tous les artistes qui sont en double
    //Première requete: on récupère les artistes et un Id_Artiste des doubles
    QString queryStr = "SELECT Id_Album, Album_Formate, Id_Artiste, Annee FROM Album GROUP BY Album_Formate, Id_Artiste HAVING COUNT(*) > 1";
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString album_formate = rec.value( "Album_Formate" ).toString();
        QString Id_Album = rec.value( "Id_Album" ).toString();
        QString Annee = rec.value( "Annee" ).toString();

        //On récupère maintenant l'id des titres en double
        queryStr = "SELECT Id_Album FROM Album WHERE Album_Formate = '"+ album_formate +"' And Id_Album != " + Id_Album + " AND Album_Formate !='bestof' AND  Annee == " + Annee + " ORDER BY Album_Formate";

        QSqlQuery  query2 = madatabase.exec(queryStr);

        while (query2.next() ) {
            QSqlRecord rec2=query2.record();
            QString Id_double = rec2.value( "Id_Album" ).toString();
            madatabase.exec("UPDATE Relations SET Id_Album = " + Id_Album + " WHERE Id_Album = " + Id_double + "" );
            madatabase.exec( "DELETE FROM Album WHERE Id_Album = " + Id_double + "" );
        }
    }

}
void BDDVersion5::DoublonsTitresEnlever()
{
    qDebug() << "DoublonsTitresEnlever";
    //Le but, c'est d'enlever tous les titres qui sont en double
    //Première requete: on récupère les titres et un Id_Titre des doubles
    QString queryStr = "SELECT Id_Titre, Titre_Formate FROM Titre GROUP BY Titre_Formate HAVING COUNT(*) > 1";
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString titre_formate = rec.value( "Titre_Formate" ).toString();
        QString Id_Titre = rec.value( "Id_Titre" ).toString();

        //On récupère maintenant l'id des titres en double
        queryStr = "SELECT Id_Titre FROM Titre WHERE Titre_Formate = '"+ titre_formate +"' And Id_Titre != " + Id_Titre + " ORDER BY Titre_Formate";

        QSqlQuery  query2 = madatabase.exec(queryStr);

        while (query2.next() ) {
            QSqlRecord rec2=query2.record();
            QString Id_double = rec2.value( "Id_Titre" ).toString();

            madatabase.exec("UPDATE Relations SET Id_Titre = " + Id_Titre + " WHERE Id_Titre = " + Id_double + "" );
            madatabase.exec( "DELETE FROM Titre WHERE Id_Titre = " + Id_double + "" );
        }
    }
}
void BDDVersion5::ReformatageCompletEntites()
{
    qDebug() << " Reformatage en cours...";
    //On reformate absolument tous les entités
    //On commence par récupérer les données des albums
    QString queryStr = " SELECT Id_Album AS 'Id', Album AS 'Entite' FROM Album";
    ExecutionRequeteFormate(queryStr,1);
    //On fait ensuite les artistes
    queryStr = " SELECT Id_Artiste AS 'Id', Artiste AS 'Entite' FROM Artiste";
    ExecutionRequeteFormate(queryStr,2);
    //On finit par les titres
    queryStr = " SELECT Id_Titre AS 'Id', Titre AS 'Entite' FROM Titre";
    ExecutionRequeteFormate(queryStr,3);

}
void BDDVersion5::ExecutionRequeteFormate(QString queryStr, int Categorie)
{
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString Entite= rec.value("Entite").toString();
        QString Id_Entite = rec.value("Id").toString();
        FormaterEntiteBDD(Entite);
        Reformatage(Entite,Id_Entite,Categorie);
    }
}

void BDDVersion5::ExecutionRequeteMajuscules(QString queryStr, int Categorie)
{
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString Entite= rec.value("Entite").toString();
        QString Id_Entite = rec.value("Id").toString();
   //     EnleverAccents ( Entite );
        MajusuculeAChaqueMot(Entite);
        Majuscules(Entite,Id_Entite,Categorie);
    }
}

void BDDVersion5::Reformatage(QString Entite,QString Id_Entite, int Categorie)
{
    switch ( Categorie )
    {
    case 1: madatabase.exec("UPDATE Album SET Album_Formate='"+ Entite +"' WHERE Id_Album='"+ Id_Entite +"'");break;
    case 2: madatabase.exec("UPDATE Artiste SET Artiste_Formate='"+ Entite +"' WHERE Id_Artiste='"+ Id_Entite +"'");break;
    case 3: madatabase.exec("UPDATE Titre SET Titre_Formate='"+ Entite +"' WHERE Id_Titre='"+ Id_Entite +"'");break;
    default: break;
    }

}

void BDDVersion5::Majuscules(QString Entite, QString Id_Entite, int Categorie)
{
    switch ( Categorie )
    {
    case 1: madatabase.exec("UPDATE Album SET Album='"+ Entite +"' WHERE Id_Album='"+ Id_Entite +"'");break;
    case 2: madatabase.exec("UPDATE Artiste SET Artiste='"+ Entite +"' WHERE Id_Artiste='"+ Id_Entite +"'");break;
    case 3: madatabase.exec("UPDATE Titre SET Titre='"+ Entite +"' WHERE Id_Titre='"+ Id_Entite +"'");break;
    default:  break;
    }
}
void BDDVersion5::ChangerArtisteDansCompilAlbum()
{
    qDebug() << "ChangerArtisteDansCompilAlbum";
    //Première chose: on marque bien les albums physiques en compil
    madatabase.exec("UPDATE Album SET Type = 2 WHERE Id_Album IN ( SELECT Id_Album FROM Phys WHERE Categorie = 2 ) ");

    //Deuxième partie: On change les artistes des albums marqués compil
    madatabase.exec("UPDATE Album SET Id_Artiste= 1 WHERE Type = 2");

}
void BDDVersion5::ChangerCategorie()
{
    madatabase.exec("UPDATE Phys SET Categorie = '13' WHERE Categorie ='2'");
    madatabase.exec("UPDATE MP3 SET Categorie = '12' WHERE Categorie ='1'");
}
void BDDVersion5::MajusculesCompletEntites()
{
    qDebug() << " Majuscules en cours...";
    //On reformate absolument tous les entités
    //On commence par récupérer les données des albums
    QString queryStr = " SELECT Id_Album AS 'Id', Album AS 'Entite' FROM Album";
    ExecutionRequeteMajuscules(queryStr,1);
    //On fait ensuite les artistes
    queryStr = " SELECT Id_Artiste AS 'Id', Artiste AS 'Entite' FROM Artiste";
    ExecutionRequeteMajuscules(queryStr,2);
    //On finit par les titres
    queryStr = " SELECT Id_Titre AS 'Id', Titre AS 'Entite' FROM Titre";
    ExecutionRequeteMajuscules(queryStr,3);
}
