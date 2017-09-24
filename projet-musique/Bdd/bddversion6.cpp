#include "bddversion6.h"
#include "bddsingleton.h"
#include <QtSql>
#include <QFile>


BDDVersion6::BDDVersion6()
{

}
void BDDVersion6::ModificationBDD()
{
    //Création d'une nouvelle table "supports" et ajout de 4 supports dans la table
    madatabase.exec("CREATE TABLE Support ( 'Id_Support' INTEGER PRIMARY KEY, 'Support' VARCHAR( 255) ) " );

    madatabase.exec( "INSERT INTO Support VALUES ( 01,'Album' ) " );
    madatabase.exec( "INSERT INTO Support VALUES ( 02,'Compil' ) " );
    madatabase.exec( "INSERT INTO Support VALUES ( 03,'Single' ) " );
    madatabase.exec( "INSERT INTO Support VALUES ( 04,'MP3' ) " );

    //Types à remettre à jour dans la table Types
    madatabase.exec( "UPDATE Type SET Type='Associatif' WHERE Id_Type = 09" );
    madatabase.exec( "UPDATE Type SET Type='Inécouté' WHERE Id_Type = 03" );
    madatabase.exec( "UPDATE Type SET Type='Reprise' WHERE Id_Type = 10" );
    madatabase.exec( "UPDATE Type SET Type='Télé Réalité' WHERE Id_Type = 06" );

    //Dans MP3 et dans Phys, le champ Categorie se change en support
    //MP3
    madatabase.exec( "ALTER TABLE mp3 RENAME TO 'mp3old'" );
    madatabase.exec( "CREATE TABLE MP3 ( 'Id_MP3' INTEGER PRIMARY KEY,'Id_Relation' INTEGER, 'Chemin' VARCHAR ( 512 ),'Support' VARCHAR ( 255 ) )" );
    madatabase.exec( "INSERT INTO MP3 ( Id_Mp3, Id_Relation,Chemin,Support )                    SELECT Id_Mp3, Id_Relation, Chemin, Categorie FROM mp3old" );
    madatabase.exec( "DROP TABLE mp3old" );
    //PHYS
    madatabase.exec( "ALTER TABLE phys RENAME TO 'physold'" );
    madatabase.exec( "CREATE TABLE Phys ( 'Id_Phys' INTEGER PRIMARY KEY,'Id_Album' SMALLINT,'Support' VARCHAR ( 255 ) ,'CodeBarres' VARCHAR ( 255 ) , 'Commentaire' VARCHAR ( 512 ) ) " );
    madatabase.exec( "INSERT INTO Phys ( Id_Phys, Id_Album,Support, CodeBarres, Commentaire ) SELECT Id_Phys, Id_Album,Categorie, CodeBarres, Commentaire FROM physold " );
    madatabase.exec( "DROP TABLE physold" );

    //Type dans Album à remettre à jour
    //Phys
    for ( int i = 1; i < 3 ; i++ )
    {
        madatabase.exec( "UPDATE Album SET Type = "+ QString::number( i ) +" WHERE Id_Album IN ( SELECT B.Id_Album FROM Album B, Phys P WHERE B.Id_Album = P.Id_Album AND P.Support = "+ QString::number( i ) +" ) " );
    }
    madatabase.exec( "UPDATE Album SET Type = 1  WHERE Id_Album IN ( SELECT B.Id_Album FROM Album B, Phys P WHERE B.Id_Album = P.Id_Album AND P.Support = 3 ) " );

    //MP3
    for ( int i = 1; i < 10 ; i++ )
    {
        madatabase.exec( "UPDATE Album SET Type = "+ QString::number( i ) +"   WHERE Id_Album IN ( SELECT B.Id_Album FROM Album B, Mp3 M, Relations R   WHERE B.Id_Album = R.Id_Album AND M.Id_Relation = R.Id_Relation  AND M.Support = "+ QString::number( i ) +" ) " );
    }
    madatabase.exec( "UPDATE Album SET Type = 3  WHERE Id_Album IN ( SELECT B.Id_Album FROM Album B, Mp3 M, Relations R  WHERE B.Id_Album = R.Id_Album AND M.Id_Relation = R.Id_Relation  AND M.Support = 11 ) " );

    madatabase.exec( "UPDATE Album SET Type = 4  WHERE Id_Album IN ( SELECT B.Id_Album FROM Album B, Mp3 M, Relations R  WHERE B.Id_Album = R.Id_Album AND M.Id_Relation = R.Id_Relation  AND M.Support = 9 ) " );

    //Support dans MP3 & Phys à remettre à jour
    //MP3
    madatabase.exec( "UPDATE MP3 SET Support = 4 ");
    //Phys
    //Pas besoin de remettre à jour, c'est déjà le cas

    //Type 11 supprimé
    madatabase.exec("DELETE FROM Type WHERE Id_Type=11");


    //On change la version
    madatabase.exec("UPDATE Configuration SET Valeur='6' WHERE Intitule= 'Version' ");

}

void BDDVersion6::ModificationCategories()
{
    madatabase.exec( "UPDATE Album SET Type = 8  WHERE Id_Album IN (SELECT DISTINCT (Id_Album) FROM Relations R, Artiste A  WHERE A.Artiste_Formate = 'classique'            AND R.Id_Artiste = A.Id_Artiste " );


}

