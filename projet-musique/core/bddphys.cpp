#include "bddphys.h"
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddartiste.h"
#include "bddtitre.h"
#include "bddtype.h"
#include "bddrelation.h"
#include <QtSql>


BDDPhys::BDDPhys(const BDDAlbum& album, const QString& ean, const BDDType& type, const QString& Commentaires, QObject* parent):
    IdOwner(-1, parent)
  , m_album(&album)
  , m_type(&type)
  , m_ean(ean)
  , m_commentaires(Commentaires)
  , m_membersAreSelfCreatad(false)
{
    recupererId();
    if (m_id == -1)
        ajouterBDD();
    else
        updateBDD();
}

BDDPhys::~BDDPhys()
{
    if (m_membersAreSelfCreatad)
    {
        delete m_type;
        delete m_album;
    }
}

void BDDPhys::deleteBDD()
{
    QString queryStr = "DELETE FROM Phys WHERE Id_Album='" + QString::number( m_id ) + "'";

    madatabase.exec( queryStr );

    m_album->supprimerenBDD();
}

BDDPhys* BDDPhys::RecupererPhys( const int id )
{
    return new BDDPhys( id );
}

void BDDPhys::ajouterBDD()
{
    QString queryStr = "INSERT INTO Phys VALUES (null,'" + QString::number( m_album->m_id ) + "','" + QString::number( m_type->m_id ) + "','" + m_ean + "','" + m_commentaires + "')";
    QSqlQuery query =  madatabase.exec( queryStr );
    m_id = query.lastInsertId().toInt();
}

void BDDPhys::recupererId()
{
    QString queryStr = "Select Id_Phys As 'Phys' from Phys WHERE Id_Album='" + QString::number( m_album->m_id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( " Id_Phys " ).toInt();

    }
    else
    {
        m_id = -1;
    }
}

BDDPhys::BDDPhys(const int id, QObject* parent):
    IdOwner(id, parent)
  , m_album(NULL)
  , m_type(NULL)
  , m_ean(-1)
  , m_commentaires()
  , m_membersAreSelfCreatad(false)
{
    QString queryStr = "SELECT * FROM Phys WHERE Id_Album='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);
    if (query.first())
    {
        QSqlRecord rec = query.record();

        m_album = BDDAlbum::RecupererAlbum(rec.value("Id_Album").toInt());
        m_type = BDDType::RecupererType(rec.value("Categorie").toInt());
        m_ean = rec.value("EAN").toString();
        m_commentaires = rec.value("Commentaire").toString();
        m_membersAreSelfCreatad = true;
    }
}

void BDDPhys::updateBDD()
{

    QString queryStr = "UPDATE Phys SET CodeBarres = '" + m_ean + "', Commentaire = '" + m_commentaires + "', Categorie = '"+ QString::number( m_type->m_id ) +"' WHERE Id_Album ='" + QString::number(m_album->m_id ) +"' ";
    madatabase.exec( queryStr );

}
