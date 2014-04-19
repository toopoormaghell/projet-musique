#include "util.h"


void EnleverAccents ( QString& Nom )
{
    Nom.toUtf8();
    Nom.replace( "è", "e" );
    Nom.replace( "é", "e" );
    Nom.replace( "à", "a" );
    Nom.replace( "ê", "e" );
    Nom.replace(":"," ");
    Nom.replace("'","\'");
    Nom.replace("\\"," ");
    Nom.replace("?"," ");
    Nom.replace("!"," ");
    Nom.replace("/"," ");
    Nom.replace("â","a");
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
