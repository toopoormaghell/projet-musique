#include "bddrelation.h"
#include "util.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddtitre.h"
#include "bddalbum.h"
#include "bddartiste.h"

BDDRelation::BDDRelation(const int id, const Handle<BDDAlbum>& album, const Handle<BDDArtiste>& artiste, const Handle<BDDTitre>& titre, const int num_piste, const QString& duree, const int mp3, const int phys, QObject* parent):
    IdOwner( id , parent)
  , m_titre( titre )
  , m_album( album )
  , m_artiste( artiste )
  , m_num_piste( num_piste )
  , m_duree( duree )
  , m_mp3( mp3 )
  , m_phys( phys )

{

}

BDDRelation::~BDDRelation()
{
}
int BDDRelation::recupererId(const QString& id_album, const QString& id_artiste, const QString &id_titre)
{
    QString queryStr = "SELECT Id_Relation from Relations WHERE Id_Titre='" + id_titre + "' AND Id_Artiste='" + id_artiste + "' AND Id_Album='" + id_album  + "'";

    QSqlQuery query = madatabase.exec( queryStr );
    int id = -1;
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id = rec.value( "Id_Relation" ).toInt();
    }

    return id;
}


void BDDRelation::updateBDD()
{
    if ( id() ==-1 )
    {
        QString  queryStr = "INSERT INTO Relations VALUES (null,'" + QString::number( m_titre->id() ) + "','" + QString::number( m_album->id() ) + "','" + QString::number( m_artiste->id() ) + "','" + QString::number( m_num_piste ) + "','" + m_duree + "','" + QString::number( m_mp3 ) + "','" + QString::number( m_phys ) + "')";

        QSqlQuery query =   madatabase.exec( queryStr );
        setId(query.lastInsertId().toInt());

    } else
    {
        QString   queryStr = "UPDATE Relations SET Id_Titre ='" + QString::number( m_titre->id() ) + "', Id_Artiste='" + QString::number( m_artiste->id() ) + "', Id_Album= '" + QString::number( m_album->id() ) + "', Duree = '" +  m_duree + "', Num_Piste='" + QString::number( m_num_piste ) + "', MP3='" + QString::number( m_mp3 ) + "', Phys='" + QString::number( m_phys ) + "' WHERE Id_Relation = '" + QString::number( id() ) + "'";

         madatabase.exec( queryStr );
    }
}

Handle<BDDRelation> BDDRelation::recupererBDD( const int id )
{
    Handle<BDDArtiste> art(nullptr);
    Handle<BDDAlbum> alb(nullptr);
    Handle<BDDTitre> tit(nullptr);
    QString duree;
    int Num_Piste = 0; int MP3=0; int Phys = 0;

    QString queryStr = "SELECT Id_Titre, Id_Album, Id_Artiste, Duree, Num_Piste, MP3, Phys FROM Relations WHERE Id_Relation='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        tit = BDDTitre::recupererBDD(rec.value("Id_Titre").toInt());
        alb = BDDAlbum::recupererBDD(rec.value("Id_Album").toInt());
        art = BDDArtiste::recupererBDD(rec.value("Id_Artiste").toInt());
        Num_Piste = rec.value("Num_Piste").toInt();
        duree = rec.value("Duree").toString();
        MP3 = rec.value("MP3").toInt();
        Phys = rec.value("Phys").toInt();

    }
    return Handle<BDDRelation>(new BDDRelation( id , alb , art , tit , Num_Piste , duree , MP3 , Phys ));
}

Handle<BDDRelation> BDDRelation::recupererBDD( const Handle<BDDAlbum>& alb, const Handle<BDDArtiste>& art, const Handle<BDDTitre>& titre, const int num_piste, const QString& duree, const int mp3, const int phys)
{
    const int id = recupererId( QString::number( alb->id() ) , QString::number( art->id() ) , QString::number( titre->id() ) );

return Handle<BDDRelation>(new BDDRelation( id, alb, art, titre, num_piste, duree, mp3, phys ));

}

void BDDRelation::supprimerenBDDMP3() const
{

    if ( id() != -1 )
    {
        QString queryStr = "SELECT Id_Phys FROM Phys WHERE Id_Album='" + QString::number( m_album->id() ) + "'";

        QSqlQuery query = madatabase.exec( queryStr );

        if ( !query.first() )
        {
            madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( id() ) + "'" );
        } else
        {
            madatabase.exec("UPDATE Relations SET MP3 = 0 WHERE Id_Relation='" + QString::number( id() ) + "'" );
        }
    }
}
void BDDRelation::supprimerModifier() const
{
    madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( id() ) + "'" );
}

void BDDRelation::supprimerenBDDPhys() const
{

    QString queryStr = "SELECT Id_Mp3 FROM MP3 WHERE Id_Relation='" + QString::number( id() ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );

    if ( !query.first() )
    {

        madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( id() ) + "'" );
    } else
    {
        madatabase.exec("UPDATE Relations SET Phys = 0 WHERE Id_Relation='" + QString::number( id() ) + "'" );
    }

}
