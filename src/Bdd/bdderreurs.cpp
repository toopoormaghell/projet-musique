#include "bdderreurs.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddpoch.h"


BDDErreurs::BDDErreurs(QObject *parent) : QObject(parent),
    m_outils( new OutilsBDD )
{

}

BDDErreurs::~BDDErreurs()
{
    delete m_outils;
}

QList<int> BDDErreurs::retrouverErreurs(int categorie)
{
    switch ( categorie )
    {
    case 1 : return retrouvererreursRelations(); break;
    case 2 : return retrouvererreursAlbums(); break;
    case 3 : return retrouvererreursArtistes(); break;
    case 4 : return retrouvererreursTitres(); break;
    case 5 : return retrouvererreursPoch();break;
    case 6 : return retrouvererreursPhys();break;
    case 7 : return retrouvererreursMP3();break;
    default: return retrouvererreursRelations();
    }
}
QList<int> BDDErreurs::retrouvererreursRelations()
{
    QList<int> liste;

    QString queryStr = "SELECT DISTINCT Id_Relation FROM Relations WHERE Id_Album='0' OR Id_Artiste='0' OR Id_Titre='0' UNION SELECT DISTINCT Id_Relation FROM Relations WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Phys) AND Id_Relation NOT IN ( SELECT DISTINCT Id_Relation FROM MP3) UNION SELECT DISTINCT Id_Relation FROM Relations WHERE MP3 =0 AND Phys = 0 UNION SELECT DISTINCT Id_Relation FROM Relations WHERE Id_Album NOT IN (SELECT DISTINCT Id_Album FROM Album) OR Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Artiste) OR Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Titre)  ";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        int temp = rec.value("Id_Relation").toInt();

        liste << temp;

    }
    return liste;
}

QList<int> BDDErreurs::retrouvererreursTitres()
{
    QList<int> liste;

    QString queryStr = "SELECT distinct Id_Titre FROM Titre WHERE Titre_Formate ='' UNION SELECT distinct Id_Titre FROM Titre WHERE Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Relations )";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        int temp = rec.value("Id_Titre").toInt();

        liste << temp;

    }
    return liste;
}

QList<int> BDDErreurs::retrouvererreursPoch()
{
    QList<int> liste;

    QString queryStr = "SELECT distinct Id_Pochette FROM Pochette WHERE  Chemin ='' UNION SELECT Id_Pochette FROM Pochette WHERE Id_Pochette !=1 AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Artiste ) AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Album)";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        int temp = rec.value("Id_Pochette").toInt();

        liste << temp;

    }
    return liste;
}

QList<int> BDDErreurs::retrouvererreursPhys()
{
    QList<int> liste;

    QString queryStr = "SELECT distinct Id_Phys FROM Phys WHERE  Id_Album ='' UNION SELECT distinct Id_Phys FROM Phys  WHERE Id_Album NOT IN (SELECT  Id_Album FROM Relations)";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        int temp = rec.value("Id_Phys").toInt();

        liste << temp;

    }
    return liste;
}

QList<int> BDDErreurs::retrouvererreursMP3()
{
    QList<int> liste;

    QString queryStr = "SELECT distinct Id_MP3 FROM MP3 WHERE Id_Relation='' OR Chemin = '' UNION SELECT distinct Id_MP3 FROM MP3 WHERE Id_Relation NOT IN (SELECT DISTINCT Id_Relation FROM Relations)";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        int temp = rec.value("Id_MP3").toInt();

        liste << temp;

    }
    return liste;
}

QList<int> BDDErreurs::retrouvererreursAlbums()
{
    QList<int> liste;

    QString queryStr = "SELECT DISTINCT Id_Album FROM Album WHERE Id_Artiste = 0 OR Id_Pochette = 0 OR Album_Formate = '' OR Annee ='' Or Type='' UNION SELECT DISTINCT Id_Album FROM Album WHERE Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Relations ) ";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        int temp = rec.value("Id_Album").toInt();

        liste << temp;

    }
    return liste;
}

