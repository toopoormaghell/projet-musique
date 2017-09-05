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
    Nom.replace( "ï", "i" );


}
void EnleverPonctuation( QString& Nom)
{
    Nom.replace( ":", " " );
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

    Nom =  Nom.toLower();
}

void FormaterEntiteBDD( QString& Entite )
{
    EnleverAccents( Entite );
    EnleverPonctuation( Entite );
    MajusuculeAChaqueMot( Entite );
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
