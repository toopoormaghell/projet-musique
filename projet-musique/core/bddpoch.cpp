#include "bddpoch.h"
#include <QImage>
#include <QtSql>
#include "bddsingleton.h"
#include "util.h"

BDDPoch::BDDPoch( const QImage& image, const QString& album, const QString& artiste, QObject *parent ) :
    QObject(parent),
    m_id(-1),
    m_image(image),
    m_chemin()
{
    QString artisteFormate( artiste );
    QString albumFormate( album );
    FormaterEntiteBDD(artisteFormate);
    FormaterEntiteBDD(albumFormate);
    m_chemin = creerchemin(album, artiste);

    recupererId();

    if(m_id == -1)
    {
        sauverImage(albumFormate, artisteFormate);
        ajouterBDD();
    }
    else
    {
        updateBDD();
    }
}

BDDPoch::~BDDPoch()
{

}
QString BDDPoch::creerchemin(const QString& album, const QString& artiste)
{

    QString artisteFormate( artiste );
    QString albumFormate( album );
    FormaterEntiteBDD(artisteFormate);
    FormaterEntiteBDD(albumFormate);

    return "./pochettes/" + artisteFormate + "/" + albumFormate + ".jpg";
}

void BDDPoch::sauverImage(const QString &album, const QString &artiste)
{
    QDir dossier;
    QString chemin = "./pochettes/" + artiste;
    dossier.mkdir(chemin);
    chemin += "/" + album + ".jpg";
    m_image.save(chemin);
}
void BDDPoch::recupererId()
{
    QString queryStr = " Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='" + m_chemin + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    if(query.first())
    {
        QSqlRecord rec = query.record();
        m_id = rec.value( "Poch" ).toInt();

    }
    else
    {
        m_id = -1;
    }
}
void BDDPoch::ajouterBDD()
{
    QString queryStr = "INSERT INTO Pochette VALUES (null,'" + m_chemin + "')";
    QSqlQuery query = madatabase.exec(queryStr);

    m_id = query.lastInsertId().toInt();
}

void BDDPoch::updateBDD()
{

}

BDDPoch* BDDPoch::recupererBDD(const int id)
{
    return new BDDPoch( id );
}

BDDPoch *BDDPoch::recupererPoch(const QString &album, const QString &artiste)

{
    QString chemin = creerchemin(album, artiste);

    QString queryStr = " Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='" + chemin + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    if(query.first())
    {

        QSqlRecord rec = query.record();
        int id = rec.value( "Poch" ).toInt();
        return recupererBDD(id);
    }
    else
    {
        return NULL;
    }


}


BDDPoch::BDDPoch( const int id, QObject* parent ):
    QObject( parent ),
    m_id( id ),
    m_image( NULL ),
    m_chemin()
{
    QString queryStr = "SELECT Chemin FROM Pochette WHERE Id_Pochette='" + QString::number( id ) + "'";
    QSqlQuery query = madatabase.exec( queryStr );
    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        m_chemin = rec.value( "Chemin" ).toString();
        m_image.load( m_chemin );
    }
}
void BDDPoch::supprimerenBDD() const
{

    //On vérifie si la pochette n'existe plus ni dans l'artiste, ni dans l'album
    QString queryStr = "SELECT Id_Pochette FROM Artiste WHERE Id_Pochette='" + QString::number(m_id) + "' UNION SELECT Id_Pochette FROM Album WHERE Id_Pochette='" + QString::number(m_id) + "'";
    qDebug() << queryStr;
    QSqlQuery  query2 = madatabase.exec(queryStr);

    //si la requête ne renvoie pas de résultat, on efface du coup la pochette
    if (!query2.first())
    {

        queryStr =  "DELETE FROM Pochette WHERE Id_Pochette='" + QString::number(m_id) + "'";
        madatabase.exec(queryStr);
        QFile::remove(m_chemin);
    }

}

