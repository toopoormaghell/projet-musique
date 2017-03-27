#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include "bddmp3.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddrelation.h"
#include "bddtype.h"
#include "bddconfig.h"
#include "bddsupport.h"
#include <QtSql>
#include <QDir>
#include <QTimer>
#include "tags.h"

BDDGestionMp3::BDDGestionMp3( QObject* parent ) :
    QObject( parent )
  , m_fichierlu()
  , m_pourcentage( 0 )
  , m_filelist()
  , m_Chemins()
  , m_type( 0 )
  , m_iteration( 0 )
  , m_souscat( 0 )
  , m_Categories()
  , m_iterateur()
{

}

void BDDGestionMp3::demarreractualiser()
{

    listeCategoriesActualiser();

    if ( !m_Categories.empty() )
        QTimer::singleShot( 0, this, SLOT( init() ) );
}

void BDDGestionMp3::init()
{
    m_type = m_Categories[0];
    m_Categories.removeFirst();

    m_filelist.clear();
    creerfilefichiers();

    m_iteration = 0;
    QTimer::singleShot( 0, this, SLOT( step() ) );

}

void BDDGestionMp3::step()
{

    m_pourcentage = m_iteration * 100 / m_filelist.count();
    emit pourcentage();
    if ( m_iteration <  m_filelist.count() )
    {
        try
        {
            actualiserMp3( m_filelist[m_iteration] );
        }
        catch ( std::bad_alloc& e )
        {
            qDebug() << e.what();
        }

        ++m_iteration;
        QTimer::singleShot( 0, this, SLOT( step() ) );
    }
    else
    {

        supprimerAnciensMP3();

    }
}

void BDDGestionMp3::stop_clique()
{
    m_iteration = m_filelist.count();
    m_type = m_Categories[m_Categories.count() - 1];
}
void BDDGestionMp3::listeCategoriesActualiser()
{
    BDDConfig temp;
    if ( temp.ActualiserAlbums() )
    {
        m_Categories << 1;
    }
    if ( temp.ActualiserCompil() )
    {
        m_Categories << 2;
    }
    if ( temp.ActualiserLives() )
    {
        m_Categories << 3;
    }

}
QString BDDGestionMp3::dossiercategorie()
{
    switch ( m_type )
    {
    case ( 1 ):
        return getdossierpardef();
        break;
    case ( 2 ):
        return "F:/Compil";
        break;
    case ( 3 ):
        return "F:/Live";
        break;
    default:
        return "";
        break;
    }
}
void BDDGestionMp3::creerfilefichiers()
{

    //Première étape: on met en QMap les chemins des MP3
    //Sous la forme de Id_Mp3 (en clé) et Chemin (en valeurs)
    recupererMp3( m_type );


    QString selectDir = dossiercategorie();


    // On remplit une QStringList avec chacun des filtres désirés ici "*.mp3" .
    QStringList listFilter;
    listFilter << "*.mp3";

    // On déclare un QDirIterator dans lequel on indique que l'on souhaite parcourir un répertoire et ses sous-répertoires.
    // De plus, on spécifie le filtre qui nous permettra de récupérer uniquement les fichiers du type souhaité.
    QDirIterator dirIterator( selectDir, listFilter , QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories );


    // Tant qu'on n'est pas arrivé à la fin de l'arborescence...
    while ( dirIterator.hasNext() )
    {
        // ...on va au prochain fichier correspondant à notre filtre
        m_filelist << dirIterator.next();
    }
}

void BDDGestionMp3::actualiserMp3( QString chemin )
{
    m_fichierlu = chemin;

    m_souscat = m_type;

    Tags fich ( chemin );

    //On récupère l'artiste, l'album, le titre et le numéro de piste
    QString artist = fich.getArtist();
    QString album =  fich.getAlbum();
    int date = fich.getYear();
    QString title =  fich.getTitle();
    int track = fich.getTrack();

    int dureesec = fich.getDuree();
    int min = dureesec / 60;
    int sec = dureesec % 60;
    SousCatParChemin( chemin );


    //On ajoute en BDD

    BDDPoch poch( fich.getPoch() ,  album.replace( "'", "$" ),  artist.replace( "'", "$" ) );
    BDDPoch* def = BDDPoch::recupererBDD(1);

    BDDArtiste art( artist.replace( "'", "$" ), ( m_souscat==2 ?*def : poch ) );
    BDDAlbum alb( album.replace( "'", "$" ),  poch, date, *BDDType::RecupererType(m_souscat), art  );

    BDDTitre tit( title.replace( "'", "$" ));
    BDDRelation rel( alb, art, tit, track, QString::number( min ) + ":" + QString::number( sec ).rightJustified( 2, '0' ), 1,0,1);
    BDDMp3 mp3( chemin.replace( "'", "$" ), rel, *BDDSupport::RecupererSupport(m_souscat) );


    if ( m_Chemins.find( mp3.id() ) != m_Chemins.end() )
    {
        m_Chemins[mp3.id()][1] = "trouve";

    }
    delete def;

}

