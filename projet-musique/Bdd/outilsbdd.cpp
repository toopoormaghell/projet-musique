#include "outilsbdd.h"
#include <QStringList>
#include <qdebug.h>
#include <QtSql>
#include <QDir>
#include <QFileInfo>
#include "util.h"
#include "bddsingleton.h"


OutilsBDD::OutilsBDD(QWidget* parent)
{
    Q_UNUSED ( parent);
}
void OutilsBDD::VirguleArtistes()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage( "VirguleArtistes" );
    emit EcrireMessage("----------------");
    emit EcrireMessage( "Artistes Concernés :" );
    //On enlève les virgules des noms d'artistes
    QList<int> artistes;
    QSqlQuery query =  madatabase.exec("SELECT Id_Artiste, Artiste FROM Artiste WHERE Artiste LIKE '%,%' ");
    while (query.next() ) {
        QSqlRecord rec=query.record();
        artistes << rec.value("Id_Artiste").toInt();
        emit EcrireMessage( rec.value("Artiste").toString() );
    }

    //On enlève la partie à laquelle on doit enlever une virgule
    madatabase.exec("UPDATE Artiste SET Artiste = SUBSTR(Artiste,0, instr(Artiste,',' ) ) WHERE Artiste LIKE '%,%'");

}
void OutilsBDD::titresphysetmp3()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage( "Titres Phys Mp3" );
    emit EcrireMessage("----------------");
    //On prend tous les MP3, on vérifie que toutes les relations avec le même titre et le même artiste soient notés MP3
    QString queryStr = "SELECT Id_Titre, Id_Artiste FROM Relations R, MP3 M WHERE M.Id_Relation = R.Id_Relation";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();

        madatabase.exec("UPDATE Relations SET MP3 = 1 WHERE Id_Titre ='"+rec.value("Id_Titre").toString()+"' AND Id_Artiste = '"+rec.value( "Id_Artiste" ).toString() +"' " );

    }

    //On prend tous les Phys, on vérifie que toutes les relations avec le même titre et le même artiste soient notés Phys
    queryStr = "SELECT Id_Titre, Id_Artiste FROM Relations R, Phys P WHERE P.Id_Album = R.Id_Album";
    query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();

        madatabase.exec("UPDATE Relations SET Phys = 1 WHERE Id_Titre ='"+rec.value("Id_Titre").toString()+"' AND Id_Artiste = '"+rec.value( "Id_Artiste" ).toString() +"' " );

    }


}
void OutilsBDD::SupprimerDoublonsArtiste()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage( "Suppression des doublons des artistes:" );
    emit EcrireMessage("----------------");
    emit EcrireMessage( "Artistes concernés:" );
    //Le but, c'est d'enlever tous les artistes qui sont en double
    //Première requete: on récupère les artistes et un Id_Artiste des doubles
    QString queryStr = "SELECT Id_Artiste, Artiste_Formate FROM Artiste GROUP BY Artiste_Formate HAVING COUNT(*) > 1";
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString artiste_formate = rec.value( "Artiste_Formate" ).toString();
        QString Id_Artiste = rec.value( "Id_Artiste" ).toString();
        emit EcrireMessage( artiste_formate );

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
void OutilsBDD::SupprimerDoublonsAlbum()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Suppression des doublons dans les albums");
    emit EcrireMessage("----------------");
    emit EcrireMessage("albums concernés");
    //Le but, c'est d'enlever tous les artistes qui sont en double
    //Première requete: on récupère les artistes et un Id_Artiste des doubles
    QString queryStr = "SELECT Id_Album, Album_Formate, Id_Artiste, Annee FROM Album GROUP BY Album_Formate, Id_Artiste HAVING COUNT(*) > 1";
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString album_formate = rec.value( "Album_Formate" ).toString();
        QString Id_Album = rec.value( "Id_Album" ).toString();
        QString Annee = rec.value( "Annee" ).toString();

        emit EcrireMessage( album_formate );

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
void OutilsBDD::SupprimerDoublonsTitre()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage( "Suppression des doublons dans les titres..");
    emit EcrireMessage("----------------");
    emit EcrireMessage( "Titres concernés");
    //Le but, c'est d'enlever tous les titres qui sont en double
    //Première requete: on récupère les titres et un Id_Titre des doubles

    QString queryStr = "SELECT Id_Titre, Titre_Formate, Titre FROM Titre GROUP BY Titre_Formate HAVING COUNT(*) > 1";
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString titre_formate = rec.value( "Titre_Formate" ).toString();
        QString Id_Titre = rec.value( "Id_Titre" ).toString();

        emit EcrireMessage( rec.value("Titre").toString()+"");

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
void OutilsBDD::ReformatageCompletEntites()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Reformatage en cours de toutes les données de la bdd");
    emit EcrireMessage("----------------");

    //On reformate absolument tous les entités
    //On commence par récupérer les données des albums
    QString queryStr = " SELECT Id_Album AS 'Id', Album AS 'Entite', Album_Formate AS 'Entite_Formatee' FROM Album";
    ExecutionRequeteFormate(queryStr,1);
    //On fait ensuite les artistes
    queryStr = " SELECT Id_Artiste AS 'Id', Artiste AS 'Entite', Artiste_Formate AS 'Entite_Formatee' FROM Artiste";
    ExecutionRequeteFormate(queryStr,2);
    //On finit par les titres
    queryStr = " SELECT Id_Titre AS 'Id', Titre AS 'Entite', Titre_Formate AS 'Entite_Formatee' FROM Titre";
    ExecutionRequeteFormate(queryStr,3);

}
void OutilsBDD::ExecutionRequeteFormate(QString queryStr, int Categorie)
{
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString Entite= rec.value("Entite").toString();
        QString Id_Entite = rec.value("Id").toString();
        QString Entite_Formatee = rec.value("Entite_Formatee").toString();
        FormaterEntiteBDD(Entite);
        if ( Entite_Formatee != Entite )
        {
            emit EcrireMessage( Entite );
            Reformatage(Entite,Id_Entite,Categorie);
        }
    }
}

