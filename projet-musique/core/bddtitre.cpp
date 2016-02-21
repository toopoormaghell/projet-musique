#include "bddtitre.h"
#include "bddsingleton.h"
#include "util.h"
#include <QtSql>
#include <QDebug>
#include "bddartiste.h"
#include "bddalbum.h"

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

void BDDTitre::supprimerenBDD() const
{
    QString queryStr="SELECT Id_Relation from Relations WHERE Id_Titre='"+QString::number(m_id)+"'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( !query.first() )
    {
        madatabase.exec("DELETE FROM Titre WHERE Id_Titre='"+QString::number(m_id)+"'");
    }
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
    QString queryStr = "Select Id_Titre As 'Titre' from Titre WHERE Titre_Formate='" + m_nomFormate+"' AND Num_Piste='"+ QString::number(m_num_piste)+"'" ;

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

void BDDTitre::mp3etphys()
{
    //Première étape: le titre existe ou non en MP3
     QString queryStr="SELECT R.Id_Relation FROM Relations R, MP3 M WHERE R.Id_Titre IN (SELECT Id_Titre FROM Titre WHERE Titre_Formate = '"+m_nomFormate+"') AND R.Id_Artiste IN (SELECT Id_Artiste FROM Relations WHERE Id_Titre IN (SELECT Id_Titre FROM Titre  WHERE Id_Titre = '"+QString::number(m_id)+"')) AND M.Id_Relation = R.Id_Relation";

    QSqlQuery query = madatabase.exec( queryStr );
    if ( query.first() )
    {
       m_mp3= true;
    }

    //Deuxième étape: le titre existe ou non sur album phys
    queryStr=" SELECT R.Id_Relation FROM Relations R, Phys P WHERE R.Id_Titre IN (SELECT Id_Titre FROM Titre WHERE Titre_Formate = '"+m_nomFormate+"') AND R.Id_Artiste IN (SELECT Id_Artiste FROM Relations WHERE Id_Titre IN (SELECT Id_Titre FROM Titre  WHERE Id_Titre = '"+QString::number(m_id)+"')) AND P.Id_Album = R.Id_Album ";

    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        m_phys = true;
    }
}

BDDTitre::BDDTitre(const int id, QObject *parent):
    QObject(parent),
    m_id(id),
    m_nom(),
    m_nomFormate(),
    m_num_piste(-1),
    m_duree(),
    m_mp3(false),
    m_phys(false),
    m_artiste(),
    m_album()
{
    QString queryStr="SELECT Titre,Num_Piste,Duree, Titre_Formate, R.Id_Artiste, R.Id_Album FROM Titre T,Relations R WHERE T.Id_Titre='"+QString::number(id)+"' AND R.Id_Titre=T.Id_Titre";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        m_nom= rec.value( "Titre" ).toString().replace("$","'");
        m_nomFormate = rec.value( "Titre_Formate" ).toString();
        m_num_piste=rec.value("Num_Piste").toInt();
        m_duree=rec.value("Duree").toString();
        m_artiste = BDDArtiste::RecupererArtiste(rec.value("Id_Artiste").toInt());
        m_album = BDDAlbum::RecupererAlbum(rec.value("Id_Album").toInt());
        mp3etphys();

    }
}
QList<int> BDDTitre::Similaires(const int id)
{
    QList<int> listeSimilaires;
    BDDTitre* titre= RecupererTitre(id);

    QString queryStr="SELECT M.Id_MP3 FROM Titre T,MP3 M, Relations R WHERE T.Id_Titre!='"+QString::number(id)+"' AND T.Titre_Formate LIKE '%"+titre->m_nomFormate+"%' AND T.Id_Titre=R.Id_Titre AND R.Id_Relation = M.Id_Relation";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        listeSimilaires << rec.value("Id_MP3").toInt();
    }
    return listeSimilaires;
}
