#include "bddartiste.h"
#include "bddsingleton.h"
#include "bddpoch.h"
#include <QtSql>
#include <QtGui>
#include "util.h"

BDDArtiste::BDDArtiste( const QString& artiste, const BDDPoch& pochette, QObject* parent ) :
    QObject( parent ),
    m_id( -1 ),
    m_nom( artiste ),
    m_pochette( &pochette ),
    m_nomFormate( artiste ),
    m_isPochetteSelfCreated( false )
{
    FormaterEntiteBDD( m_nomFormate );

    recupererId();
    if ( m_id == -1 )
        ajouterBDD();
}

BDDArtiste::~BDDArtiste()
{
    if ( m_isPochetteSelfCreated )
        delete m_pochette;
}

void BDDArtiste::recupererId()
{

    QString queryStr = "Select Id_Artiste As 'Artiste', Id_Pochette AS 'Poch' from Artiste WHERE ArtisteSSAccents='" + m_nomFormate+"'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Artiste" ).toInt();
    }
    else
    {
        m_id = -1;
    }
}

void BDDArtiste::ajouterBDD()
{

    QString queryStr = "INSERT INTO Artiste VALUES (null,'" + m_nom + "','" + QString::number(m_pochette->m_id) + "','" + m_nomFormate + "')";
    QSqlQuery query = madatabase.exec( queryStr );
    m_id = query.lastInsertId().toInt();
}

BDDArtiste* BDDArtiste::RecupererArtiste( const int id )
{
    return new BDDArtiste( id );
}

BDDArtiste::BDDArtiste(const int id , QObject *parent):
    QObject( parent ),
    m_id( id ),
    m_nom(),
    m_pochette(),
    m_nomFormate()
{
    QString queryStr = "SELECT Artiste, ArtisteSSAccents, Id_Pochette FROM Artiste WHERE Id_Artiste='" + QString::number( id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        m_nom = rec.value( "Artiste" ).toString().replace("$","'");;
        m_nomFormate = rec.value( "ArtisteSSAccents" ).toString();
        m_pochette = BDDPoch::recupererBDD( rec.value( "Id_Pochette" ).toInt() );
        m_isPochetteSelfCreated = true;
    }
}


void BDDArtiste::updateBDD()
{

}

void BDDArtiste::deleteBDD(const int Id_Artiste)
{
  /*  //On vérifie si l'artiste existe ou non dans la table des relations
    QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Artiste='"+QString::number(Id_Artiste)+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la requête ne renvoie pas de résultat, on efface du coup l'artiste
    if (!query2.first()) {

        queryStri =  "DELETE FROM Artiste WHERE Id_Artiste='"+QString::number(Id_Artiste)+"'";
        query2 = madatabase.exec(queryStri);



    }
*/
}

void BDDArtiste::EchangerArtiste(QString &nom)
{
    QStringList temp=nom.split(" ");
    if (temp.size()==2)
    {
        nom=temp[1]+" "+temp[0];
    }
    if (temp.size()==3)
    {
        nom=temp[1]+" "+temp[2]+" "+temp[0];
    }

}
void BDDArtiste::ChoisirArtisteEchange(QString& nom)
{
    FormaterEntiteBDD(nom);
    QString queryStri="SELECT Artiste FROM Artiste WHERE Nom_Formate='"+nom+"'";
    QSqlQuery query= madatabase.exec(queryStri);

    if (!query.first())
    {
        EchangerArtiste(nom);
        query=madatabase.exec(queryStri);
        if (query.first()) {
            QSqlRecord rec = query.record();
            nom=rec.value("Artiste").toString();
        }
    }


}




