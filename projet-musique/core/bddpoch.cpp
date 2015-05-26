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
    m_chemin=creerchemin(album,artiste);

    recupererId();

    if(m_id==-1)
    {
        sauverImage(albumFormate,artisteFormate);
        ajouterBDD();
    }
}

BDDPoch::~BDDPoch()
{
}
QString BDDPoch::creerchemin(const QString& album,const QString& artiste)
{

    QString artisteFormate( artiste );
    QString albumFormate( album );
    FormaterEntiteBDD(artisteFormate);
    FormaterEntiteBDD(albumFormate);

    return "./pochettes/"+artisteFormate+"/"+albumFormate+".jpg";
}

void BDDPoch::sauverImage(const QString &album, const QString &artiste)
{
    QDir dossier;
    QString chemin="./pochettes/"+artiste;
    dossier.mkdir(chemin);
    chemin+="/"+album+".jpg";
    m_image.save(chemin);
}
void BDDPoch::recupererId()
{
    QString queryStr =" Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='"+m_chemin+"'";
    QSqlQuery query=madatabase.exec(queryStr);

    if(query.first()) {
        QSqlRecord rec = query.record();
        m_id= rec.value( "Poch" ).toInt();

    } else {
        m_id=-1;
    }
}
void BDDPoch::ajouterBDD()
{
    QString queryStr="INSERT INTO Pochette VALUES (null,'" + m_chemin+"')";
    QSqlQuery query=madatabase.exec(queryStr);

    m_id= query.lastInsertId().toInt();
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
    QString chemin = creerchemin(album,artiste);

    QString queryStr =" Select Id_Pochette As 'Poch' from Pochette WHERE Chemin='"+chemin+"'";
    QSqlQuery query=madatabase.exec(queryStr);

    if(query.first()) {

        QSqlRecord rec = query.record();
        int id= rec.value( "Poch" ).toInt();
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

/*
void BDDPoch::supprimerPochette(const int &IdPoch, const QString Chemin_Album)
{
    //On vérifie si l'artiste existe ou non dans la table des relations
    QString queryStri =  "Select Id_Artiste from Artiste WHERE Id_Pochette='"+QString::number(IdPoch)+"'" ;
    QSqlQuery  query2 = madatabase.exec(queryStri);

    //si la requête ne renvoie pas de résultat, on efface du coup la pochette
    if (!query2.first()) {

        queryStri =  "DELETE FROM Pochette WHERE Id_Pochette='"+QString::number(IdPoch)+"'";
        madatabase.exec(queryStri);

        QFile::remove(Chemin_Album);

    } else {

        QSqlRecord rec= query2.record();

        QString Id_Artiste = rec.value("Id_Artiste").toString();
        queryStri = "SELECT Id_Pochette from Relations WHERE Id_Artiste='"+Id_Artiste+"'";
        QSqlQuery query= madatabase.exec(queryStri);

        if (query.first())
        {
            QSqlRecord rec2=query.record();
            QString Id_Poch=rec2.value("Id_Pochette").toString();
            query2=madatabase.exec("UPDATE Artiste SET Id_Pochette='"+Id_Poch+"' WHERE Id_Artiste='"+Id_Artiste+"'");

        }
        queryStri =  "DELETE FROM Pochette WHERE Id_Pochette='"+QString::number(IdPoch)+"'";
        madatabase.exec(queryStri);

        QFile::remove(Chemin_Album);


    }
}
*/