void BDDGestionMp3::supprimerAnciensMP3( )
{
    m_iterateur = m_Chemins.constBegin();

    m_iteration = 0;

    QTimer::singleShot( 0, this, SLOT( supprstep() ) );
}
void BDDGestionMp3::supprstep()
{
    if ( m_iterateur != m_Chemins.constEnd() )
    {
        try
        {

            m_pourcentage = m_iteration * 100 / m_Chemins.count();

            int cle = m_iterateur.key();

            if ( m_Chemins[cle][1] != "trouve" )
            {
                emit pourcentage();
                SupprimerenBDDMP3( cle );
            }
            m_iteration++;
            m_Chemins.remove( cle );
            m_iterateur = m_Chemins.constBegin();
        }
        catch ( std::bad_alloc& e )
        {
            qDebug() << e.what();
        }
        QTimer::singleShot( 0, this, SLOT( supprstep() ) );
    }
    else
    {

        if ( !m_Categories.empty() )
            QTimer::singleShot( 0, this, SLOT( init() ) );
        else
        {
            ReconstruireListeCategorie();
            emit fin();
            BDDSingleton::getInstance().supprimerdossiersvides();
        }
    }
}
void BDDGestionMp3::recupererMp3( int Type )
{
    QMap < int, QStringList > Chemins;

    QString queryStri = "Select Id_MP3, Chemin FROM MP3 WHERE Categorie='" + QString::number( Type ) + "'";
    if ( Type == 1 )
    {
        queryStri = "Select Id_MP3, Chemin FROM MP3 WHERE Categorie NOT IN(2)";
    }

    QSqlQuery  query =  madatabase.exec( queryStri );

    while ( query.next() )
    {
        QStringList infos;
        QSqlRecord rec = query.record();
        const int Mp3 = rec.value( "Id_MP3" ).toInt();
        const QString Chem = rec.value( "Chemin" ).toString().replace( "$", "'" );

        infos  << Chem << "Pas Trouvé";

        Chemins.insert( Mp3, infos );

    }
    m_Chemins = Chemins;

}
QString BDDGestionMp3::getdossierpardef()
{
    QString queryStr = "Select Valeur from Configuration WHERE Intitule='DossierParDef'" ;
    QSqlQuery  query = madatabase.exec( queryStr );
    query.next();
    QSqlRecord rec = query.record();

    return rec.value( "Valeur" ).toString();

}
void BDDGestionMp3::SousCatParChemin( QString chemin )
{

    if ( chemin.contains( "BOF" ) )
    {
        m_souscat = 4;
    }
    if ( chemin.contains( "Comedies Musicales" ) )
    {
        m_souscat = 5;
    }
    if ( chemin.contains( "Télé Réalités" ) )
    {
        m_souscat = 6;
    }
    if ( chemin.contains( "New Age" ) )
    {
        m_souscat = 7;
    }
    if ( chemin.contains( "Classique" ) )
    {
        m_souscat = 8;
    }
    if ( chemin.contains( "Generiques" ) )
    {
        m_souscat = 9;
    }
    if ( chemin.contains( "Reprises" ) )
    {
        m_souscat = 10;
    }
}
void BDDGestionMp3::ReconstruireListeCategorie()
{
    //On met dans une autre catégorie les artistes qui ont moins de 10 Mp3 à leur actif
    QString queryStr = "UPDATE MP3 SET Categorie = '11' WHERE Id_Relation IN ( SELECT Id_Relation FROM Relations WHERE  Id_Artiste IN ( SELECT Id_Artiste FROM Relations R, MP3 M, Album B  WHERE M.Id_Relation = R.Id_Relation AND R.Id_Album = B.Id_Album AND B.Type = 1 GROUP BY R.Id_Artiste HAVING COUNT(M.Id_Relation)<10 ) ) " ;
    madatabase.exec( queryStr );

    //Les albums de ces mp3 changent aussi de categories
    queryStr = "UPDATE Album SET Type = '11' WHERE Id_Album IN ( SELECT Id_Album FROM Relations WHERE Id_Artiste IN ( SELECT Id_Artiste FROM Relations R, MP3 M, Album B            WHERE M.Id_Relation = R.Id_Relation AND R.Id_Album = B.Id_Album AND B.Type = 1 GROUP BY R.Id_Artiste HAVING COUNT(M.Id_Relation)<10 ) ) " ;
    madatabase.exec( queryStr );


    //On ajoute dans cette même catégorie les artistes qui ont qu'un seul album à leur actif
    queryStr = " UPDATE MP3 SET Categorie = '11' WHERE Id_Relation IN ( SELECT Id_Relation FROM Relations WHERE Id_Album IN ( SELECT R.Id_Album FROM Relations R, MP3 M, Album B  WHERE  R.Id_Album = B.Id_Album AND B.Type = 1 AND M.Id_Relation = R.Id_Relation GROUP BY R.Id_Artiste HAVING COUNT ( DISTINCT R.Id_Album) < 2 ))" ;
    madatabase.exec( queryStr );

    //Les albums de ces mp3 changent aussi de categories
    queryStr = " UPDATE Album SET Type = '11' WHERE Id_Album IN ( SELECT Id_Album FROM Relations WHERE Id_Album IN ( SELECT R.Id_Album FROM Relations R, MP3 M  WHERE  , Album B  WHERE  R.Id_Album = B.Id_Album AND B.Type = 1 AND M.Id_Relation = R.Id_Relation GROUP BY R.Id_Artiste HAVING COUNT ( DISTINCT R.Id_Album) < 2 ))" ;
    madatabase.exec( queryStr );

}

void BDDGestionMp3::SupprimerenBDDMP3( int Id )
{

    BDDMp3* mp3 = BDDMp3::RecupererMp3( Id );
    m_fichierlu = "Suppression de ..." + mp3->m_chemin;
    mp3->supprimerenBDD();
    delete mp3;

}
void BDDGestionMp3::ViderBDD()
{
    QList<int> tempCat = BDDType::NbCategories();

    for ( int i = 0; tempCat.count(); i++ )
    {
        recupererMp3( tempCat[i] );
        if ( m_Chemins.isEmpty() )
            supprimerAnciensMP3();
    }
}
