#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QImage>
#include "helpers_global.h"

void HELPERSSHARED_EXPORT FormaterEntiteBDD( QString& Entite );
QString HELPERSSHARED_EXPORT EchangerArtiste( QString Artiste );
void HELPERSSHARED_EXPORT EnleverAccents( QString& Nom );
void HELPERSSHARED_EXPORT EnleverPonctuation( QString& Nom );
void HELPERSSHARED_EXPORT MajusuculeAChaqueMot( QString& Entite );

#ifndef PHYS_STRUCT
#define PHYS_STRUCT
typedef struct HELPERSSHARED_EXPORT _TitresPhys
{
    int Num_Piste;
    QString Duree;
    QString Titre;
    QString id;
    QString Artiste;
    bool MP3Phys;
    bool MP3;
    bool Phys;
    bool Garde;
  //  QString Id_Art;
 //   int Support_MP3;

    _TitresPhys():
        Num_Piste( 0 ),
        Duree(),
        Titre(),
        id(),
        Artiste(),
        MP3Phys( false ),
        MP3( false ),
        Phys ( false ),
        Garde ( false )
  //      ,Id_Art()
  //     , Support_MP3( -1 )
    {}

    char* toString() const
    {
        QString tmp( "Num_Piste='%1' "
                     "Duree='%2' "
                     "Titre='%3' "
                     "id='%4' "
                     "Artiste='%5' "
                     "MP3Phys='%6'\n"
                     "MP3='%7'\n"
                     "Phys='%8'\n"
                     "Garde='%9'\n"
   //                  "Id_Art='%10'\n"
  //                   "Support_MP3='%11'\n"
                     );
        QString tmp2 = tmp.arg( QString::number( Num_Piste ), Duree, Titre, id, Artiste, QString::number( MP3Phys ),QString::number( MP3 ),QString::number( Phys ), QString::number( Garde) );
        return tmp2.toLatin1().data();
    }
} TitresPhys;



typedef struct HELPERSSHARED_EXPORT _AlbumPhys
{
    int Type;
    QString Album;
    QString Artiste;
    int Annee;
    QList<TitresPhys> titres;
    int Id_Release;
    QImage Poch;
    int Id_Album;
    int Id_Poch;
    int Support;
    _AlbumPhys():
        Type( 1 ),
        Album(),
        Artiste(),
        Annee( 1 ),
        titres(),
        Id_Release( 1 ),
        Poch(),
        Id_Album( 1 ),
        Id_Poch ( -1 ),
        Support ( 1 )
    {}
    char* toString() const
    {
        QString tmp2;
        for ( int i = 0; i < titres.size(); ++i )
            tmp2 += titres[i].toString();
        QString tmp( "Type='%1'\n"
                     "Album='%2'\n"
                     "Artiste='%3'\n"
                     "Annee='%4'\n"
                     "titres='\n%5\n'\n"
                     "Id_Release='%6'\n"
                     "Poch='%7'\n"
                     "Id_Album='%8'\n"
                     "Support='%9'\n");
        QString tmp3 = tmp.arg( QString::number( Type ), Album, Artiste, QString::number( Annee ), tmp2, QString::number( Id_Release ), QString::number( Poch.byteCount() ), QString::number( Id_Album ),  QString::number( Support ) );
        return tmp3.toLatin1().data();
    }
} AlbumPhys;
#endif

#endif // UTIL_H