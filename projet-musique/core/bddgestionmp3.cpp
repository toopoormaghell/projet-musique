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
//    qDebug() << "ici";
    m_type = type;
    creerfilefichiers();
    m_iteration = 0;

    QTimer::singleShot(0, this, SLOT( step() ) );
}

void BDDGestionMp3::step()
{
//    qDebug() << "pass";
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
    }
}


void BDDGestionMp3::creerfilefichiers()
{
    //Première étape: on met en QMap les chemins des MP3
    //Sous la forme de Id_Mp3 (en clé) et Id_Titre,Chemin,Booléen (en valeurs)
    m_Chemins = recupererMp3(m_type);

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
    qDebug() << chemin;
    // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
    QByteArray arrFileName = QFile::encodeName(chemin);
    const char *encodedName = arrFileName.constData();
    TagLib::FileRef f(encodedName);

    //   notifierObservateurs( chemin, (float)copt / (float)fileList.size() );

    //On récupère l'artiste, l'album, le titre et le numéro de piste
    TagLib::String artist = f.tag()->artist();
    TagLib::String album =  f.tag()->album();
    TagLib::uint date= f.tag()->year();
    TagLib::String title =  f.tag()->title();
    TagLib::uint track = f.tag() -> track();
    int dureesec=f.audioProperties()->length();
    int min=dureesec/60;
    int sec=dureesec%60;
    ArtisteParChemin(artist,chemin);

    //On ajoute en BDD
    int IdMp3;
    BDDPoch poch( ImageAlbum( f ), TStringToQString(album).replace("'","$"), TStringToQString(artist).replace("'","$") );
    BDDArtiste art( TStringToQString(artist).replace("'","$"), poch );
    BDDAlbum alb(TStringToQString(album).replace("'","$"),poch,date,m_type);
    BDDTitre tit(TStringToQString(title).replace( "'","$"),track,QString::number(min)+":"+QString::number(sec).rightJustified(2,'0'));
    BDDRelation rel(alb,art,tit);

    BDDMp3 mp3(chemin.replace("'","$"),rel,m_type);

    if ( m_Chemins.find( IdMp3 ) != m_Chemins.end() )
    {
        m_Chemins[IdMp3][1] = "trouvé";

    }

}

void BDDGestionMp3::supprimerAnciensMP3 ( )
{

    //On parcourt la Map des chemins pour trouver ceux qui n'ont jamais été trouvés.
    QMap < int, QStringList >::const_iterator iterateur;

    for (iterateur = m_Chemins.constBegin(); iterateur != m_Chemins.constEnd() ; ++iterateur)
    {
        int cle = iterateur.key ();

        QStringList ligne = iterateur.value ();

        if (ligne[1]!="trouvé")
        {
            QString key;
            key.setNum(cle);
            int Id_Titre=ligne[0].toInt();
            //   SupprimerMp3(Id_Titre);
        }
    }
}
QMap<int,QStringList> BDDGestionMp3::recupererMp3(int Type)
{
    QMap < int, QStringList > Chemins;

    QString queryStri = "Select * FROM Pochette ";
    QSqlQuery  query =  madatabase.exec(queryStri);

    while ( query.next() ) {
        QStringList infos;
        QSqlRecord rec = query.record();
        const int Mp3 = rec.value( "Id_Pochette").toInt();
        const QString Chem = rec.value( "Chemin" ).toString();

        infos  << Chem << "Pas Trouvé";

        Chemins.insert(Mp3,infos);

    }
    return Chemins;
}
QString BDDGestionMp3::getdossierpardef()
{
    QString queryStr = "Select Valeur from Configuration WHERE Intitule='DossierParDef'" ;
    QSqlQuery  query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();

    return rec.value("Valeur").toString();

}
void BDDGestionMp3::ArtisteParChemin(TagLib::String &artist, QString chemin)
{
    if (chemin.contains("BOF"))
    {
        artist = "BOF";
    }
    if (chemin.contains("Comedies Musicales"))
    {
        artist = "Comedies Musicales";
    }
    if (chemin.contains("Télé Réalités"))
    {
        artist = "Télé Réalités";
    }
    if (chemin.contains("Era"))
    {
        artist= "Era";
    }
    if (chemin.contains("Classique"))
    {
        artist="Classique";
    }
    if (chemin.contains("Generiques"))
    {
        artist="Generiques";
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
