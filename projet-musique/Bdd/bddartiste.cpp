#include "bddartiste.h"
#include "bddsingleton.h"
#include "bddpoch.h"
#include <QtSql>
#include <QtGui>
#include "util.h"

BDDArtiste::~BDDArtiste()
{
    delete m_pochette;
}

int BDDArtiste::recupererId(const QString& nomFormate)
{
    QString queryStr = "Select Id_Artiste As 'Artiste' from Artiste WHERE Artiste_Formate='" + nomFormate + "'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    int id = -1;
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id = rec.value( "Artiste" ).toInt();
    }
    return id;
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

    return new BDDArtiste( id, nom, nomFormate, pochette );
}

BDDArtiste::BDDArtiste(const int id, const QString& nom, const QString& nomFormate, BDDPoch* pochette, QObject* parent):
    IdOwner(id, parent)
  , m_nom(nom)
  , m_nomFormate(nomFormate)
  , m_pochette(pochette)
{
}

BDDArtiste* BDDArtiste::recupererBDD(const QString& nom)
{
    const int id = TrouverId(nom);
    return recupererBDD(id);
}

BDDArtiste* BDDArtiste::recupererBDD(const QString& artiste, BDDPoch& pochette)
{
    QString nom(artiste);
    EnleverAccents(nom);
    MajusuculeAChaqueMot(nom);
    QString nomFormate(nom);
    FormaterEntiteBDD(nomFormate);

    const int id = TrouverId(nom);
    if ( id == -1 )
    {
        return new BDDArtiste( id , nom, nomFormate, &pochette);
    } else
    {
        return recupererBDD( id );
    }
}
int BDDArtiste::TrouverId( const QString &nom )
{
    QString nomFormate = ChoisirArtisteEchange( nom );
    FormaterEntiteBDD(nomFormate);
    return recupererId( nomFormate );
}

void BDDArtiste::updateBDD()
{
    m_pochette->updateBDD();
    if (id() == -1)
    {
        QString queryStr = "INSERT INTO Artiste VALUES (null,'" + m_nom + "','" + QString::number( m_pochette->id() ) + "','" + m_nomFormate + "')";
        QSqlQuery query = madatabase.exec( queryStr );
        setId(query.lastInsertId().toInt());
    }
    else
    {
        QString queryStri = " UPDATE Artiste SET Artiste ='" + m_nom + "', Artiste_Formate='" + m_nomFormate + "', Id_Pochette='" + QString::number( m_pochette->id() ) + "' WHERE Id_Artiste='" + QString::number( id() ) + "'";
        madatabase.exec( queryStri );
    }
}

void BDDArtiste::supprimerenBDD() const
{
    if ( id() != -1 && id() != 1 )
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

void BDDArtiste::changerPoch( int id_nouv_poch )
{
    QString queryStri = " UPDATE Artiste SET Artiste ='" + m_nom + "', Artiste_Formate='" + m_nomFormate + "', Id_Pochette='" + QString::number( id_nouv_poch ) + "' WHERE Id_Artiste='" + QString::number( id() ) + "'";
    madatabase.exec( queryStri );
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
