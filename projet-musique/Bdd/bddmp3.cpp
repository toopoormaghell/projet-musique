#include "bddmp3.h"
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddsupport.h"
#include "bddrelation.h"
#include <QtSql>
#include "tags.h"
#include "bddpoch.h"

BDDMp3::BDDMp3( const int id, const QString& Chemin, const Handle<BDDRelation>& relation, const Handle<BDDSupport>& support, QObject* parent ):
    IdOwner( id , parent )
  , m_relation( relation )
  , m_chemin( Chemin )
  , m_support( support )
{

}

BDDMp3::~BDDMp3()
{
}

Handle<BDDMp3> BDDMp3::RecupererBDD(const int id)
{
    QString chemin;
    Handle<BDDRelation> rel(nullptr);
    Handle<BDDSupport> supp(nullptr);

    QString queryStr = "SELECT * FROM MP3 WHERE Id_MP3='" + QString::number(id) + "'";

    QSqlQuery query = madatabase.exec(queryStr);

    if (query.first())
    {
        QSqlRecord rec = query.record();

        rel = BDDRelation::recupererBDD(rec.value("Id_Relation" ).toInt());
        chemin = rec.value("Chemin").toString().replace("$", "'");
        supp = BDDSupport::RecupererSupport(rec.value("Support").toInt());

    }

    return Handle<BDDMp3>(new BDDMp3 ( id, chemin , rel , supp ));
}

Handle<BDDMp3> BDDMp3::RecupererBDD( const QString& Chemin, const Handle<BDDRelation>& relation, const Handle<BDDSupport>& support )
{
    const int id = recupererId( Chemin );

    return Handle<BDDMp3>(new BDDMp3( id , Chemin, relation , support ));
}

Handle<BDDMp3> BDDMp3::RecupererBDDParRelation(const int id)
{
    QString queryStr = "SELECT Id_Mp3 FROM MP3 WHERE Id_Relation ='" + QString::number( id ) + "'";

    QSqlQuery query = madatabase.exec( queryStr );
    int id_mp3 = -1;

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id_mp3 = rec.value("Id_Mp3").toInt();
    }

    return RecupererBDD( id_mp3 );
}

Handle<BDDMp3> BDDMp3::RecupererBDDParChemin(const QString& Chemin)
{
    QString queryStr = "SELECT Id_MP3 FROM MP3 WHERE Chemin='" + Chemin + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    int id_mp3 = -1;
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id_mp3 = rec.value("Id_Mp3").toInt();
    }

    return RecupererBDD( id_mp3 );
}

QMap<int, QStringList> BDDMp3::RecupererMP3s(int Type)
{
    QMap<int, QStringList> chemins;

    QString queryStri = "Select Id_MP3, Chemin FROM MP3 M, Relations R, Album B WHERE R.Id_Relation = M.Id_Relation AND R.Id_Album = B.Id_Album AND B.Type='" + QString::number( Type ) + "'";

    if ( Type == 1 )
    {
        queryStri = "Select Id_MP3, Chemin FROM MP3 M, Relations R, Album B WHERE R.Id_Relation = M.Id_Relation AND R.Id_Album = B.Id_Album AND B.Type NOT IN(2)";
    }

    QSqlQuery  query =  madatabase.exec( queryStri );

    while ( query.next() )
    {
        QStringList infos;
        QSqlRecord rec = query.record();
        const int Mp3 = rec.value( "Id_MP3" ).toInt();
        const QString Chem = rec.value( "Chemin" ).toString().replace( "$", "'" );

        infos  << Chem << "Pas Trouvé";

        chemins.insert( Mp3, infos );

    }

    return chemins;
}

int BDDMp3::recupererId(const QString& Chemin)
{
    int id = -1;
    QString queryStr = "SELECT Id_MP3 FROM MP3 WHERE Chemin='" + Chemin + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id =  rec.value( "Id_MP3" ).toInt();
    }
    return id;
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

void BDDMp3::updateBDD()
{
    if ( id() ==-1 )
    {
        QString queryStr = "INSERT INTO MP3 VALUES (null,'" + QString::number( m_relation->id() ) + "','" + m_chemin + "','" + QString::number( m_support->id() ) + "')";
        QSqlQuery query = madatabase.exec( queryStr );
        setId(query.lastInsertId().toInt());
    }   else
    {
        QString queryStr = "UPDATE MP3 SET Id_Relation ='" + QString::number( m_relation->id() ) + "', Chemin ='" + m_chemin.replace( "'", "$" ) + "', Support = '" + QString::number( m_support->id() ) + "'  WHERE Id_MP3 = '" + QString::number( id() ) + "'";

        madatabase.exec( queryStr );
    }
}
void BDDMp3::supprimerenBDD() const
{
    if ( id() != 0 )
    {
        QString queryStr = "DELETE FROM MP3 WHERE Id_MP3='" + QString::number( id() ) + "'";
        if (m_relation != nullptr)
            m_relation->supprimerenBDDMP3();

        madatabase.exec( queryStr );
    }
}
