#include "util.h"


void EnleverAccents ( QString& Nom )
{
    Nom.toUtf8();
    Nom.replace( "�", "e" );
    Nom.replace( "�", "e" );
    Nom.replace( "�", "a" );
    Nom.replace( "�", "e" );
    Nom=  Nom.toLower();
    Nom.replace(":"," ");
    Nom.replace("'","\'");
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
