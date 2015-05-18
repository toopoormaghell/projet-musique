#include "bddtitre.h"
#include "bddsingleton.h"
#include "util.h"
#include <QtSql>

BDDTitre::BDDTitre(const QString &nom, const int &num_piste, const QString &duree, QObject *parent) :
    QObject(parent),
    m_id(-1),
    m_nom(nom),
    m_nomFormate(nom),
    m_num_piste(num_piste),
    m_duree(duree)
{
    FormaterEntiteBDD(m_nomFormate);
    recupererId();
    if (m_id==-1)
    {
        ajouterBDD();
    } else
    {
        updateBDD();
    }
}

void BDDTitre::updateBDD()
{

}

void BDDTitre::deleteBDD()
{

}

BDDTitre *BDDTitre::RecupererTitre(const int id)
{
    return new BDDTitre(id);
}

void BDDTitre::ajouterBDD()
{
    QString queryStr="INSERT INTO Titre VALUES (null,'"+ m_nom+ "','"+QString::number(m_num_piste) +"','"+ m_nomFormate+"','"+ m_duree +"')";

     QSqlQuery query=  madatabase.exec(queryStr);

         m_id= query.lastInsertId().toInt();
}

void BDDTitre::recupererId()
{
    QString queryStr = "Select Id_Titre As 'Titre' from Titre WHERE TitreSSAccents='" + m_nomFormate+"' AND Duree='"+m_duree+"' AND Num_Piste='"+ QString::number(m_num_piste)+"'" ;

    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Titre" ).toInt();

    } else
    {
        m_id = -1;
    }
}

BDDTitre::BDDTitre(const int id, QObject *parent):
    QObject(parent),
    m_id(id),
    m_nom(),
    m_nomFormate(),
    m_num_piste(-1),
    m_duree()
{
    QString queryStr="SELECT Titre,Num_Piste,Duree, TitreSSAccents FROM Titre WHERE Id_Titre='"+QString::number(id)+"'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        m_nom= rec.value( "Titre" ).toString().replace("$","'");
        m_nomFormate = rec.value( "TitreSSAccents" ).toString();
        m_num_piste=rec.value("Num_Piste").toInt();
        m_duree=rec.value("Duree").toString();

    }
}
