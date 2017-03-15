#include "bddmp3.h"
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddtype.h"
#include "bddrelation.h"
#include <QtSql>
#include "tags.h"
#include "bddpoch.h"

BDDMp3::BDDMp3(const QString& Chemin, const BDDRelation& relation, const BDDType& type, QObject* parent):
    IdOwner(-1, parent)
  , m_relation(&relation)
  , m_chemin(Chemin)
  , m_type(&type)
  , m_membersAreSelfCreated(false)
{
    recupererId();

    if (id() == -1)
        ajouterBDD();
    else
        updateBDD();
}

BDDMp3::~BDDMp3()
{
    if ( m_membersAreSelfCreated )
    {
        delete m_type;
        delete m_relation;
    }
}

void BDDMp3::recupererId()
{
    QString queryStr = "SELECT Id_MP3 FROM MP3 WHERE Id_Relation='" + QString::number( m_relation->id() ) + "' AND Chemin='" + m_chemin + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        setId(rec.value( "Id_MP3" ).toInt());

    }
    else
    {
        setId(-1);
    }
}
void BDDMp3::ajouterBDD()
{
    QString queryStr = "INSERT INTO MP3 VALUES (null,'" + QString::number( m_relation->id() ) + "','" + m_chemin + "','" + QString::number( m_type->id() ) + "')";
    QSqlQuery query = madatabase.exec( queryStr );
    setId(query.lastInsertId().toInt());
}
BDDMp3* BDDMp3::RecupererMp3( const int id )
{
    return new BDDMp3( id );
}
BDDMp3* BDDMp3::RecupererMp3ParChemin( const QString& chemin )
{
    return new BDDMp3( chemin );
}

BDDMp3 *BDDMp3::RecupererMP3ParTitre(const int& id)
{
    QString queryStr = "SELECT Id_Mp3 FROM Mp3 WHERE Id_Relation =( SELECT Id_Relation FROM Relations WHERE Id_Titre='" + QString::number( id ) + "')";

    QSqlQuery query = madatabase.exec( queryStr );
    int id_mp3 = -1;
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id_mp3 = rec.value("Id_Mp3").toInt();
    }

    return new BDDMp3( id_mp3 );
}

void BDDMp3::ChangerTag(const QString &NouveauAlbum, const QString &NouveauTitre, const QString &NouveauArtiste, const int &NouvelleAnnee, const int &NouvellePiste, const QString &NouvellePoch)
{
    Tags t ( m_chemin );
    t.setAlbum( NouveauAlbum );
    t.setArtist( NouveauArtiste );
    t.setTitle( NouveauTitre );
    t.setTrack( NouvellePiste );
    t.setYear( NouvelleAnnee );
    t.save();
    t.fermerTag();

    Tags::setPoch( NouvellePoch, m_chemin );
}

BDDMp3::BDDMp3(const int id, QObject* parent):
    IdOwner(id, parent)
  , m_relation(NULL)
  , m_chemin()
  , m_type(NULL)
  , m_membersAreSelfCreated(false)

{
    QString queryStr = "SELECT * FROM MP3 WHERE Id_MP3='" + QString::number(id) + "'";

    QSqlQuery query = madatabase.exec(queryStr);
    if (query.first())
    {
        QSqlRecord rec = query.record();

        m_relation = BDDRelation::RecupererRelation(rec.value("Id_Relation" ).toInt());
        m_chemin = rec.value("Chemin").toString().replace("$", "'");
        m_type = BDDType::RecupererType(rec.value("Categorie").toInt());
        m_membersAreSelfCreated = true;
    }
}

BDDMp3::BDDMp3(const QString& chemin, QObject* parent):
    IdOwner(-1, parent)
  , m_relation(NULL)
  , m_chemin(chemin)
  , m_type(NULL)
{
    m_chemin = m_chemin.replace("'", "$");
    QString queryStr = "SELECT * FROM MP3 WHERE Chemin='" + m_chemin + "'";

    QSqlQuery query = madatabase.exec(queryStr);
    if (query.first())
    {
        QSqlRecord rec = query.record();

        setId(rec.value("Id_Relation").toInt());
        m_relation = BDDRelation::RecupererRelation(rec.value("Id_Relation").toInt());
        m_type = BDDType::RecupererType(rec.value("Categorie").toInt());
        m_membersAreSelfCreated = true;
    }
}

void BDDMp3::updateBDD()
{
    QString queryStr = "UPDATE MP3 SET Id_Relation ='" + QString::number( m_relation->id() ) + "', Chemin ='" + m_chemin.replace( "'", "$" ) + "', Categorie = '" + QString::number( m_type->id() ) + "'  WHERE Id_MP3 = '" + QString::number( id() ) + "'";

    madatabase.exec( queryStr );
}
void BDDMp3::supprimerenBDD() const
{
    QString queryStr = "DELETE FROM MP3 WHERE Id_MP3='" + QString::number( id() ) + "'";

    m_relation->supprimerenBDDMP3();
    madatabase.exec( queryStr );
}
