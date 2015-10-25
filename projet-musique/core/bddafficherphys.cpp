#include "bddafficherphys.h"
#include <QtSql>
#include "bddsingleton.h"

BDDAfficherPhys::BDDAfficherPhys(QObject *parent) :
    QObject(parent)
{
}
QList<int> BDDAfficherPhys::ListeArtiste()
{
    QList<int> liste;

    QString queryStr="SELECT DISTINCT A.Id_Artiste FROM Artiste A, Phys P,Relations R WHERE A.Id_Artiste!='01' AND R.Id_Album=P.Id_Album AND R.Id_Artiste=A.Id_Artiste AND P.Categorie!='2' ORDER BY Artiste";

    QSqlQuery query= madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        liste << rec.value("Id_Artiste").toInt();
    }
    return liste;
}
QList<int> BDDAfficherPhys::listeAlbums(QString Id_Artiste)
{
    QList<int> albums;
    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Categorie='1' ORDER BY Al.Annee DESC";

    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toInt();
    }
    return albums;
}
QList<int> BDDAfficherPhys::listeSingles(QString Id_Artiste)
{
    QList<int> albums;
    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Categorie='3' ORDER BY Al.Annee DESC";

    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toInt();
    }
    return albums;
}

void BDDAfficherPhys::exporterHTML()
{
    QStringList albart=ListeAlbumSauvegarde();

    QString chemin = "F:/Tout.html";
    //Récupère le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName = chemin;
    QFile fichier(fileName);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&fichier);
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
    flux << "<Table>";
    int compcouleur= 0;
    for(int cpt=0;cpt<albart.count();cpt=cpt+2)
    {
        if (compcouleur%2==0)
        {
            flux << "<tr bgcolor='beige'><td>" << QString::number((cpt/2)+1).rightJustified(3,'0') << "</td><td>"<< albart[cpt+1]<<"</td><td>"  << albart[cpt] << "</td></tr>"<< endl;
        } else
        {
            flux << "<tr bgcolor='coral'><td>" << QString::number(cpt/2+1).rightJustified(3,'0') << "</td><td>"<< albart[cpt+1]<<"</td><td>"  << albart[cpt] << "</td></tr>"<< endl;
        }
        compcouleur++;
    }
    flux << "</Table>";
}
QStringList BDDAfficherPhys::ListeAlbumSauvegarde()
{
    QStringList albart;


    QString QueryStr="SELECT DISTINCT Al.Album, Ar.Artiste FROM Phys P,Album Al, Artiste Ar, Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=Al.Id_Album AND R.Id_Artiste = Ar.Id_Artiste ORDER BY Ar.Artiste";
    QSqlQuery query=madatabase.exec(QueryStr);

    while(query.next())
    {
        QSqlRecord rec=query.record();
        albart << rec.value("Album").toString().replace("$","'") << rec.value("Artiste").toString().replace("$","'");
    }
    return albart;

}

QList<int> BDDAfficherPhys::listeCompils(QString Id_Artiste)
{
    QList<int> albums;

    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND P.Id_Album=R.Id_Album AND P.Categorie='2' ORDER BY Al.Annee DESC";
    if ( Id_Artiste =="-1")
    {

        queryStr= "SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P, Relations R WHERE Al.Id_Album = R.Id_Album AND P.Id_Album = R.Id_Album AND P.Categorie='2' ORDER By Al.Annee DESC";
    }
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toInt();
    }
    return albums;
}
QStringList BDDAfficherPhys::ListeTitresPossibles()
{
    QStringList Titres;

    QString QueryStr="SELECT DISTINCT Titre FROM Titre ORDER BY Titre";
    QSqlQuery query=madatabase.exec(QueryStr);

    while(query.next())
    {
        QSqlRecord rec=query.record();
        Titres << rec.value("Titre").toString().replace("$","'") ;
    }
    return Titres;

}
QStringList BDDAfficherPhys::ListeArtistesPossibles()
{
    QStringList Artistes;

    QString QueryStr="SELECT DISTINCT Artiste FROM Artiste ORDER BY Artiste";
    QSqlQuery query=madatabase.exec(QueryStr);

    while(query.next())
    {
        QSqlRecord rec=query.record();
        Artistes << rec.value("Artiste").toString().replace("$","'") ;
    }
    return Artistes;

}