QList<int> BDDErreurs::retrouvererreursArtistes()
{
    QList<int> liste;

    QString queryStr = "SELECT DISTINCT Id_Artiste FROM Artiste WHERE Id_Pochette = 0 OR Artiste_Formate = '' UNION SELECT DISTINCT Id_Artiste FROM Artiste WHERE Id_Artiste !='01' AND Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Relations ) ";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        int temp = rec.value("Id_Artiste").toInt();

        liste << temp;

    }
    return liste;
}
QStringList BDDErreurs::lectureErreur( int categorie, int id )
{
    switch ( categorie )
    {
    case 1 : return lectureErreurRelation( id ); break;
    case 2 : return lectureErreurAlbum( id ); break;
    case 3 : return lectureErreurArtiste( id ); break;
    case 4 : return lectureErreurTitre( id ); break;
    case 5 : return lectureErreurPochette( id );break;
    case 6 : return lectureErreurPhys( id );break;
    case 7 : return lectureErreurMP3( id );break;
    default: return lectureErreurRelation( id );
    }
}
QStringList BDDErreurs::lectureErreurRelation ( int id )
{
    QStringList liste;

    QString queryStr = "SELECT * FROM Relations WHERE Id_Relation='"+  QString::number( id ) +"' ";
    QSqlQuery query = madatabase.exec( queryStr );
    for (int i =0 ; i < 11 ; i++ )
    {
        liste << "<font color='blue'>Vide.</font>";
    }
    liste[0] = QString::number( id );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[1] = rec.value("Id_Album").toString();
        liste[2] = rec.value("Id_Artiste").toString();
        liste[3] = rec.value("Id_Titre").toString();
        liste[4] = rec.value("Num_Piste").toString();
        liste[5] = rec.value("Duree").toString();
        liste[6] = rec.value("MP3").toString();
        liste[7] = rec.value("Phys").toString();
    }
    queryStr = "SELECT * FROM Relations WHERE Id_Relation='"+  QString::number( id ) +"' AND Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Phys) AND Id_Relation NOT IN ( SELECT DISTINCT Id_Relation FROM MP3) ";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[8] =  "<font color='blue'>Oui</font>";
    } else
    {
        liste[8] =  "non";
    }
    queryStr = "SELECT Id_Phys FROM Phys WHERE Id_Album='"+  liste[1] +"'";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[9] = query.record().value("Id_Phys").toString();
    }
    queryStr = "SELECT Id_MP3 FROM MP3 WHERE Id_Relation='"+  QString::number( id ) +"' ";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[10] = query.record().value("Id_MP3").toString();
    }
    return liste;
}
QStringList BDDErreurs::lectureErreurAlbum ( int id )
{
    QStringList liste;
    for (int i =0 ; i < 9 ; i++ )
    {
        liste << "<font color='blue'>Vide.</font>";
    }
    QString queryStr = "SELECT * FROM Album WHERE Id_Album='"+  QString::number( id ) +"' ";
    QSqlQuery query = madatabase.exec( queryStr );
    liste[0] = QString::number( id );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[1] = rec.value("Album").toString();
        liste[2] = rec.value("Album_Formate").toString();
        liste[3] = rec.value("Id_Pochette").toString();
        liste[4] = rec.value("Annee").toString();
        liste[5] = rec.value("Type").toString();
        liste[6] = rec.value("Id_Artiste").toString();
    }
    queryStr = "SELECT * FROM Album WHERE Id_Album='"+  QString::number( id ) +"' AND Id_Album NOT IN ( SELECT DISTINCT Id_Album FROM Relations )";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[7] = "<font color='blue'>Oui</font>";
    } else
    {
        liste[7] = "non";
    }
    queryStr = "SELECT Id_Phys FROM Phys WHERE Id_Album='"+  QString::number( id )+"'";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[8] = rec.value("Id_Phys").toString();
    }


    return liste;
}
QStringList BDDErreurs::lectureErreurArtiste ( int id )
{
    QStringList liste;

    QString queryStr = "SELECT * FROM Artiste WHERE Id_Artiste='"+  QString::number( id ) +"' ";
    QSqlQuery query = madatabase.exec( queryStr );
    for (int i =0 ; i < 5 ; i++ )
    {
        liste << "<font color='blue'>Vide.</font>";
    }
    liste[0] = QString::number( id );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[1] = rec.value("Artiste").toString();
        liste[2] = rec.value("Artiste_Formate").toString();
        liste[3] = rec.value("Id_Pochette").toString();
    }

    queryStr = "SELECT * FROM Artiste WHERE Id_Artiste='"+  QString::number( id ) +"' AND Id_Artiste !='01' AND Id_Artiste NOT IN ( SELECT DISTINCT Id_Artiste FROM Relations ) ";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[4] = "<font color='blue'>Oui</font>";
    } else
    {
        liste[4] = "non";
    }
    return liste;
}
QStringList BDDErreurs::lectureErreurTitre ( int id )
{
    QStringList liste;
    for (int i =0 ; i < 4 ; i++ )
    {
        liste << "<font color='blue'>Vide.</font>";
    }
    QString queryStr = "SELECT * FROM Titre WHERE Id_Titre='"+  QString::number( id ) +"' ";
    QSqlQuery query = madatabase.exec( queryStr );

    liste[0] = QString::number( id );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[1] = rec.value("Titre").toString();
        liste[2] = rec.value("Titre_Formate").toString();
    }

    queryStr = "SELECT * FROM Titre WHERE Id_Titre='"+  QString::number( id ) +"' AND Id_Titre NOT IN ( SELECT DISTINCT Id_Titre FROM Relations )";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[3] = "<font color='blue'>Oui</font>";
    } else
    {
        liste[3] = "non";
    }
    return liste;
}

