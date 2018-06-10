#include "bddalbum.h"
#include "bddpoch.h"
#include "util.h"
#include "bddsingleton.h"
#include <QtSql>
#include "bddtype.h"
#include "bddartiste.h"
#include "bddtitre.h"


BDDAlbum::~BDDAlbum()
{

    delete m_artiste;
    delete m_type;
    delete m_pochette;

}

int BDDAlbum::recupererId(const QString& nomFormate, const QString& id_Artiste)
{
    QString queryStr = "Select Id_Album As 'Album' from Album WHERE Album_Formate='" + nomFormate + "' AND Id_Artiste='" + id_Artiste + "'" ;
    QSqlQuery query = madatabase.exec( queryStr );

    int id = -1;
    if ( query.first() )
    {
        QSqlRecord rec = query.record();
        id = (rec.value( "Album" ).toInt());
    }
    return id;
}


void BDDAlbum::updateBDD()
{
    m_pochette->updateBDD();

    if ( id() ==-1 )
    {
        QString queryStr = "INSERT INTO Album VALUES (null,'" + m_nom + "','" + QString::number( m_pochette->id() ) + "','" + m_nomFormate + "','" + QString::number( m_annee ) + "','" + QString::number( m_type->id() ) + "','" + QString::number( m_artiste->id() )+ "')";
        QSqlQuery query = madatabase.exec( queryStr );

        setId(query.lastInsertId().toInt());
    }
    else
    {
        QString queryStr = "UPDATE Album SET Album_Formate ='" + m_nomFormate + "', Id_Pochette='" + QString::number( m_pochette->id() ) + "', Annee= '" + QString::number( m_annee ) + "', Id_Artiste= '" + QString::number( m_artiste->id() ) + "'  WHERE Id_Album = '" + QString::number( id() ) + "'";
        QSqlQuery madatabase.exec( queryStr );
    }

}

BDDAlbum* BDDAlbum::recupererBDD(const int id)
{
    QString queryStr = "SELECT Album, Album_Formate, Id_Pochette, Annee, Type, Id_Artiste FROM Album WHERE Id_Album='" + QString::number(id) + "'";
    QSqlQuery query = madatabase.exec(queryStr);

    QString nom, nomFormate;
    int Annee=0;
    BDDPoch* pochette = nullptr;
    BDDArtiste* art = nullptr;
    BDDType* type = nullptr;

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        nom = rec.value("Album").toString().replace("$", "'");
        pochette = BDDPoch::recupererBDD(rec.value("Id_Pochette").toInt());
        nomFormate = rec.value("Album_Formate").toString();
        Annee = rec.value("Annee").toInt();
        type = BDDType::RecupererType(rec.value("Type").toInt());
        art = BDDArtiste::recupererBDD(rec.value("Id_artiste").toInt());

    }

    return new BDDAlbum(id,nom,nomFormate,pochette,Annee,type,art );
}
BDDAlbum::BDDAlbum(const int id, const QString& nom, const QString& nomFormate, BDDPoch* pochette, int annee, const BDDType* type, const BDDArtiste* artiste, QObject* parent):
    IdOwner( id,parent )
  , m_nom( nom )
  , m_nomFormate (nomFormate)
  , m_pochette ( pochette )
  , m_annee ( annee )
  , m_type ( type )
  , m_artiste ( artiste )
{

}

void BDDAlbum::supprimerenBDD() const
{
    if ( id() != -1 )
    {

        //On vérifie si l'album existe ou non dans la table des relations
        QString queryStri =  "Select Id_Relation As 'Relation' from Relations WHERE Id_Album='" + QString::number( id() ) + "'" ;
        QSqlQuery  query2 = madatabase.exec( queryStri );

        //si la deuxième requête ne renvoie pas de résultat, on efface du coup l'album
        if ( !query2.first() )
        {

            madatabase.exec( "DELETE FROM Album WHERE Id_Album='" + QString::number( id() ) + "'" );

        }

        m_pochette->supprimerenBDD();
        m_artiste->supprimerenBDD();
    }
}
int BDDAlbum::TrouverId(const QString &nom, const int &id_Artiste)
{
    QString nomFormate = nom;
    FormaterEntiteBDD( nomFormate );
    return recupererId( nomFormate,QString::number( id_Artiste ) );

}


BDDAlbum* BDDAlbum::recupererBDD(const QString& album, BDDPoch &pochette, int annee, const BDDType& type, const BDDArtiste& artiste)
{
    QString nom (album );
    EnleverAccents (nom );
    MajusuculeAChaqueMot ( nom );
    QString nomFormate( nom );
    FormaterEntiteBDD( nomFormate );

    const int id = TrouverId(nom, artiste.id() );

    return new BDDAlbum( id,nom,nomFormate,&pochette,annee,&type,&artiste );
}

AlbumPhys BDDAlbum::RecupAlbumEntite( const int id )
{
    AlbumPhys albphys;

    //On récupère les infos liées à l'album
    BDDAlbum* alb = BDDAlbum::recupererBDD( id );
    albphys.Album = alb->m_nom;
    albphys.Annee = alb->m_annee;
    albphys.Id_Album = alb->id();
    albphys.Poch = alb->m_pochette->m_image;
    albphys.Id_Poch = alb->m_pochette->id();
    albphys.Type = alb->m_type->id();
    albphys.Artiste = alb->m_artiste->m_nom;

    delete alb;

    //On récupère les titres liés à l'album
    QString queryStr = "SELECT DISTINCT R.Id_Titre, R.Duree, R.Num_Piste, R.MP3, R.Phys,  R.Id_Artiste FROM Relations R, Titre T WHERE R.Id_Album='" + QString::number( id ) + "' AND T.Id_Titre=R.Id_Titre ORDER BY Num_Piste";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        TitresPhys titre;
        QSqlRecord rec = query.record();
        BDDTitre*  TitreEnCours = BDDTitre::recupererBDD( rec.value( "Id_Titre" ).toInt() );
        BDDArtiste* art = BDDArtiste::recupererBDD(rec.value( "Id_Artiste" ).toInt());

        titre.Artiste = art->m_nom;
        titre.Duree = rec.value( "Duree" ).toString();
        titre.id = QString::number( TitreEnCours->id() ) ;
        titre.Num_Piste = rec.value( "Num_Piste" ).toInt();
        titre.Titre = TitreEnCours->m_nom;
        titre.MP3Phys = rec.value("MP3").toBool() && rec.value("Phys").toBool();
        titre.MP3 = rec.value("MP3").toBool();
        titre.Phys = rec.value("Phys").toBool();

        albphys.titres << titre;
        delete TitreEnCours;
        delete art;

    }
    return albphys;
}

bool BDDAlbum::ExisteEnPhys(const int id)
{
    //On récupère les titres liés à l'album
    QString queryStr = "SELECT * FROM Phys WHERE Id_Album ='"+ QString::number( id )+"'";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        return true;
    }
    return false;
}
