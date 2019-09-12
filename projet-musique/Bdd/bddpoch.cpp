#include "bddpoch.h"
#include <QImage>
#include <QtSql>
#include "bddsingleton.h"
#include "util.h"


QString BDDPoch::creerchemin( const QString& album, const QString& artiste )
{


    QString artisteFormate( artiste );
    QString albumFormate( album );
      FormaterEntiteBDD( artisteFormate );
    if ( artisteFormate == "artistesdivers")
    {
        artisteFormate = "Compil";
    }
    FormaterEntiteBDD( albumFormate );

    return "./pochettes/" + artisteFormate + "/" + albumFormate + ".jpg";
}


QList<int> BDDPoch::pochettesparart(const QString &artiste)
{
    QList<int> listepoch;

    QString queryStr = " Select DISTINCT A.Id_Pochette As 'Poch' from Relations R, Album A WHERE R.Id_Artiste='" + artiste + "' AND A.Id_Album = R.Id_Album ";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();

        listepoch << rec.value("Poch").toInt();
    }

    return listepoch;
}

void BDDPoch::sauverImage() const
{
    QDir dossier;
    QDir toCreate( QFileInfo( m_chemin ).dir() );
    dossier.mkdir( toCreate.path() );
    QImage temp = m_image.scaled( 250,250 );
    temp.save( m_chemin );
}

BDDPoch::~BDDPoch()
{

}

void BDDPoch::updateBDD()
{
    sauverImage();
    if (id() == -1)
    {
        QString queryStr = "INSERT INTO Pochette VALUES (null,'" + m_chemin + "')";
        QSqlQuery query = madatabase.exec( queryStr );
        setId(query.lastInsertId().toInt());
    }
    else
    {
        QString queryStr = "UPDATE Pochette SET Chemin = '" + m_chemin + "' WHERE Id_Pochette = '" + QString::number(id()) + "'";
        madatabase.exec(queryStr);
    }
}

Handle<BDDPoch> BDDPoch::recupererBDD(const int id)
{
    QString queryStr = "SELECT Chemin FROM Pochette WHERE Id_Pochette='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    QString chemin;
    QImage image;
    if (query.first())
    {
        QSqlRecord rec = query.record();

        chemin = rec.value("Chemin").toString();
        image.load(chemin);
    }
    return Handle<BDDPoch>(new BDDPoch(id, image, chemin));
}

Handle<BDDPoch> BDDPoch::recupererBDD(const QImage &image, const QString &album, const QString &artiste)
{
    QString albumFormate(album);
    QString artisteFormate(artiste);
    FormaterEntiteBDD(albumFormate);
    FormaterEntiteBDD(artisteFormate);
    QString chemin(creerchemin(album, artiste));

    QString queryStr = " Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='" + chemin + "'";
    QSqlQuery query = madatabase.exec( queryStr );

    int id = -1;

    if (query.first())
    {
        QSqlRecord rec = query.record();
        id = rec.value("Poch").toInt();
    }
    return Handle<BDDPoch>(new BDDPoch(id, image, chemin));
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