QStringList BDDErreurs::lectureErreurPochette ( int id )
{
    QStringList liste;
    for (int i =0 ; i < 3 ; i++ )
    {
        liste << "<font color='blue'>Vide.</font>";
    }
    QString queryStr = "SELECT * FROM Pochette WHERE Id_Pochette='"+  QString::number( id ) +"' ";
    QSqlQuery query = madatabase.exec( queryStr );
    liste[0] = QString::number( id );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[1] = rec.value("Chemin").toString();
    }
    queryStr = "SELECT Id_Pochette FROM Pochette WHERE Id_Pochette !=1 AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Artiste ) AND Id_Pochette NOT IN ( SELECT DISTINCT Id_Pochette FROM Album) AND Id_Pochette ='"+  QString::number( id ) +"'";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[2] = "<font color='blue'>Oui</font>";
    } else
    {
        liste[2] = "non";
    }
    return liste;
}

QStringList BDDErreurs::lectureErreurMP3 ( int id )
{
    QStringList liste;
    for (int i =0 ; i < 5 ; i++ )
    {
        liste << "<font color='blue'>Vide.</font>";
    }
    QString queryStr = "SELECT * FROM MP3 WHERE Id_Mp3='"+  QString::number( id ) +"' ";
    QSqlQuery query = madatabase.exec( queryStr );
    liste[0] = QString::number( id );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[1] = rec.value("Id_Relation").toString();
        liste[2] = rec.value("Chemin").toString();
        liste[3] = rec.value("Support").toString();
    }
    queryStr = "SELECT distinct Id_Relation FROM MP3  WHERE Id_Relation NOT IN (SELECT DISTINCT Id_Relation FROM Relations) AND Id_MP3 ='"+  QString::number( id ) +"' ";

    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[4] = "<font color='blue'>Oui</font>";
    } else
    {
        liste[4] = "non";
    }
    return liste;
}

QStringList BDDErreurs::lectureErreurPhys ( int id )
{
    QStringList liste;
    for (int i =0 ; i < 6 ; i++ )
    {
        liste << "<font color='blue'>Vide.</font>";
    }
    QString queryStr = "SELECT * FROM Phys WHERE Id_Phys='"+  QString::number( id ) +"' ";
    QSqlQuery query = madatabase.exec( queryStr );
    liste[0] = QString::number( id );
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        liste[1] = rec.value("Id_Album").toString();
        liste[2] = rec.value("Support").toString();
        liste[3] = rec.value("CodeBarres").toString();
        liste[4] = rec.value("Commentaire").toString();
    }
    queryStr = "SELECT distinct Id_Album FROM Phys  WHERE Id_Album NOT IN (SELECT  Id_Album FROM Relations) AND Id_Phys ='"+  QString::number( id ) +"' ";
    query = madatabase.exec( queryStr );
    if ( query.first() )
    {
        liste[5] = "<font color='blue'>Oui</font>";
    } else
    {
        liste[5] = "non";
    }

    return liste;
}
void BDDErreurs::supprimer( int categorie, int id )
{
    switch ( categorie )
    {
    case 1 : return supprimerRelation( id ); break;
    case 2 : return supprimerAlbum( id ); break;
    case 3 : return supprimerArtiste( id ); break;
    case 4 : return supprimerTitre( id ); break;
    case 5 : return supprimerPoch( id );break;
    case 6 : return supprimerPhys( id );break;
    case 7 : return supprimerMP3( id );break;
    default: return supprimerRelation( id );
    }
}
void BDDErreurs::supprimerPoch ( int id )
{
    QString   queryStr = "SELECT Id_Pochette, Chemin FROM Pochette WHERE Id_Pochette='"+  QString::number( id ) +"'";
    QSqlQuery  query = madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString chemin = rec.value("Chemin").toString();
        QFile::remove( chemin );
        madatabase.exec("DELETE FROM Pochette WHERE Id_Pochette='"+  QString::number( id ) +"'");
    }
}
void BDDErreurs::supprimerRelation ( int id )
{
    madatabase.exec("DELETE FROM Relations WHERE Id_Relation='"+  QString::number( id ) +"'");

}
void BDDErreurs::supprimerAlbum ( int id )
{
    madatabase.exec("DELETE FROM Album WHERE Id_Album='"+  QString::number( id ) +"'");

}
void BDDErreurs::supprimerArtiste ( int id )
{
    madatabase.exec("DELETE FROM Artiste WHERE Id_Artiste='"+  QString::number( id ) +"'");
}
void BDDErreurs::supprimerTitre ( int id )
{
    madatabase.exec("DELETE FROM Titre WHERE Id_Titre='"+  QString::number( id ) +"'");
}
void BDDErreurs::supprimerMP3 ( int id )
{
    madatabase.exec("DELETE FROM MP3 WHERE Id_MP3='"+  QString::number( id ) +"'");
}
void BDDErreurs::supprimerPhys ( int id )
{
    madatabase.exec("DELETE FROM Phys WHERE Id_Phys='"+  QString::number( id ) +"'");
}
QImage BDDErreurs::AfficherImagePoch( int id )
{
    Handle<BDDPoch> poch = BDDPoch::recupererBDD( id );
    QImage temp = poch->m_image;
    return temp;
}
