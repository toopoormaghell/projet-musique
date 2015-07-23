#include "bddphys.h"
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddtype.h"
#include "bddrelation.h"
#include <QtSql>


BDDPhys::BDDPhys(const BDDAlbum &album, const QString &ean, const int &type, QObject *parent):
    QObject( parent),
    m_id(-1),
    m_album(&album),
    m_artiste(),
    m_titres(),
    m_type(BDDType::RecupererType(type)),
    m_membersAreSelfCreatad(false),
    m_ean(ean)
{
    recupererId();
    if (m_id==-1)
    {
        ajouterBDD();
    }
}
BDDPhys::~BDDPhys()
{
    if (m_membersAreSelfCreatad)
    {
        m_titres.clear();
        delete m_artiste;
        delete m_album;
        delete m_type;
    }
}

void BDDPhys::deleteBDD()
{


}

BDDPhys *BDDPhys::RecupererPhys(const int id)
{
    return new BDDPhys( id);
}

void BDDPhys::ajouterBDD()
{
    QString queryStr="INSERT INTO Phys VALUES (null,'"+QString::number(m_album->m_id)+"','"+QString::number(m_type->m_id)+"','"+m_ean+"')";
    QSqlQuery query=  madatabase.exec(queryStr);
    m_id = query.lastInsertId().toInt();
}

void BDDPhys::recupererId()
{
    QString queryStr="Select Id_Phys As 'Phys' from Phys WHERE Id_Album='"+QString::number(m_album->m_id)+"'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id=rec.value( " Id_Phys " ).toInt();

    } else
    {
        m_id = -1;
    }
}

BDDPhys::BDDPhys(const int id, QObject *parent):
    m_id(id),
    m_titres(),
    m_artiste(),
    m_album(),
    m_ean(-1),
    m_type()
{
    QString queryStr="SELECT * FROM Phys WHERE Id_Album='"+ QString::number( id)+"'";
    QSqlQuery query= madatabase.exec( queryStr );
    if ( query.first() )
    {
        QSqlRecord rec= query.record();

        m_type = BDDType::RecupererType(rec.value("Categorie").toInt());
        m_album = BDDAlbum::RecupererAlbum(rec.value("Id_Album").toInt());
        RecupererTitres();
        m_membersAreSelfCreatad= true;
    }
}
void BDDPhys::RecupererTitres()
{
    QString queryStr=" SELECT R.Id_Titre, R.Id_Artiste FROM Relations R,Titre T WHERE R.Id_Album='"+ QString::number(m_album->m_id)+"' AND T.Id_Titre=R.Id_Titre ORDER BY T.Num_Piste";
    QSqlQuery query= madatabase.exec( queryStr );
    while (query.next() ) {
        QSqlRecord rec=query.record();

        m_artiste = BDDArtiste::RecupererArtiste(rec.value("Id_Artiste").toInt());
        m_titres <<   BDDTitre::RecupererTitre(rec.value("Id_Titre").toInt());

    }
}
