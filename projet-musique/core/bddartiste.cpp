#include "bddartiste.h"
#include "bddsingleton.h"
#include "bddpoch.h"
#include <QtSql>
#include <QtGui>
#include "util.h"

BDDArtiste::BDDArtiste(const QString& artiste, BDDPoch& pochette, QObject* parent):
    IdOwner(-1, parent)
  , m_nom(artiste)
  , m_nomFormate(artiste)
  , m_pochette(&pochette)
  , m_isPochetteSelfCreated(false)
{
    EnleverAccents ( m_nom );
    MajusuculeAChaqueMot ( m_nom );
   FormaterEntiteBDD ( m_nomFormate );

    QString art = m_nom;
    TrouverId(art);

    if (id() == -1)
        ajouterBDD();
    else
        updateBDD();
}

BDDArtiste::~BDDArtiste()
{
    if ( m_isPochetteSelfCreated )
        delete m_pochette;
}

void BDDArtiste::recupererId()
{

    QString queryStr = "Select Id_Artiste As 'Artiste', Id_Pochette AS 'Poch' from Artiste WHERE Artiste_Formate='" + m_nomFormate + "'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        setId(rec.value( "Artiste" ).toInt());
        m_pochette = BDDPoch::recupererBDD(rec.value("Poch").toInt());
        m_isPochetteSelfCreated = true;
    }
    else
    {
        setId(-1);
    }
}

void BDDArtiste::ajouterBDD()
{

    QString queryStr = "INSERT INTO Artiste VALUES (null,'" + m_nom + "','" + QString::number( m_pochette->id() ) + "','" + m_nomFormate + "')";
    QSqlQuery query = madatabase.exec( queryStr );
    setId(query.lastInsertId().toInt());
}

BDDArtiste* BDDArtiste::recupererBDD(const int id)
{
    QString queryStr = "SELECT Artiste, Artiste_Formate, Id_Pochette FROM Artiste WHERE Id_Artiste='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    QString nom, nomFormate;
    BDDPoch* pochette = nullptr;
    if (query.first())
    {
        QSqlRecord rec = query.record();

        nom = rec.value("Artiste").toString().replace("$", "'");
        pochette = BDDPoch::recupererBDD(rec.value("Id_Pochette").toInt());
        nomFormate = rec.value("Artiste_Formate").toString();
    }

    return new BDDArtiste(id, nom, nomFormate, pochette);
}

BDDArtiste::BDDArtiste(const int id, const QString& nom, const QString& nomFormate, BDDPoch* pochette, QObject* parent):
    IdOwner(id, parent)
  , m_nom(nom)
  , m_nomFormate(nomFormate)
  , m_pochette(pochette)
{
}

BDDArtiste::BDDArtiste(const QString& artiste, QObject* parent):
    IdOwner(0, parent)
  , m_nom(artiste)
  , m_nomFormate(artiste)
  , m_pochette(NULL)
{
    TrouverId(m_nom);
    QString queryStr = "SELECT Artiste, Artiste_Formate, Id_Pochette FROM Artiste WHERE Id_Artiste='" + QString::number(id()) + "'";

    QSqlQuery query = madatabase.exec(queryStr);
    while (query.next())
    {
        QSqlRecord rec = query.record();

        m_nom = rec.value("Artiste").toString().replace("$", "'");
        m_pochette = BDDPoch::recupererBDD(rec.value("Id_Pochette").toInt());
        m_nomFormate = rec.value("Artiste_Formate").toString();
        m_isPochetteSelfCreated = true;
    }
}

BDDArtiste* BDDArtiste::RecupererArtparNom( QString& nom )
{
    return new BDDArtiste( nom );
}

void BDDArtiste::TrouverId( QString& nom )
{
    setId(-1);
    m_nomFormate = ChoisirArtisteEchange(nom);
    FormaterEntiteBDD( m_nomFormate );
    recupererId();
}

void BDDArtiste::updateBDD()
{
    m_pochette->updateBDD();
    QString queryStri = " UPDATE Artiste SET Artiste ='" + m_nom + "', Artiste_Formate='" + m_nomFormate + "', Id_Pochette='" + QString::number( m_pochette->id() ) + "' WHERE Id_Artiste='" + QString::number( id() ) + "'";
    madatabase.exec( queryStri );

}

void BDDArtiste::supprimerenBDD() const
{
    if ( id() != -1 )
    {
        //On vérifie si l'artiste existe ou non dans la table des relations
        QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Artiste='" + QString::number( id() ) + "'" ;
        QSqlQuery  query2 = madatabase.exec( queryStri );

        //si la requête ne renvoie pas de résultat, on efface du coup l'artiste
        if ( !query2.first() )
        {

            madatabase.exec( "DELETE FROM Artiste WHERE Id_Artiste='" + QString::number( id() ) + "'" );

        }
        m_pochette->supprimerenBDD();

    }
}

void BDDArtiste::EchangerArtiste( QString& nom )
{
    QStringList temp = nom.split( " " );
    if ( temp.size() == 2 )
    {
        nom = temp[1] + " " + temp[0];
    }
    if ( temp.size() == 3 )
    {
        nom = temp[1] + " " + temp[2] + " " + temp[0];
    }

}
QString BDDArtiste::ChoisirArtisteEchange(const QString& nom)
{
    QString temp = nom;
    FormaterEntiteBDD(temp);
    QString queryStri = "SELECT Artiste FROM Artiste WHERE Artiste_Formate='" + temp + "'";
    QSqlQuery query = madatabase.exec( queryStri );

    if ( !query.first() )
    {
        temp = nom;
        EchangerArtiste( temp );
        FormaterEntiteBDD( temp );
        queryStri = "SELECT Artiste FROM Artiste WHERE Artiste_Formate='" + temp + "'";
        query = madatabase.exec( queryStri );
        if ( query.first() )
        {
            QSqlRecord rec = query.record();
            temp = rec.value( "Artiste" ).toString();
        }
    }
    return temp;
}
