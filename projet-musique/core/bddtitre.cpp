#include "bddtitre.h"
#include "bddsingleton.h"
#include "util.h"
#include <QtSql>
#include "bddartiste.h"
#include "bddalbum.h"

BDDTitre::BDDTitre(const QString& nom, QObject* parent):
    IdOwner(-1, parent)
  , m_nom(nom)
  , m_nomFormate(nom)
  , m_areAlbumAndArtisteSelfCreated(false)
{
    EnleverAccents ( m_nom );
    MajusuculeAChaqueMot ( m_nom );
    FormaterEntiteBDD( m_nomFormate );
    recupererId();
    if (id() == -1)
        ajouterBDD();
    else
        updateBDD();
}

void BDDTitre::updateBDD()
{
    QString queryStr = "UPDATE Titre SET Titre_Formate ='" + m_nomFormate + "', Titre ='" +  m_nom  + "' WHERE Id_Titre = '" + QString::number( id() ) + "'";
    madatabase.exec( queryStr );
}

void BDDTitre::supprimerenBDD() const
{
    if ( id() != -1 )
    {
        QString queryStr = "SELECT Id_Relation from Relations WHERE Id_Titre='" + QString::number( id() ) + "'";
        QSqlQuery query = madatabase.exec( queryStr );

        if ( !query.first() )
        {
            madatabase.exec( "DELETE FROM Titre WHERE Id_Titre='" + QString::number( id() ) + "'" );
        }
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

    setId(query.lastInsertId().toInt());
}

void BDDTitre::recupererId()
{
    QString queryStr = "Select T.Id_Titre As 'Titre' from Titre T, Relations R WHERE T.Titre_Formate='" + m_nomFormate + "' AND T.Id_Titre=R.Id_Titre " ;

    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        setId(rec.value( "Titre" ).toInt());

    }
    else
    {
        setId(-1);
    }
}

void BDDTitre::mp3physfusion()
{
    /*   m_mp3 = false; m_phys= false;
    //Première étape: le titre existe ou non en MP3
    QString queryStr = "SELECT M.Id_MP3 FROM Relations R, MP3 M WHERE R.Id_Titre = '" + QString::number( id() ) + "' AND M.Id_Relation = R.Id_Relation";

    QSqlQuery query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        m_mp3 = true;
    }
    //Deuxième étape: le titre existe ou non sur album phys
    queryStr = " SELECT P.Id_Phys FROM Relations R, Phys P WHERE R.Id_Titre = '" + QString::number( id() ) + "')) AND P.Id_Album = R.Id_Album ";

    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        m_phys = true;
    }
    */
}

BDDTitre::BDDTitre(const int id, QObject* parent):
    IdOwner(id, parent)
  , m_nom()
  , m_nomFormate()
{
    QString queryStr = "SELECT Titre, Titre_Formate, R.Id_Artiste, R.Id_Album FROM Titre T,Relations R WHERE T.Id_Titre='" + QString::number(id) + "' AND R.Id_Titre=T.Id_Titre";
    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next())
    {
        QSqlRecord rec = query.record();
        m_nom = rec.value("Titre").toString().replace("$", "'");
        m_nomFormate = rec.value("Titre_Formate").toString();
        m_areAlbumAndArtisteSelfCreated = true;
    }
}

QList<int> BDDTitre::Similaires( const int id )
{
    QList<int> listeSimilaires;
    BDDTitre* titre = RecupererTitre( id );

    QString queryStr = "SELECT M.Id_MP3 FROM MP3 M, Relations R WHERE R.Id_Titre =='" + QString::number( id ) + "' AND R.Id_Relation = M.Id_Relation";
    delete titre;
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        listeSimilaires << rec.value( "Id_MP3" ).toInt();
    }
    return listeSimilaires;
}
