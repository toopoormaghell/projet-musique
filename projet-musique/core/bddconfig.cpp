#include "bddconfig.h"
#include <QObject>
#include "bddsingleton.h"
#include <QtSql>

BDDConfig::BDDConfig(QObject *parent) : QObject(parent)
{

}

QString BDDConfig::recupdossierpardef()
{
    QString queryStr = "Select Valeur from Configuration WHERE Intitule='DossierParDef'" ;
    QSqlQuery  query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();

    return rec.value("Valeur").toString();
}
void BDDConfig::EnregistrerDossierParDef(QString doss)
{
    QString queryStri ="Update Configuration SET Valeur='"+doss+"' WHERE Intitule='DossierParDef'";
    madatabase.exec(queryStri);
}
bool BDDConfig::ActualiserAlbums()
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
bool BDDConfig::ActualiserCompil()
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
bool BDDConfig::ActualiserLives()
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
void BDDConfig::EnregistrerActuAlbums(bool check)
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
void BDDConfig::EnregistrerActuCompil(bool check)
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
void BDDConfig::EnregistrerActuLives(bool check)
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
