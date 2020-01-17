#include "bddlisteplaylist.h"
#include <QtSql>
#include "meta_titre.h"

BDDListePlaylist::BDDListePlaylist(QObject* parent):
    QObject( parent )
{

}

void BDDListePlaylist::EnregistrerPlaylist(QString nom_playlist)
{
    QString queryStr = " INSERT INTO ListePlaylist VALUES(null, '" + nom_playlist + "' ) " ;

    madatabase.exec( queryStr );


}
void BDDListePlaylist::SupprimerPlaylist( int id_playlist )
{
    QString queryStr = "DELETE FROM ListePlaylist WHERE Id_ListePlaylist ='" + QString::number( id_playlist ) + "'" ;

    madatabase.exec( queryStr );

}

QStringList BDDListePlaylist::listePlaylist()
{
    QStringList liste;
    QString queryStr = " SELECT * FROM ListePlaylist ";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_ListePlaylist").toString();
        liste << rec.value( "Nom_ListePlaylist").toString();
    }

    return liste;
}

QList<int> BDDListePlaylist::listeMp3( int id_Playlist, int Ordre )
{
    QList<int> liste;
    QString queryStr = " SELECT R.Id_Relation FROM RelPlaylist RP, Relations R, Titre T, Artiste A, Album B WHERE RP.Id_ListePlaylist = '" + QString::number( id_Playlist) + "' AND R.Id_Relation = RP.Id_Relation AND  T.Id_Titre = R.Id_Titre AND A.Id_Artiste = R.Id_Artiste AND R.Id_Album = B.Id_Album ";
    queryStr += " ORDER BY " + OrderBy( Ordre );
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        liste << rec.value( "Id_Relation").toInt();

    }

    return liste;
}

QString BDDListePlaylist::OrderBy( int Ordre )
{
    switch (Ordre )
    {
    case 1 : return "A.Artiste, B.Album ";
    case 2 : return "A.Artiste DESC ";
    case 3 : return "T.Titre ";
    case 4 : return "T.Titre DESC";
    default: return "T.Titre ";
    }
}
QString BDDListePlaylist::NbMp3( int id_Playlist )
{
    QString nb;

    QString queryStr = "SELECT COUNT(DISTINCT Id_Relation) AS 'Nb' FROM RelPlaylist WHERE Id_ListePlaylist = '" + QString::number( id_Playlist) + "' ";

    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        nb = rec.value( "Nb").toString();

    }
    return nb;
}
