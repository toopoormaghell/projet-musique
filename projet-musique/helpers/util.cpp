#include "util.h"
#include <QStringList>
#include <QDebug>

QString EchangerArtiste( QString Artiste )
{
    QString Echange = Artiste;
    QStringList temp = Artiste.split( " " );
    if ( temp.size() == 2 )
    {
        Echange = temp[1] + " " + temp[0];
    }

    return Echange;
}
void EnleverAccents( QString& Nom )
{
    Nom.toUtf8();
    Nom.replace( "è", "e" );
    Nom.replace( "é", "e" );
    Nom.replace( "à", "a" );
    Nom.replace( "ê", "e" );
    Nom.replace( "â", "a" );
    Nom.replace( "û", "u" );
    Nom.replace( "ù" , "u" );
    Nom.replace( "Â", "a" );
    Nom.replace( "ô", "o" );
    Nom.replace( "À", "a" );
    Nom.replace( "î" ,"i" );
    Nom.replace( "+", " " );
    Nom.replace( "ç", "c" );
    Nom.replace( "É", "e" );
    Nom.replace( "Ê", "e" );
    Nom.replace( "ï", "i" );
    Nom.replace( "œ", "oe" );

}
void EnleverPonctuation( QString& Nom)
{
    Nom.replace( ":", " " );
    Nom.replace( "*", " " );
    Nom.replace( "\\", " " );
    Nom.replace( "?", " " );
    Nom.replace( "!", " " );
    Nom.replace( "/", " " );
    Nom.replace( "'", "$" );
    Nom.replace( ",", " " );
    Nom.replace( "&", " " );
    Nom.replace( "$", " " );
    Nom.replace( ".", " " );
    Nom.replace( "-", " " );
    Nom.replace( '"'," " );
    Nom.replace( "#", " " );
    Nom.replace( "(", " " );
    Nom.replace( "%","pourcent" );
    Nom.replace( ")"," " );
    Nom.replace( "["," " );
    Nom.replace( "]"," " );
    Nom.replace( "'"," " );
    Nom.replace(QString("\u2026")," ");
    Nom.replace("n°","numero");
    Nom.replace("N°","numero");
    Nom.replace("+"," ");
    Nom.replace("-"," ");
    Nom =  Nom.toLower();
}

void FormaterEntiteBDD( QString& Entite )
{
    EnleverAccents( Entite );
    EnleverPonctuation( Entite );

    QString res;
    QStringList temp = Entite.split( " " );

    for ( int cpt = 0; cpt < temp.count(); cpt++ )
    {
        res += temp[cpt];
    }
    Entite = res;
}

void MajusuculeAChaqueMot(QString& Entite)
{
    QString temp;
   Entite = Entite.toLower();
    QStringList decoupage = Entite.split(" ");
    for ( int cpt = 0; cpt < decoupage.count(); cpt++ )
    {

        QString decoup = decoupage[cpt];
        decoup =decoup.remove(0,1);
        temp += decoupage[cpt][0].toUpper()+ decoup;
        if ( cpt != decoupage.count()-1)
        {
            temp +=' ';
        }
    }


    Entite = temp;

}

QString AnneesSwitch( int type )
{
    switch ( type )
    {
    case 0 :
        return "Annee <1980";
    case 1 :
        return " Annee >=1980 AND Annee <1990";
    case 2 :
        return " Annee >=1990 AND Annee <2000";
    case 3 :
        return " Annee>=2000 AND Annee<2010";
    case 4 :
        return " Annee>=2010 AND Annee<2015";
    case 5 :
        return " Annee>=2015";
    default :
        return " Annee>=2015";
    }
}


QString CreerChemin(QString& alb, QString& art, QString& tit)
{

    QString artisteFormate( art );
    QString albumFormate( alb );
    QString titreFormate ( tit );
    FormaterEntiteBDD( artisteFormate );
    FormaterEntiteBDD( albumFormate );
    FormaterEntiteBDD( titreFormate );

    return "./pochettes/" + artisteFormate + "/" + albumFormate + ".jpg";
}
