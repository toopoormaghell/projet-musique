#include "gestionverifications.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddpoch.h"
#include "bddversion5.h"

GestionVerifications::GestionVerifications()
{

}
void GestionVerifications::SuppressionPochettes()
{
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
    BDDSingleton::getInstance().supprimerdossiersvides();
}
QStringList GestionVerifications::creerfilepochettes()
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
void GestionVerifications::verifierbdd()
{
    BDDSingleton::getInstance().verifierBDD();
}
void GestionVerifications::titresphysetmp3()
{
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

void GestionVerifications::PochCompils()
{

    //Sélectionner les chemins de toutes les pochettes que la BDD utilise
    QString queryStr = "SELECT Chemin, A.Album_Formate, P.Id_Pochette FROM POCHETTE P, Album A, Phys Ph WHERE A.Id_Album = Ph.Id_Album AND P.Id_Pochette = A.Id_Pochette AND Ph.Support = 2 ";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString Chemin = rec.value ( "Chemin" ) .toString().replace("$","'");
        QString album = rec.value ( "Album_Formate" ) .toString().replace("$","'");
        BDDPoch* poch = BDDPoch::recupererBDD(rec.value ( "Id_Pochette" ).toInt());

        QDir dossier;
        //nouveau chemin
        QString chm = "./pochettes/compil" ;
        dossier.mkdir( chm );
        chm += "/" + album + ".jpg";

        if (chm != Chemin )
        {
            //on enregistre la nouvelle image
            poch->m_image.save( chm );
            //On update la BDD avec le nouveau chemin
            poch->m_chemin = chm;
            poch->updateBDD();

            //On supprime l'image de l'ancien chemin
            QFile::remove( Chemin );
        }
    }
}
void GestionVerifications::ReformatageEntites()
{
    BDDVersion5 temp;
    temp.ReformatageCompletEntites();

}
void GestionVerifications::MajusculesEntites()
{
    BDDVersion5 temp;
    temp.MajusculesCompletEntites();

}
void GestionVerifications::ArtistesCompils()
{
    QString queryStr = "UPDATE Artiste SET Id_Pochette = (SELECT Id_Pochette FROM Album B, Relations R WHERE Artiste.Id_Artiste = R.Id_Artiste AND B.Id_Album = R.Id_Album) WHERE Id_Artiste NOT IN ( SELECT DISTINCT (Id_Artiste) FROM Relations R, Phys P WHERE R.Id_Album = P.Id_Album AND P.Id_Album IN (SELECT DISTINCT Id_Album FROM Phys WHERE Support !=2)   ) AND Id_Artiste IN ( SELECT DISTINCT (Id_Artiste) FROM Relations R, Phys P WHERE R.Id_Album = P.Id_Album AND P.Id_Album IN (SELECT DISTINCT Id_Album FROM Phys) ) ";

    madatabase.exec( queryStr);


}
