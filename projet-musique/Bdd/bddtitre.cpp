#include "bddtitre.h"
#include "bddsingleton.h"
#include "util.h"
#include <QtSql>
#include "bddartiste.h"
#include "bddalbum.h"


void BDDTitre::updateBDD()
{
    if ( id() == -1 )
    {
        QString queryStr = "INSERT INTO Titre VALUES (null,'" + m_nom + "','" + m_nomFormate + "')";

        QSqlQuery query =  madatabase.exec( queryStr );

        setId(query.lastInsertId().toInt());
    }
    else
    {
        QString queryStr = "UPDATE Titre SET Titre_Formate ='" + m_nomFormate + "', Titre ='" +  m_nom  + "' WHERE Id_Titre = '" + QString::number( id() ) + "'";
        madatabase.exec( queryStr );

    }

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

BDDTitre::~BDDTitre()
{

}

Handle<BDDTitre> BDDTitre::recupererBDD(const QString& nom)
{
    QString nomF ( nom );
    EnleverAccents ( nomF );
    MajusuculeAChaqueMot ( nomF );
    const int id = TrouverId( nomF );
    QString nomFormate ( nomF );
    FormaterEntiteBDD ( nomFormate );
    return Handle<BDDTitre>(new BDDTitre ( id, nomF , nomFormate ));

}

Handle<BDDTitre> BDDTitre::recupererBDD( const int id )
{

    QString queryStr = "SELECT Titre, Titre_Formate, R.Id_Artiste, R.Id_Album FROM Titre T,Relations R WHERE T.Id_Titre='" + QString::number(id) + "' AND R.Id_Titre=T.Id_Titre";
    QSqlQuery query = madatabase.exec(queryStr);

    QString nom, nomFormate;
    if (query.first() )
    {
        QSqlRecord rec = query.record();
        nom = rec.value("Titre").toString().replace("$", "'");
        nomFormate = rec.value("Titre_Formate").toString();

    }

    return Handle<BDDTitre>(new BDDTitre( id, nom, nomFormate ));
}


int BDDTitre::recupererId(const QString& nomFormate)
{
    QString queryStr = "Select T.Id_Titre As 'Titre' from Titre T, Relations R WHERE T.Titre_Formate='" + nomFormate + "' " ;

    QSqlQuery query = madatabase.exec( queryStr );
    int id = -1;
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id = (rec.value( "Titre" ).toInt());

    }


    return id;
}



BDDTitre::BDDTitre(const int id, QString& nom, QString& nomFormate, QObject* parent):
    IdOwner(id, parent)
  , m_nom(nom)
  , m_nomFormate(nomFormate)
{

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

int BDDTitre::TrouverId(const QString& nom)
{
    QString nomFormate = nom;
    EnleverAccents ( nomFormate );
    FormaterEntiteBDD( nomFormate );

    return recupererId( nomFormate );
}

QList<int> BDDTitre::Similaires( const int id )
{
    QList<int> listeSimilaires;
    Handle<BDDTitre> titre = recupererBDD( id );

    QString queryStr = "SELECT R.Id_Relation FROM MP3 M, Relations R WHERE R.Id_Titre =='" + QString::number( id ) + "' AND R.Id_Relation = M.Id_Relation";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        listeSimilaires << rec.value( "Id_Relation" ).toInt();
    }
    return listeSimilaires;
}
