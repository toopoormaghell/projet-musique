#include "bddpoch.h"
#include <QImage>
#include <QtSql>
#include "bddsingleton.h"
#include "util.h"

BDDPoch::BDDPoch(const QImage& image, const QString& album, const QString& artiste, QObject* parent):
    IdOwner(-1, parent)
  , m_image(image)
  , m_chemin()
{
    QString artisteFormate(artiste);
    QString albumFormate(album);
    FormaterEntiteBDD(artisteFormate);
    FormaterEntiteBDD(albumFormate);
    m_chemin = creerchemin(album, artiste);

    recupererId();

    if (id() == -1)
    {
        sauverImage(albumFormate, artisteFormate);
        ajouterBDD();
    }
    else
    {
        updateBDD();
    }
}

QString BDDPoch::creerchemin( const QString& album, const QString& artiste )
{

    QString artisteFormate( artiste );
    QString albumFormate( album );
    FormaterEntiteBDD( artisteFormate );
    FormaterEntiteBDD( albumFormate );

    return "./pochettes/" + artisteFormate + "/" + albumFormate + ".jpg";
}

QList<int> BDDPoch::pochettesparart(const QString &artiste)
{
    QList<int> listepoch;

    QString queryStr = " Select DISTINCT Id_Pochette As 'Poch' from Relations R, Album A WHERE R.Id_Artiste='" + artiste + "' AND A.Id_Album = R.Id_Album UNION SELECT Id_Pochette AS 'Poch' from Artiste WHERE Id_Artiste = '" + artiste + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        listepoch << rec.value("Poch").toInt();
    }

    return listepoch;
}

void BDDPoch::sauverImage( const QString& album, const QString& artiste )
{
    QDir dossier;
    QString chemin = "./pochettes/" + artiste;
    dossier.mkdir( chemin );
    chemin += "/" + album + ".jpg";
    m_image.save( chemin );
}
void BDDPoch::recupererId()
{
    QString queryStr = " Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='" + m_chemin + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        setId(rec.value( "Poch" ).toInt());

    }
    else
    {
        setId(-1);
    }
}
void BDDPoch::ajouterBDD()
{
    QString queryStr = "INSERT INTO Pochette VALUES (null,'" + m_chemin + "')";
    QSqlQuery query = madatabase.exec( queryStr );

    setId(query.lastInsertId().toInt());
}

void BDDPoch::updateBDD()
{

    madatabase.exec("UPDATE Pochette SET Chemin = '" + m_chemin + "' WHERE Id_Pochette = '" + QString::number(id()) + "'");
}

BDDPoch* BDDPoch::recupererBDD(const int id)
{
    QString queryStr = "SELECT Chemin FROM Pochette WHERE Id_Pochette='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    QString chemin;
    QImage image;
    while (query.next())
    {
        QSqlRecord rec = query.record();

        chemin = rec.value("Chemin").toString();
        image.load(chemin);
    }
    return new BDDPoch(id, image, chemin);
}

BDDPoch::BDDPoch(const int id, const QImage& image, const QString& chemin, QObject* parent):
    IdOwner(id, parent)
  , m_image(image)
  , m_chemin(chemin)
{
}

void BDDPoch::supprimerenBDD() const
{
    if ( id() != -1 )
    {

        //On vérifie si la pochette n'existe plus ni dans l'artiste, ni dans l'album
        QString queryStr = "SELECT Id_Pochette FROM Artiste WHERE Id_Pochette='" + QString::number( id() ) + "' UNION SELECT Id_Pochette FROM Album WHERE Id_Pochette='" + QString::number( id() ) + "'";
        QSqlQuery  query2 = madatabase.exec( queryStr );

        //si la requête ne renvoie pas de résultat, on efface du coup la pochette
        if ( !query2.first() )
        {

            queryStr =  "DELETE FROM Pochette WHERE Id_Pochette='" + QString::number( id() ) + "'";
            madatabase.exec( queryStr );
            QFile::remove( m_chemin );
        }

    }
}
