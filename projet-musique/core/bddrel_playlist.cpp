#include "bddrel_playlist.h"
#include <QtSql>
#include "meta_album.h"
#include "meta_titre.h"

BDDRel_Playlist::BDDRel_Playlist(QObject* parent):
    QObject( parent )
{

}

void BDDRel_Playlist::AjoutRel_Playlist(int id_playlist, int id_relation)
{
    QString queryStr = " INSERT INTO RelPlaylist VALUES(null, '" + QString::number( id_playlist) + "', '" + QString::number( id_relation) + "' ) " ;

    madatabase.exec( queryStr );
}

void BDDRel_Playlist::AjouterAlbumEnPlaylist(int id_playlist, int id_album)
{
    Meta_Album* temp= Meta_Album::RecupererBDD( id_album );

    QList<Meta_Titre *> titres = temp->gettitres();
    for (int i=0;i< titres.count(); i++ )
    {
        if (titres[i]->getid_mp3() > 0 )
        {
           AjoutRel_Playlist(id_playlist, titres[i]->getid_relation() );
        }
    }
}

