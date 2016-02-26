#include "bddmp3.h"
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddtype.h"
#include "bddrelation.h"
#include <QtSql>

BDDMp3::BDDMp3(const QString &Chemin, const BDDRelation &relation, const int &type, QObject *parent):
    QObject( parent),
    m_id(-1),
    m_relation(&relation),
    m_album(),
    m_artiste(),
    m_titre(),
    m_type(BDDType::RecupererType(type)),
    m_chemin(Chemin),
    m_membersAreSelfCreated( false )
{
    recupererId();

    if ( m_id == -1 )
    {
        ajouterBDD();
    }
    else
    {
        updateBDD();
    }
}

BDDMp3::~BDDMp3()
{
    if ( m_membersAreSelfCreated )
    {
        delete m_titre;
        delete m_artiste;
        delete m_album;
        delete m_relation;
        delete m_type;
    }
}

void BDDMp3::recupererId()
{
    QString queryStr = "SELECT Id_MP3 FROM MP3 WHERE Id_Relation='" + QString::number(m_relation->m_id) + "' AND Chemin='" + m_chemin + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value("Id_MP3").toInt();

    }
    else
    {
        m_id = -1;
    }
}
void BDDMp3::ajouterBDD()
{
    QString queryStr = "INSERT INTO MP3 VALUES (null,'" + QString::number(m_relation->m_id) + "','" + m_chemin + "','" + QString::number(m_type->m_id) + "')";
    QSqlQuery query = madatabase.exec( queryStr );
    m_id = query.lastInsertId().toInt();
}
BDDMp3* BDDMp3::RecupererMp3(const int id)
{
    return new BDDMp3( id );
}
BDDMp3* BDDMp3::RecupererMp3ParChemin( QString &chemin)
{
    return new BDDMp3(chemin);
}

BDDMp3::BDDMp3(const int id, QObject *parent):
    QObject(parent),
    m_id(id),
    m_relation(),
    m_album(),
    m_artiste(),
    m_titre(),
    m_type(),
    m_chemin()

{
    QString queryStr = "SELECT * FROM MP3 WHERE Id_MP3='" + QString::number( id ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        m_chemin = rec.value( "Chemin" ).toString().replace("$", "'");
        m_type = BDDType::RecupererType(rec.value("Categorie").toInt());
        m_relation = BDDRelation::RecupererRelation(rec.value("Id_Relation").toInt());

        m_album = BDDAlbum::RecupererAlbum(m_relation->m_id_album);
        m_artiste = BDDArtiste::RecupererArtiste(m_relation->m_id_artiste);
        m_titre = BDDTitre::RecupererTitre(m_relation->m_id_titre);
        m_membersAreSelfCreated = true;

    }
}
BDDMp3::BDDMp3(const QString &chemin, QObject *parent):
    QObject(parent),
    m_id(0),
    m_relation(),
    m_album(),
    m_artiste(),
    m_titre(),
    m_type(),
    m_chemin(chemin)
{
    m_chemin = m_chemin.replace("'", "$");
    QString queryStr = "SELECT * FROM MP3 WHERE Chemin='" + m_chemin + "'";

    QSqlQuery query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        m_id = rec.value("Id_Relation").toInt();
        m_type = BDDType::RecupererType(rec.value("Categorie").toInt());
        m_relation = BDDRelation::RecupererRelation(rec.value("Id_Relation").toInt());
        m_album = BDDAlbum::RecupererAlbum(m_relation->m_id_album);
        m_artiste = BDDArtiste::RecupererArtiste(m_relation->m_id_artiste);
        m_titre = BDDTitre::RecupererTitre(m_relation->m_id_titre);
        m_membersAreSelfCreated = true;

    }
}
void BDDMp3::updateBDD()
{

}
void BDDMp3::supprimerenBDD() const
{
    QString queryStr = "DELETE FROM MP3 WHERE Id_MP3='" + QString::number(m_id) + "'";
    madatabase.exec(queryStr);
    m_relation->supprimerenBDDMP3();
    m_album->supprimerenBDD();
    m_artiste->supprimerenBDD();
    m_titre->supprimerenBDD();
}