void OutilsBDD::ExecutionRequeteMajuscules(QString queryStr, int Categorie)
{
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString Entite= rec.value("Entite").toString();
        QString Id_Entite = rec.value("Id").toString();
        MajusuculeAChaqueMot(Entite);
        if ( Entite != rec.value("Entite").toString() )
        {
            emit EcrireMessage( Entite );
            Majuscules(Entite,Id_Entite,Categorie);
        }
    }
}

QStringList OutilsBDD::creerfilepochettes()
{
    QStringList fileList;

    // On remplit une QStringList avec chacun des filtres désirés ici "*.jpg" .
    QStringList listFilter;
    listFilter << "*.jpg";

    QString selectDir = "./pochettes";

    // On déclare un QDirIterator dans lequel on indique que l'on souhaite parcourir un répertoire et ses sous-répertoires.
    // De plus, on spécifie le filtre qui nous permettra de récupérer uniquement les fichiers du type souhaité.
    QDirIterator dirIterator( selectDir, listFilter , QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories );


    // Tant qu'on n'est pas arrivé à la fin de l'arborescence...
    while ( dirIterator.hasNext() )
    {
        // ...on va au prochain fichier correspondant à notre filtre
        fileList << dirIterator.next();
    }

    return fileList;
}

void OutilsBDD::SupprimerDossiersVides()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Supprime les dossiers vides");
    emit EcrireMessage("----------------");
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

void OutilsBDD::Reformatage(QString Entite,QString Id_Entite, int Categorie)
{
    switch ( Categorie )
    {
    case 1: madatabase.exec("UPDATE Album SET Album_Formate='"+ Entite +"' WHERE Id_Album='"+ Id_Entite +"'");break;
    case 2: madatabase.exec("UPDATE Artiste SET Artiste_Formate='"+ Entite +"' WHERE Id_Artiste='"+ Id_Entite +"'");break;
    case 3: madatabase.exec("UPDATE Titre SET Titre_Formate='"+ Entite +"' WHERE Id_Titre='"+ Id_Entite +"'");break;
    default: break;
    }

}

void OutilsBDD::Majuscules(QString Entite, QString Id_Entite, int Categorie)
{
    switch ( Categorie )
    {
    case 1: madatabase.exec("UPDATE Album SET Album='"+ Entite +"' WHERE Id_Album='"+ Id_Entite +"'");break;
    case 2: madatabase.exec("UPDATE Artiste SET Artiste='"+ Entite +"' WHERE Id_Artiste='"+ Id_Entite +"'");break;
    case 3: madatabase.exec("UPDATE Titre SET Titre='"+ Entite +"' WHERE Id_Titre='"+ Id_Entite +"'");break;
    default:  break;
    }
}
void OutilsBDD::ChangerArtisteDansCompilAlbum()
{
    qDebug() << "ChangerArtisteDansCompilAlbum";
    //Première chose: on marque bien les albums physiques en compil
    madatabase.exec("UPDATE Album SET Type = 2 WHERE Id_Album IN ( SELECT Id_Album FROM Phys WHERE Categorie = 2 ) ");

    //Deuxième partie: On change les artistes des albums marqués compil
    madatabase.exec("UPDATE Album SET Id_Artiste= 1 WHERE Type = 2");

}
void OutilsBDD::MajusculesCompletEntites()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Majuscules en cours sur toutes les données de la bdd");
    emit EcrireMessage("----------------");
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

