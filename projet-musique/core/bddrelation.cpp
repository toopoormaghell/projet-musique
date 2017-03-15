#include "bddrelation.h"
#include "util.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddtitre.h"
#include "bddalbum.h"
#include "bddartiste.h"

BDDRelation::BDDRelation(const BDDAlbum& album, const BDDArtiste& artiste, const BDDTitre& titre, const int num_piste, const QString& duree, const int mp3, const int phys, const int MP3Phys, QObject* parent):
    IdOwner(-1, parent)
  , m_titre(&titre)
  , m_album(&album)
  , m_artiste(&artiste)
  , m_num_piste(num_piste)
  , m_duree(duree)
  , m_mp3(mp3)
  , m_phys(phys)
  , m_areSelfCreated(false)
{
    recupererId();
    if (id() == -1)
        ajouterBDD();
    else
        updateBDD(MP3Phys);
}

BDDRelation::~BDDRelation()
{
    if (m_areSelfCreated)
    {
        delete m_artiste;
        delete m_album;
        delete m_titre;
    }
}
void BDDRelation::recupererId()
{
    //on vérifie si la relation existe ou non
    QString queryStr = "SELECT Id_Relation from Relations WHERE Id_Titre='" + QString::number( m_titre->id() ) + "' AND Id_Artiste='" + QString::number( m_artiste->id() ) + "' AND Id_Album='" + QString::number( m_album->id() ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        setId(rec.value( "Id_Relation" ).toInt());
    }
    else
    {
        setId(-1);
    }
}


void BDDRelation::updateBDD(const int MP3Phys)
{
    QString queryStr="";
    //MP3Phys = 1 si ca vient des MP3
    //MP3Phys = 0 si ca vient des Phys
    //MP3Phys = 2 si c'est juste une update
    queryStr = "UPDATE Relations SET Id_Titre ='" + QString::number( m_titre->id() ) + "', Id_Artiste='" + QString::number( m_artiste->id() ) + "', Id_Album= '" + QString::number( m_album->id() ) + "', Duree = '" +  m_duree + "', Num_Piste='" + QString::number( m_num_piste ) + "', MP3='" + QString::number( m_mp3 ) + "', Phys='" + QString::number( m_phys ) + "' WHERE Id_Relation = '" + QString::number( id() ) + "'";

    if (MP3Phys == 1)
    {
        queryStr = "UPDATE Relations SET Id_Titre ='" + QString::number( m_titre->id() ) + "', Id_Artiste='" + QString::number( m_artiste->id() ) + "', Id_Album= '" + QString::number( m_album->id() ) + "', Duree = '" +  m_duree + "', Num_Piste='" + QString::number( m_num_piste ) + "', MP3='" + QString::number( m_mp3 ) + "' WHERE Id_Relation = '" + QString::number( id() ) + "'";
    }
    if (MP3Phys == 0)
    {
        queryStr = "UPDATE Relations SET Id_Titre ='" + QString::number( m_titre->id() ) + "', Id_Artiste='" + QString::number( m_artiste->id() ) + "', Id_Album= '" + QString::number( m_album->id() ) + "', Duree = '" +  m_duree + "', Num_Piste='" + QString::number( m_num_piste ) + "', Phys='" + QString::number( m_phys ) + "' WHERE Id_Relation = '" + QString::number( id() ) + "'";
    }

    madatabase.exec( queryStr );
}

BDDRelation* BDDRelation::RecupererRelation( const int id )
{
    return new BDDRelation( id );
}

BDDRelation::BDDRelation(const int id, QObject* parent):
    IdOwner(id, parent)
  , m_titre(NULL)
  , m_album(NULL)
  , m_artiste(NULL)
  , m_num_piste(-1)
  , m_duree()
  , m_mp3(-1)
  , m_phys(-1)
  , m_areSelfCreated(false)
{
    QString queryStr = "SELECT Id_Titre, Id_Album, Id_Artiste, Duree, Num_Piste, MP3, Phys FROM Relations WHERE Id_Relation='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next())
    {
        QSqlRecord rec = query.record();

        m_titre = BDDTitre::RecupererTitre(rec.value("Id_Titre").toInt());
        m_album = BDDAlbum::RecupererAlbum(rec.value("Id_Album").toInt());
        m_artiste = BDDArtiste::RecupererArtiste(rec.value("Id_Artiste").toInt());
        m_num_piste = rec.value("Num_Piste").toInt();
        m_duree = rec.value("Duree").toString();
        m_mp3 = rec.value("MP3").toInt();
        m_phys = rec.value("Phys").toInt();
        m_areSelfCreated= true;
    }
}

BDDRelation::BDDRelation(const int id, QString Type, QObject* parent):
    IdOwner(-1, parent)
  , m_titre(NULL)
  , m_album(NULL)
  , m_artiste(NULL)
  , m_num_piste()
  , m_duree()
  , m_mp3()
  , m_phys()
  , m_areSelfCreated(false)
{
    QString queryStr="";
    if (Type == "Titre")
    {
        queryStr = "SELECT Id_Titre, Id_Album, Id_Artiste, Id_Relation, Duree, Num_Piste, MP3, Phys FROM Relations WHERE Id_Titre='" + QString::number(id) + "'";

    }
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next())
    {
        QSqlRecord rec = query.record();

        setId(rec.value("Id_Relation").toInt());
        m_titre = BDDTitre::RecupererTitre(rec.value("Id_Titre").toInt());
        m_album = BDDAlbum::RecupererAlbum(rec.value("Id_Album").toInt());
        m_artiste = BDDArtiste::RecupererArtiste(rec.value("Id_Artiste").toInt());
        m_num_piste = rec.value("Num_Piste").toInt();
        m_duree = rec.value("Duree").toString();
        m_mp3 = rec.value("MP3").toInt();
        m_phys = rec.value("Phys").toInt();
        m_areSelfCreated= true;
    }
}

void BDDRelation::ajouterBDD()
{
    QString  queryStr = "INSERT INTO Relations VALUES (null,'" + QString::number( m_titre->id() ) + "','" + QString::number( m_album->id() ) + "','" + QString::number( m_artiste->id() ) + "','" + m_duree + "','" + QString::number( m_num_piste ) + "','" + QString::number( m_mp3 ) + "','" + QString::number( m_phys ) + "')";

    QSqlQuery query =     madatabase.exec( queryStr );
    setId(query.lastInsertId().toInt());

}

void BDDRelation::supprimerenBDDMP3() const
{

    QString queryStr = "SELECT Id_Phys FROM Phys WHERE Id_Album='" + QString::number( m_album->id() ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );

    if ( !query.first() )
    {

        madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( id() ) + "'" );
    }

}
void BDDRelation::supprimerModifier() const
{
    madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( id() ) + "'" );
}

BDDRelation *BDDRelation::RecupererRelationParTitre(const int id)
{
    return new BDDRelation(id, "Titre");
}
void BDDRelation::supprimerenBDDPhys() const
{

    QString queryStr = "SELECT Id_Mp3 FROM MP3 WHERE Id_Relation='" + QString::number( id() ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );

    if ( !query.first() )
    {

        madatabase.exec( "DELETE FROM Relations WHERE Id_Relation='" + QString::number( id() ) + "'" );
    }

}
