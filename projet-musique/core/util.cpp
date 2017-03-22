#include "util.h"
#include <QStringList>
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
    Nom.replace( ":", " " );
    Nom.replace( "\\", " " );
    Nom.replace( "?", " " );
    Nom.replace( "!", " " );
    Nom.replace( "/", " " );
    Nom.replace( "â", "a" );
    Nom.replace( "û", "u" );
    Nom.replace( "ù" , "u" );
    Nom.replace( "Â", "a" );
    Nom.replace( "'", "$" );
    Nom.replace( ",", " " );
    Nom.replace( "ô", "o" );
    Nom.replace( "&", " " );
    Nom.replace( "$", " " );
    Nom.replace( ".", " " );
    Nom.replace( "-", " " );
    Nom.replace( "À", "a" );
    Nom.replace( "î" ,"i" );
    Nom.replace( "+", " " );
    Nom.replace( "ç", "c" );
    Nom.replace( "É", "e" );
    Nom.replace( "ï", "i" );
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
    QString res;
    QStringList temp = Entite.split( " " );

    for ( int cpt = 0; cpt < temp.count(); cpt++ )
    {
        res += temp[cpt];
    }
    Entite = res;
}
