#include "bddgestionmp3.h"
#include "bddsingleton.h"
#include <QtSql>
#include <QDir>
#include <QTimer>
#include "bddmp3.h"
#include "bddpoch.h"
#include "bddartiste.h"
#include "bddalbum.h"
#include "bddtitre.h"
#include "bddrelation.h"
#include "bddtype.h"

BDDGestionMp3::BDDGestionMp3(QObject *parent) :
    QObject(parent)
{
}

void BDDGestionMp3::demarreractualiser(int type)
{

    m_type = type;
    creerfilefichiers();
    m_iteration = 0;

    QTimer::singleShot(0, this, SLOT( step() ) );
}

void BDDGestionMp3::step()
{
    m_pourcentage = m_iteration*100/m_filelist.count();
    emit pourcentage();
    if (m_iteration <  m_filelist.count())
    {
        try
        {
            actualiserMp3(m_filelist[m_iteration]);
        }
        catch ( std::bad_alloc& e )
        {
            qDebug() << e.what();
        }

        QTimer::singleShot(0, this, SLOT( step() ) );
        ++m_iteration;
    } else
    {
        qDebug("Fin");
        supprimerAnciensMP3();
    }
}


void BDDGestionMp3::creerfilefichiers()
{
    m_filelist.clear();
    //Première étape: on met en QMap les chemins des MP3
    //Sous la forme de Id_Mp3 (en clé) et Chemin (en valeurs)
    recupererMp3(m_type);


    QString selectDir = getdossierpardef();


    // On remplit une QStringList avec chacun des filtres désirés ici "*.mp3" .
    QStringList listFilter;
    listFilter << "*.mp3";

    // On déclare un QDirIterator dans lequel on indique que l'on souhaite parcourir un répertoire et ses sous-répertoires.
    // De plus, on spécifie le filtre qui nous permettra de récupérer uniquement les fichiers du type souhaité.
    QDirIterator dirIterator(selectDir, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);


    // Tant qu'on n'est pas arrivé à la fin de l'arborescence...
    while(dirIterator.hasNext())
    {
        // ...on va au prochain fichier correspondant à notre filtre
        m_filelist << dirIterator.next();
    }
}

void BDDGestionMp3::actualiserMp3(QString chemin)
{
    m_fichierlu = chemin;
    m_souscat= m_type;
    // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
    QByteArray arrFileName = QFile::encodeName(chemin);
    const char *encodedName = arrFileName.constData();
    TagLib::FileRef f(encodedName);

    //On récupère l'artiste, l'album, le titre et le numéro de piste
    TagLib::String artist = f.tag()->artist();
    TagLib::String album =  f.tag()->album();
    TagLib::uint date= f.tag()->year();
    TagLib::String title =  f.tag()->title();
    TagLib::uint track = f.tag() -> track();
    int dureesec=f.audioProperties()->length();
    int min=dureesec/60;
    int sec=dureesec%60;
    SousCatParChemin(artist,chemin);

    //On ajoute en BDD

    BDDPoch poch( ImageAlbum( f ), TStringToQString(album).replace("'","$"), TStringToQString(artist).replace("'","$") );
    BDDArtiste art( TStringToQString(artist).replace("'","$"), poch );
    BDDAlbum alb(TStringToQString(album).replace("'","$"),poch,date,m_souscat);
    BDDTitre tit(TStringToQString(title).replace( "'","$"),track,QString::number(min)+":"+QString::number(sec).rightJustified(2,'0'));
    BDDRelation rel(alb,art,tit);

    BDDMp3 mp3(chemin.replace("'","$"),rel,m_souscat);


    if ( m_Chemins.find( mp3.m_id ) != m_Chemins.end() )
    {
        m_Chemins.remove(mp3.m_id);
    }
}

void BDDGestionMp3::supprimerAnciensMP3 ( )
{
    //On parcourt la Map des chemins pour trouver ceux qui n'ont jamais été trouvés.
    QMap < int, QStringList >::const_iterator iterateur;
    m_iteration=0;

    for (iterateur = m_Chemins.constBegin(); iterateur != m_Chemins.constEnd() ; ++iterateur)
    {
        m_pourcentage = m_iteration*100/m_Chemins.count();
        emit pourcentage();
        int cle = iterateur.key ();

           SupprimerenBDDMP3(cle);

        m_iteration++;
    }
    BDDSingleton::getInstance().supprimerdossiersvides();
}
void BDDGestionMp3::recupererMp3(int Type)
{
    QMap < int, QStringList > Chemins;

    QString queryStri = "Select Id_MP3, Chemin FROM MP3 ";
    QSqlQuery  query =  madatabase.exec(queryStri);

    while ( query.next() ) {
        QStringList infos;
        QSqlRecord rec = query.record();
        const int Mp3 = rec.value( "Id_MP3").toInt();
        const QString Chem = rec.value( "Chemin" ).toString().replace("$","'");

        infos  << Chem << "Pas Trouvé";

        Chemins.insert(Mp3,infos);

    }
    m_Chemins= Chemins;
}
QString BDDGestionMp3::getdossierpardef()
{
    QString queryStr = "Select Valeur from Configuration WHERE Intitule='DossierParDef'" ;
    QSqlQuery  query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();

    return rec.value("Valeur").toString();

}
void BDDGestionMp3::SousCatParChemin(TagLib::String &artist, QString chemin)
{
    if (chemin.contains("BOF"))
    {
       m_souscat = 4;
    }
    if (chemin.contains("Comedies Musicales"))
    {
        m_souscat = 5;
    }
    if (chemin.contains("Télé Réalités"))
    {
        m_souscat = 6;
    }
    if (chemin.contains("Era"))
    {
        m_souscat = 7;
    }
    if (chemin.contains("Classique"))
    {
        m_souscat = 8;
    }
    if (chemin.contains("Generiques"))
    {
        m_souscat = 9;
    }
}

QImage BDDGestionMp3::ImageAlbum(const TagLib::FileRef &f)
{
    //On s'occupe de la pochette de l'album qu'on enregistre
    QImage Image;
    TagLib::ID3v2::Tag Tag(f.file(),0);
    TagLib::ID3v2::FrameList Liste = Tag.frameListMap()["APIC"];
    TagLib::ID3v2::AttachedPictureFrame *Pic = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(Liste.front());

    if ( ( Pic == NULL ) || Pic->picture().isEmpty() )
    {
        Image.fromData("./Pochettes/def.jpg");

    }
    else
    {
        Image.loadFromData((const uchar *) Pic->picture().data(), Pic->picture().size());
    }

    return Image;
}
void BDDGestionMp3::SupprimerenBDDMP3(int Id)
{
    BDDMp3* mp3 = BDDMp3::RecupererMp3(Id);
    mp3->supprimerenBDD();
    mp3->~BDDMp3();
}
