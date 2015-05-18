#include "bddgeneral.h"
#include <QtSql>
#include "bddsingleton.h"
#include <QDir>

bddgeneral::bddgeneral(QObject *parent) : QObject(parent)
{
}

QString bddgeneral::getdossierpardef()
{
    QString queryStr = "Select Valeur from Configuration WHERE Intitule='DossierParDef'" ;
    QSqlQuery  query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();

    return rec.value("Valeur").toString();

}
void bddgeneral::verifierBDD()
{
    //On vérifie si la table MP3 est conforme
    madatabase.exec("DELETE FROM Titre WHERE Titre = ''");
    madatabase.exec("DELETE FROM Artiste WHERE Artiste = ''");
    madatabase.exec("DELETE FROM Album WHERE Album = ''");
    madatabase.exec("DELETE FROM Pochette WHERE Chemin = ''");

    madatabase.exec("DELETE FROM Relations WHERE Id_Album NOT IN (SELECT DISTINCT Id_Album FROM Album) OR Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste) OR Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Titre) OR Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette From Pochette)");
    madatabase.exec("DELETE FROM Relations WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Phys) AND Id_Relation NOT IN ( SELECT DISTINCT Id_Relation FROM MP3) ");

    madatabase.exec("DELETE FROM MP3 WHERE Id_Relation NOT IN (SELECT DISTINCT Id_Relation FROM Relations)");
    madatabase.exec("DELETE FROM Phys WHERE Id_Album NOT IN (SELECT  Id_Album FROM Relations)");
}
void bddgeneral::EnregistrerDossierParDef(QString doss)
{
    QString queryStri ="Update Configuration SET Valeur='"+doss+"' WHERE Intitule='DossierParDef'";
    madatabase.exec(queryStri);
}
void bddgeneral::CopierBDD()
{
    QString cheminBDD="./Musique.db";
    QFile temp(cheminBDD);
    QString cheminCopie="../Musique.db";
    temp.copy(cheminCopie);
}
void bddgeneral::ChargerBDD()
{
    QString cheminBDD="../Musique.db";
    QFile temp(cheminBDD);
    QString cheminCopie="./Musique.db";
    temp.copy(cheminCopie);
}
bool bddgeneral::ActualiserAlbums()
{
    bool resultat=false;
    QString queryStr="Select Valeur From Configuration where Intitule='ActualiserAlbums'";
    QSqlQuery query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();
    QString temp=rec.value( "Valeur" ).toString();
    if (temp=="Oui")
    {
        resultat=true;
    }
    return resultat;
}
bool bddgeneral::ActualiserCompil()
{
    bool resultat=false;
    QString queryStr="Select Valeur From Configuration where Intitule='ActualiserCompil'";
    QSqlQuery query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();
    QString temp=rec.value( "Valeur" ).toString();
    if (temp=="Oui")
    {
        resultat=true;
    }
    return resultat;
}
bool bddgeneral::ActualiserLives()
{
    bool resultat=false;
    QString queryStr="Select Valeur From Configuration where Intitule='ActualiserLives'";
    QSqlQuery query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();
    QString temp=rec.value( "Valeur" ).toString();
    if (temp=="Oui")
    {
        resultat=true;
    }
    return resultat;
}
void bddgeneral::EnregistrerActuAlbums(bool check)
{
    QString queryStr="Update Configuration SET Valeur=";

    if(check)
    {
        queryStr+="'Oui'";
    } else
    {
        queryStr+="'Non'";
    }
    queryStr+=" WHERE Intitule='ActualiserAlbums'";

    QSqlQuery query = madatabase.exec(queryStr);
}
void bddgeneral::EnregistrerActuCompil(bool check)
{
    QString queryStr="Update Configuration SET Valeur=";

    if(check)
    {
        queryStr+="'Oui'";
    } else
    {
        queryStr+="'Non'";
    }
    queryStr+=" WHERE Intitule='ActualiserCompil'";

    QSqlQuery query = madatabase.exec(queryStr);
}
void bddgeneral::EnregistrerActuLives(bool check)
{
    QString queryStr="Update Configuration SET Valeur=";

    if(check)
    {
        queryStr+="'Oui'";
    } else
    {
        queryStr+="'Non'";
    }
    queryStr+=" WHERE Intitule='ActualiserLives'";

    QSqlQuery query = madatabase.exec(queryStr);
}
QString bddgeneral::getjetonAcces()
{
    QString QueryStr="SELECT Valeur FROM Configuration WHERE Intitule='JetonAcces'";
    QSqlQuery query=madatabase.exec(QueryStr);

    while (query.next())
    {
        QSqlRecord rec=query.record();
        return rec.value("Valeur").toString();
    }
}
QString bddgeneral::getjetonSecret()
{
    QString QueryStr="SELECT Valeur FROM Configuration WHERE Intitule='JetonSecret'";
    QSqlQuery query=madatabase.exec(QueryStr);

    while (query.next())
    {
        QSqlRecord rec=query.record();
        return rec.value("Valeur").toString();
    }
}
void bddgeneral::changerjetonAcces(QString jeton)
{
    QString QueryStr="UPDATE Configuration SET Valeur='"+jeton+"' WHERE Intitule='JetonAcces'";
    QSqlQuery query=madatabase.exec(QueryStr);
}
void bddgeneral::changerjetonSecret(QString jeton)
{
    QString QueryStr="UPDATE Configuration SET Valeur='"+jeton+"' WHERE Intitule='JetonSecret'";
    QSqlQuery query=madatabase.exec(QueryStr);
}
