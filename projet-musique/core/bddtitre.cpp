#include "bddtitre.h"
#include "bddsingleton.h"
#include "util.h"
#include <QtSql>
#include <QDebug>
#include "bddartiste.h"
#include "bddalbum.h"

BDDTitre::BDDTitre(const QString& nom, const BDDAlbum& album , QObject* parent) :
    QObject( parent ),
    m_id( -1 ),
    m_nom( nom ),
    m_nomFormate( nom ),
    m_album ( &album ),
    m_areAlbumAndArtisteSelfCreated ( false )
{
    FormaterEntiteBDD( m_nomFormate );
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

void BDDTitre::updateBDD()
{
    QString queryStr = "UPDATE Titre SET Titre_Formate ='" + m_nomFormate + "', Titre ='" +  m_nom  + "' WHERE Id_Titre = '" + QString::number( m_id ) + "'";
    madatabase.exec( queryStr );
}
BDDTitre::~BDDTitre()
{
    if ( m_areAlbumAndArtisteSelfCreated )
    {
        delete m_album;
        delete m_artiste;
    }
}
void BDDTitre::supprimerenBDD() const
{
    QString queryStr = "SELECT Id_Relation from Relations WHERE Id_Titre='" + QString::number( m_id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( !query.first() )
    {
        madatabase.exec( "DELETE FROM Titre WHERE Id_Titre='" + QString::number( m_id ) + "'" );
    }
}

BDDTitre* BDDTitre::RecupererTitre( const int id )
{
    return new BDDTitre( id );
}

void BDDTitre::ajouterBDD()
{
    QString queryStr = "INSERT INTO Titre VALUES (null,'" + m_nom + "','" + m_nomFormate + "')";

    QSqlQuery query =  madatabase.exec( queryStr );

    m_id = query.lastInsertId().toInt();
}

void BDDTitre::recupererId()
{
    QString queryStr = "Select T.Id_Titre As 'Titre' from Titre T, Relations R WHERE T.Titre_Formate='" + m_nomFormate + "' AND T.Id_Titre=R.Id_Titre AND R.Id_Album='"+ QString::number( m_album->m_id )+"'" ;

    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Titre" ).toInt();

    }
    else
    {
        m_id = -1;
    }
}

void BDDTitre::mp3physfusion()
{
 /*   m_mp3 = false; m_phys= false;
    //Première étape: le titre existe ou non en MP3
    QString queryStr = "SELECT M.Id_MP3 FROM Relations R, MP3 M WHERE R.Id_Titre = '" + QString::number( m_id ) + "' AND M.Id_Relation = R.Id_Relation";

    QSqlQuery query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        m_mp3 = true;
    }
    //Deuxième étape: le titre existe ou non sur album phys
    queryStr = " SELECT P.Id_Phys FROM Relations R, Phys P WHERE R.Id_Titre = '" + QString::number( m_id ) + "')) AND P.Id_Album = R.Id_Album ";

    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        m_phys = true;
    }
    */
}

BDDTitre::BDDTitre( const int id, QObject* parent ):
    QObject( parent ),
    m_id( id ),
    m_nom(),
    m_nomFormate(),
    m_artiste(),
    m_album()
{
    QString queryStr = "SELECT Titre, Titre_Formate, R.Id_Artiste, R.Id_Album FROM Titre T,Relations R WHERE T.Id_Titre='" + QString::number( id ) + "' AND R.Id_Titre=T.Id_Titre";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        m_nom = rec.value( "Titre" ).toString().replace( "$", "'" );
        m_nomFormate = rec.value( "Titre_Formate" ).toString();
        m_artiste = BDDArtiste::RecupererArtiste( rec.value( "Id_Artiste" ).toInt() );
        m_album = BDDAlbum::RecupererAlbum( rec.value( "Id_Album" ).toInt() );
        m_areAlbumAndArtisteSelfCreated = true;

    }
}
QList<int> BDDTitre::Similaires( const int id )
{
    QList<int> listeSimilaires;
    BDDTitre* titre = RecupererTitre( id );

    QString queryStr = "SELECT M.Id_MP3 FROM MP3 M, Relations R WHERE R.Id_Titre=='" + QString::number( id ) + "' AND R.Id_Artiste != '" + QString::number( titre->m_artiste->m_id ) + "' AND R.Id_Relation = M.Id_Relation";
    delete titre;
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        listeSimilaires << rec.value( "Id_MP3" ).toInt();
    }
    return listeSimilaires;
}
