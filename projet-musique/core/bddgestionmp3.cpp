#include "bddgestionmp3.h"
#include "bddmp3.h"
#include "bddtype.h"
#include "bddconfig.h"
#include "tags.h"
#include "meta_titre.h"
#include <QDebug>
#include <QDirIterator>
#include <QDir>
#include <QTimer>
#include "outilsbdd.h"

BDDGestionMp3::BDDGestionMp3( QObject* parent ) :
    QObject( parent )
  , m_fichierlu()
  , m_pourcentage( 0 )
  , m_filelist()
  , m_Chemins()
  , m_type( 0 )
  , m_support( 0 )
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
        m_Categories << 4;
    }
}
QString BDDGestionMp3::dossiercategorie()
{
    switch ( m_type )
    {
    case ( 1 ):
        m_support = 1;
        return getdossierpardef();

    case ( 2 ):
        m_support = 2;
        return "F:/Compil";

    case ( 4 ):
        m_support = 4;
        return "F:/Albums Live";

    default:
        return "";

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

    QString donnees_p = "";

    //On ajoute en BDD
    Meta_Titre* mp3 = Meta_Titre::CreerMeta_Titre( album , artist ,title , date , QString::number( min ) + ":" + QString::number( sec ).rightJustified( 2, '0' ) , track , fich.getPoch(), m_souscat, -1, m_support , chemin, donnees_p, donnees_p );
    mp3->UpdateBDD();

    if ( m_Chemins.find( mp3->getid_mp3() ) != m_Chemins.end() )
    {
        m_Chemins[mp3->getid_mp3()][1] = "trouve";

    }
    delete mp3;
}

void BDDGestionMp3::supprimerAnciensMP3( )
{
    m_iterateur = m_Chemins.constBegin();

    m_iteration = 0;

    QTimer::singleShot( 0, this, SLOT( supprstep() ) );
}
void BDDGestionMp3::supprstep()
{
    if ( m_iterateur != m_Chemins.constEnd() && m_Chemins.count()!=0 )
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

            m_iterateur++;
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
            OutilsBDD* temp = new OutilsBDD;
            temp->SuppressionPochettes();
            emit fin();
        }
    }
}
void BDDGestionMp3::recupererMp3( int Type )
{
    m_Chemins = BDDMp3::RecupererMP3s( Type );
}
QString BDDGestionMp3::getdossierpardef()
{
    return BDDConfig::recupdossierpardef();
}
void BDDGestionMp3::SousCatParChemin( QString chemin )
{
    if ( chemin.contains( "BOF" ) )
    {
        m_souscat = 5;
    }
    if ( chemin.contains( "Comedies Musicales" ) )
    {
        m_souscat = 6;
    }
    if ( chemin.contains( "Télé Réalités" ) )
    {
        m_souscat = 7;
    }
    if ( chemin.contains( "New Age" ) )
    {
        m_souscat = 8;
    }
    if ( chemin.contains( "Classique" ) )
    {
        m_souscat = 9;
    }
    if ( chemin.contains( "Reprises" ) )
    {
        m_souscat = 10;
    }

}


void BDDGestionMp3::SupprimerenBDDMP3( int Id )
{
    Meta_Titre* mp3 = Meta_Titre::RecupererBDDMP3( Id );
    m_fichierlu = "Suppression de ..." + mp3->getcheminmp3();
    mp3->SupprimerBDDMP3();
    delete mp3;
}

void BDDGestionMp3::ViderBDD()
{
    recupererMp3( 25 );

    if ( ! m_Chemins.isEmpty() )
        supprimerAnciensMP3();

}
