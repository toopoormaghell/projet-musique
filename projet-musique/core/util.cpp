#include "util.h"


void EnleverAccents ( QString& Nom )
{
    Nom.toUtf8();
    Nom.replace( "�", "e" );
    Nom.replace( "�", "e" );
    Nom.replace( "�", "a" );
    Nom.replace( "�", "e" );
    Nom.replace(":"," ");
    Nom.replace("\\"," ");
    Nom.replace("?"," ");
    Nom.replace("!"," ");
    Nom.replace("/"," ");
    Nom.replace("�","a");
    Nom.replace("�","u");
    Nom.replace("�","a");
    Nom.replace("'","$");
    Nom.replace(","," ");
    Nom.replace("�","o");
    Nom.replace("$","");
    Nom.replace(".","");
    Nom.replace("-","");
    Nom.replace("�","a");

    Nom=  Nom.toLower();
}

QString EchangerArtiste(QString Artiste)
{
    QString Echange=Artiste;
    QStringList temp=Artiste.split(" ");
    if (temp.size()==2)
    {
        Echange = temp[1]+" "+temp[0];
    }

    return Echange;
}


void FormaterEntiteBDD(QString& Entite)
{

    EnleverAccents(Entite);
   QString res;
    QStringList temp = Entite.split(" ");

    for (int cpt=0;cpt<temp.count();cpt++)
    {
        res+=temp[cpt];
    }
   Entite=res;


}
