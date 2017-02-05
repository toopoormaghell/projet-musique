#include "bddverification.h"
#include <QStringList>
#include <qdebug.h>
#include <QtSql>
#include <QDir>
#include <QFileInfo>
#include "util.h"
#include "bddsingleton.h"

BDDVerification::BDDVerification()
{

}
void BDDVerification::VirguleArtistes()
{
    //Première partie :
    //On Récupère les ids correspondants
    QList<int> artistes;
    QSqlQuery query =  madatabase.exec("SELECT Id_Artiste FROM Artiste WHERE Artiste LIKE '%,%' ");
    while (query.next() ) {
        QSqlRecord rec=query.record();
        artistes << rec.value("Id_Artiste").toInt();
    }

    //On enlève la partie à laquelle on doit enlever une virgule
    madatabase.exec("UPDATE Artiste SET Artiste = SUBSTR(Artiste,0, instr(Artiste,',' ) ) WHERE Artiste LIKE '%,%'");

    //On modifie l'artiste formate
    for ( int i = 0; i<artistes.count(); i++ )
    {
        //On récupère le nom de l'artiste à formater
        query = madatabase.exec("SELECT Artiste FROM Artiste WHERE Id_Artiste ='" + QString::number( artistes[i] ) + "'");
        while (query.next() ) {
            QSqlRecord rec=query.record();
            QString art = rec.value("Artiste").toString();
            FormaterEntiteBDD(art);
            madatabase.exec("UPDATE Artiste SET Artiste_Formate = '"+ art + "' WHERE Id_Artiste ='"+ QString::number( artistes[i] ) +"'");
        }

    }
    SupprimerDoublonsArtiste();
}
void BDDVerification::CompilsPhysiqueMp3()
{
    //Pour les compils physiques, deux choses à faire:
    //Première chose, on fait en sorte que les titres existants dans la compil et qui existent aussi en MP3 soient bien marqués MP3 dans la relation avec la compil:
    madatabase.exec("UPDATE Relations SET MP3 = 1 WHERE Id_Album IN ( SELECT DISTINCT P.Id_Album FROM Phys P WHERE P.Categorie='2' ) AND Id_Titre =( SELECT DISTINCT Id_Titre FROM Relations R WHERE R.MP3=1 AND Relations.Id_Artiste = R.Id_Artiste)");
    //Deuxième chose, les mêmes titres doivent être marqués Phys dans la relation avec le mp3:
    madatabase.exec("UPDATE Relations SET Phys = 1  WHERE  Id_Titre = ( SELECT DISTINCT Id_Titre FROM Relations R WHERE R.Phys=1 AND Relations.Id_Artiste = R.Id_Artiste)");

}
void BDDVerification::SupprimerDoublonsArtiste()
{
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
            madatabase.exec("DELETE FROM Artiste WHERE Id_Artiste = " + ArtisteASupprimer + "" );
        }
    }

}
