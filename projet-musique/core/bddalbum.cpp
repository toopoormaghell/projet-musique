#include "bddalbum.h"
#include "bddpoch.h"
#include "util.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddtype.h"

BDDAlbum::BDDAlbum(const QString& album, const BDDPoch& pochette, int annee, int type, QObject *parent) :
    QObject(parent),
    m_id(-1),
    m_nom(album),
    m_nomFormate(album),
    m_type(BDDType::RecupererType(type)),
    m_pochette( &pochette ),
    m_annee(annee),
    m_areTypeAndPochetteSelfCreated( false )

{
    FormaterEntiteBDD( m_nomFormate );
    recupererId();
    if (m_id==-1)
    {
        ajouterBDD();
    }
}

void BDDAlbum::updateBDD()
{

}


BDDAlbum::~BDDAlbum()
{
    if ( m_areTypeAndPochetteSelfCreated )
    {
        delete m_type;
        delete m_pochette;
    }
}
void BDDAlbum::recupererId()
{
    QString queryStr = "Select Id_Album As 'Album' from Album WHERE Album_Formate='" + m_nomFormate+"' AND Id_Pochette='" + QString::number(m_pochette->m_id) +"'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Album" ).toInt();
    } else
    {
        m_id = -1;
    }
}

BDDAlbum::BDDAlbum(const int id, QObject *parent):
    QObject(parent),
    m_id(id),
    m_nom(),
    m_nomFormate(),
    m_pochette(),
    m_annee(1),
    m_type()
{
    QString queryStr="SELECT Album,Album_Formate,Id_Pochette, Annee, Type FROM Album WHERE Id_Album='"+ QString::number( id )+"'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        m_nom = rec.value( "Album" ).toString().replace("$","'");
        m_nomFormate = rec.value( "Album_Formate" ).toString();
        m_annee=rec.value("Annee").toInt();
        m_type=BDDType::RecupererType(rec.value("Type").toInt());
        m_pochette = BDDPoch::recupererBDD( rec.value( "Id_Pochette" ).toInt() );
        m_areTypeAndPochetteSelfCreated = true;
    }
}
BDDAlbum* BDDAlbum::RecupererAlbum(const int id)
{
    return new BDDAlbum(id);
}
void BDDAlbum::ajouterBDD()
{
    QString queryStr="INSERT INTO Album VALUES (null,'"+ m_nom+ "','" +QString::number(m_pochette->m_id) + "','" + m_nomFormate +"','" + QString::number(m_annee)+"','"+QString::number(m_type->m_id)+"')";
   QSqlQuery query = madatabase.exec(queryStr);

    m_id=query.lastInsertId().toInt();
}

void BDDAlbum::supprimerenBDD() const
{

    //On vérifie si l'album existe ou non dans la table des relations
    QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Album='"+QString::number(m_id)+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la deuxième requête ne renvoie pas de résultat, on efface du coup l'album
    if (!query2.first()) {

        madatabase.exec("DELETE FROM Album WHERE Id_Album='"+QString::number(m_id)+"'");

    }
m_pochette->supprimerenBDD();
}