void OutilsBDD::ArtistesCompils()
{
    QString queryStr = "UPDATE Artiste SET Id_Pochette = (SELECT Id_Pochette FROM Album B, Relations R WHERE Artiste.Id_Artiste = R.Id_Artiste AND B.Id_Album = R.Id_Album) WHERE Id_Artiste NOT IN ( SELECT DISTINCT (Id_Artiste) FROM Relations R, Phys P WHERE R.Id_Album = P.Id_Album AND P.Id_Album IN (SELECT DISTINCT Id_Album FROM Phys WHERE Support !=2)   ) AND Id_Artiste IN ( SELECT DISTINCT (Id_Artiste) FROM Relations R, Phys P WHERE R.Id_Album = P.Id_Album AND P.Id_Album IN (SELECT DISTINCT Id_Album FROM Phys) ) ";

    madatabase.exec( queryStr);
}

void OutilsBDD::SuppressionPochettes()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Suppression des pochettes non utilisées");
    emit EcrireMessage("----------------");

    QStringList Chemins;

    //Sélectionner les chemins de toutes les pochettes que la BDD utilise
    QString queryStr = "SELECT Chemin FROM POCHETTE";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        Chemins << rec.value ( "Chemin" ) .toString().replace("$","'");

    }

    QStringList filelist = creerfilepochettes();

    for ( int cpt = 0; cpt<Chemins.count(); cpt ++ )
    {

        int position = filelist.indexOf ( Chemins[cpt] ) ;
        if( position != -1)
        {
            filelist.removeAt(position);
        }
    }

    for ( int cpt =0; cpt < filelist.count(); cpt ++ )
    {
        QFile::remove ( filelist[cpt] ) ;

    }
    SupprimerDossiersVides();

}
/*******************************************************
 *Permet de supprimer les fichiers des pochettes
 *
 ******************************************************/
bool OutilsBDD::removeDir( const QString& dirPath, const bool remove, const QString fichier )
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

void OutilsBDD::VerifierPoch()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Vérifie l'intégrité des pochettes");
    emit EcrireMessage("----------------");
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
    //Première chose on récupère les pochettes non utilisées
    queryStr = "SELECT Id_Pochette, Chemin FROM Pochette WHERE Id_Pochette !=1 AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Artiste ) AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Album)";
    query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString chemin = rec.value("Chemin").toString();
        QFile::remove( chemin );
        madatabase.exec("DELETE FROM Pochette WHERE Id_Pochette= '"+rec.value("Id_Pochette").toString()+"'");
    }

    //Vide
    madatabase.exec("DELETE FROM Pochette WHERE Chemin = ''");

}

void OutilsBDD::VerifierRelation()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Vérifie l'intégrité des relations");
    emit EcrireMessage("----------------");
    //Vide
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album ='' OR Id_Artiste = '' OR Id_Titre = '' OR Id_Relation = '' ");
    //MP3 ou Phys
    madatabase.exec("UPDATE Relations SET MP3 =0 WHERE MP3 =1 AND Id_Relation NOT IN ( SELECT Id_Relation FROM MP3 ) ");
    madatabase.exec("UPDATE Relations SET MP3 =1 WHERE MP3 =0 AND Id_Relation  IN ( SELECT Id_Relation FROM MP3 ) ");
    madatabase.exec("UPDATE Relations SET Phys =0 WHERE Phys =1 AND Id_Album NOT IN ( SELECT Id_Album FROM PHYS ) ");
    madatabase.exec("UPDATE Relations SET Phys =1 WHERE Phys =0 AND Id_Album IN ( SELECT Id_Album FROM PHYS ) ");
    //Non utilisé
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Phys) AND Id_Relation NOT IN ( SELECT DISTINCT Id_Relation FROM MP3) " );
    madatabase.exec( "DELETE FROM Relations WHERE MP3 =0 AND Phys = 0" );
    madatabase.exec( "DELETE FROM Relations WHERE Id_Titre IS NULL  OR Id_Titre = 0" );
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album = 0  OR Id_Album IS NULL" );
    madatabase.exec( "DELETE FROM Relations WHERE Id_Artiste = 0 OR Id_Artiste IS NULL" );
    madatabase.exec( "DELETE FROM Relations WHERE Num_Piste = 0 OR Num_Piste IS NULL" );

    //Non valide
    madatabase.exec( "DELETE FROM Relations WHERE Id_Album NOT IN (SELECT DISTINCT Id_Album FROM Album) OR Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste) OR Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Titre) OR Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette From Pochette)" );
}

void OutilsBDD::VerifierAlbum()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Vérifie l'intégrité des albums");
    emit EcrireMessage("----------------");
    //Vide
    madatabase.exec( "DELETE FROM Album WHERE Album = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM Album WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Relations ) " );
    //Non valide
    madatabase.exec( "UPDATE Album SET Id_Pochette = '1' WHERE Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Pochette ) " );
    madatabase.exec( "UPDATE Album SET Id_Artiste = '1' WHERE Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste ) " );
    QString queryStr = "SELECT Album, Id_Album, Album_Formate FROM Album";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString nom = rec.value( "Album" ).toString();
        QString Id_Alb = rec.value( "Id_Album").toString();
        QString Alb = rec.value("Album_Formate").toString();
        FormaterEntiteBDD ( nom );
        if ( nom != Alb)
            madatabase.exec( "UPDATE Album SET Album_Formate = '"+ nom +"' WHERE Id_Album = "+ Id_Alb +" " );
    }
}

void OutilsBDD::VerifierArtiste()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Vérifie l'intégrité des artistes");
    emit EcrireMessage("----------------");
    //Vide
    madatabase.exec( "DELETE FROM Artiste WHERE Artiste = '' AND Id_Artiste !='01' " );
    //Non utilisé
    madatabase.exec( "DELETE FROM Artiste WHERE Id_Artiste !='01' AND Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Relations ) " );
    //Non valide
    madatabase.exec( "UPDATE Artiste SET Id_Pochette = '1' WHERE Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Pochette ) " );
    QString queryStr = "SELECT Artiste, Id_Artiste, Artiste_Formate FROM Artiste";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString nom = rec.value( "Artiste" ).toString();
        QString Id_Art = rec.value( "Id_Artiste").toString();
        QString Art = rec.value("Artiste_Formate").toString();
        FormaterEntiteBDD ( nom );
        if ( nom != Art)
            madatabase.exec( "UPDATE Artiste SET Artiste_Formate = '"+ nom +"' WHERE Id_Artiste = "+ Id_Art +" " );
    }
}

void OutilsBDD::VerifierTitre()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Vérifie l'intégrité des titres");
    emit EcrireMessage("----------------");
    //Vide
    madatabase.exec( "DELETE FROM Titre WHERE Titre = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM Titre WHERE Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Relations ) " );
    //Non valide
    madatabase.exec( "UPDATE Titre SET Num_Piste = '1' WHERE Num_Piste = '' " );
    QString queryStr = "SELECT Titre, Id_Titre, Titre_Formate FROM Titre";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString nom = rec.value( "Titre" ).toString();
        QString Id_Titre = rec.value( "Id_Titre").toString();
        QString Titre_Formate = rec.value("Titre_Formate").toString();
        FormaterEntiteBDD ( nom );
        if ( nom != Titre_Formate )
            madatabase.exec( "UPDATE Titre SET Titre_Formate = '"+ nom +"' WHERE Id_Titre = "+ Id_Titre +" " );
    }

}

void OutilsBDD::VerifierMP3()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Vérifie l'intégrité des mp3");
    emit EcrireMessage("----------------");
    //Vide
    madatabase.exec( "DELETE FROM MP3 WHERE Chemin = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM MP3 WHERE Id_Relation NOT IN (SELECT DISTINCT Id_Relation FROM Relations)" );
    //Non valide
    madatabase.exec( "UPDATE MP3 SET Categorie = '1' WHERE Categorie NOT IN ( SELECT DISTINCT Id_Type FROM Type ) " );
}

void OutilsBDD::VerifierPhys()
{
    emit EcrireMessage("----------------");
    emit EcrireMessage("Vérifie l'intégrité des albums physiques");
    emit EcrireMessage("----------------");
    //Vide
    madatabase.exec( "DELETE FROM Phys WHERE CodeBarres = ''" );
    //Non utilisé
    madatabase.exec( "DELETE FROM Phys WHERE Id_Album NOT IN (SELECT  Id_Album FROM Relations)" );
    //Non valide
    madatabase.exec( "UPDATE Phys SET Categorie = '1' WHERE Categorie NOT IN ( SELECT DISTINCT Id_Type FROM Type ) " );

}
