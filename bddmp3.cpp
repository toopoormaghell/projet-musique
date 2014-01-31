#include "bddmp3.h"
#include "bddsingleton.h"
#include <QtSql>
#include <QDir>

BDDMp3::BDDMp3(QObject *parent) :
    BDDCommun( parent )
{
}
// *****************************************************************
// *****************************************************************
// Fonction permettant de parcourir les dossiers et de remplir la BDD
// *****************************************************************
// *****************************************************************
void BDDMp3::actualiserMp3(QString type)
{
    //Premi�re �tape: on met en QMap les chemins des MP3
    //Sous la forme de Id_Mp3 (en cl�) et Id_Titre,Chemin,Bool�en (en valeurs)
    QMap < int, QStringList > Chemins = recupererMp3(type);

    QString selectDir;

    if (type=="Album")
    {
        selectDir = "F:/Albums/Indochine";
    }
    if (type=="Compil")
    {
        selectDir="F:/Compil";
    }

    // On remplit une QStringList avec chacun des filtres d�sir�s ici "*.mp3" .
    QStringList listFilter;
    listFilter << "*.mp3";

    // On d�clare un QDirIterator dans lequel on indique que l'on souhaite parcourir un r�pertoire et ses sous-r�pertoires.
    // De plus, on sp�cifie le filtre qui nous permettra de r�cup�rer uniquement les fichiers du type souhait�.
    QDirIterator dirIterator(selectDir, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    // Variable qui contiendra tous les fichiers correspondant � notre recherche
    QStringList fileList;
    // Tant qu'on n'est pas arriv� � la fin de l'arborescence...
    while(dirIterator.hasNext())
    {
        // ...on va au prochain fichier correspondant � notre filtre
        fileList << dirIterator.next();
    }

    int copt=0;
    //Pour chaque fichier, on va tenter de le rentrer dans la BDD
    while (copt<fileList.size())
    {
        //Ouverture du fichier MP3
        QString chemin = fileList[copt];

        // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
        QByteArray arrFileName = QFile::encodeName(chemin);
        const char *encodedName = arrFileName.constData();
        TagLib::FileRef f(encodedName);

        //  qDebug() << chemin;
        notifierObservateurs( chemin, (float)copt / (float)fileList.size() );
        //qDebug() << chemin << " " << (float)copt / (float)fileList.size();

        //On r�cup�re l'artiste, l'album, le titre et le num�ro de piste
        TagLib::String artist = f.tag()->artist();
        TagLib::String album =  f.tag()->album();
        TagLib::uint date= f.tag()->year();
        TagLib::String title =  f.tag()->title();
        TagLib::uint track = f.tag() -> track();
        int dureesec=f.audioProperties()->length();
        int min=dureesec/60;
        int sec=dureesec%60;
        ArtisteParChemin(artist,chemin);

        MP3Gestion mp3;
        mp3.Album= TStringToQString(album).replace("'","$");
        mp3.Artiste=TStringToQString(artist).replace("'","$");
        mp3.Titre=TStringToQString(title).replace( "'","$");
        mp3.Annee=QString::number(date);
        mp3.Duree= QString::number(min)+":"+QString::number(sec).rightJustified(2,'0');
        mp3.Num_Piste=track;
        mp3.Type=type;
        mp3.Pochette=ImageAlbum(encodedName);
        mp3.CheminFichier=chemin.replace("'","$");

        int IdMp3=ajouterMp3(mp3);

        if ( Chemins.find( IdMp3 ) != Chemins.end() )
        {
            Chemins[IdMp3][2] = "trouv�";
        }
        copt++;
    }
    //On parcourt la Map des chemins pour trouver ceux qui n'ont jamais �t� trouv�s.
    QMap < int, QStringList >::const_iterator iterateur;

    for (iterateur = Chemins.constBegin(); iterateur != Chemins.constEnd() ; iterateur++)
    {
        int cle = iterateur.key ();

        QStringList ligne = iterateur.value ();

        if (ligne[2]!="trouv�")
        {
            QString key;
            key.setNum(cle);
            int Id_Titre=ligne[0].toInt();
            SupprimerMp3(Id_Titre,cle);
        }
    }
}
QMap<int,QStringList> BDDMp3::recupererMp3(QString Type)
{
    QMap < int, QStringList > Chemins;

    QString queryStri = "Select * FROM MP3 WHERE Categorie='"+Type+"' ORDER BY Id_MP3";
    QSqlQuery  query =  madatabase.exec(queryStri);

    while ( query.next() ) {
        QStringList infos;
        QSqlRecord rec = query.record();
        const int Mp3 = rec.value( "Id_MP3").toInt();
        const QString Titre = rec.value( "Id_Titre" ).toString();
        const QString Chem = rec.value( "Chemin" ).toString();
        infos << Titre << Chem << "Pas Trouv�";
        Chemins.insert(Mp3,infos);

    }
    return Chemins;

}
QImage BDDMp3::ImageAlbum(const char* encodedName)
{
    //On s'occupe de la pochette de l'album qu'on enregistre
    QImage Image;
    TagLib::ID3v2::Tag Tag(TagLib::FileRef(TagLib::FileName(encodedName)).file(),0);
    TagLib::ID3v2::FrameList Liste = Tag.frameListMap()["APIC"];
    TagLib::ID3v2::AttachedPictureFrame *Pic = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(Liste.front());
    Image.loadFromData((const uchar *) Pic->picture().data(), Pic->picture().size());

    return Image;
}
void BDDMp3::ArtisteParChemin(TagLib::String &artist, QString chemin)
{
    if (chemin.contains("BOF"))
    {
        artist = "BOF";
    }
    if (chemin.contains("Comedies Musicales"))
    {
        artist = "Comedies Musicales";
    }
    if (chemin.contains("T�l� R�alit�s"))
    {
        artist = "T�l� R�alit�s";
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
QStringList  BDDMp3::listeArtistes(QString Categorie)
{
    QStringList liste;

    QString queryStr="SELECT DISTINCT Ar.Artiste, Ar.Id_Artiste FROM Artiste Ar, Album Al, Mp3 M, Titre T WHERE T.Id_Album=Al.Id_Album AND Al.Id_Artiste = Ar.Id_Artiste AND T.Id_Titre=M.Id_Titre AND M.Categorie='"+Categorie+"' ORDER BY Ar.Artiste";

    QSqlQuery query= madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        liste << rec.value("Artiste").toString().replace("$","'");
        liste << rec.value("Id_Artiste").toString();

    }

    return liste;
}
QStringList BDDMp3::listeCategories()
{
    QStringList categories;

    QSqlQuery query= madatabase.exec("SELECT DISTINCT Categorie FROM Mp3 M ORDER BY Categorie");

    while (query.next() ) {
        QSqlRecord rec=query.record();

        categories << rec.value("Categorie").toString().replace("$","'");

    }
    return categories;
}
QStringList BDDMp3::listeAlbums(QString Id_Artiste)
{
    QStringList albums;
    QSqlQuery query=madatabase.exec("SELECT DISTINCT Al.Album, Al.Annee, Al.Id_Album FROM Album Al, MP3 M,Titre T WHERE Al.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = T.Id_Album AND M.Id_Titre = T.Id_Titre ORDER BY Al.Annee");

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Annee").toString()+" - "+rec.value("Album").toString().replace("$","'");
        albums << rec.value("Id_Album").toString();
    }
    return albums;
}
QStringList BDDMp3::listeTitresAlbum(QString Id_Album)
{
    QStringList titres;
    QSqlQuery query=madatabase.exec("SELECT DISTINCT Titre, Duree, Num_Piste, T.Id_Titre FROM Titre T, Mp3 M WHERE M.Id_Titre = T.Id_Titre AND Id_Album="+Id_Album+" ORDER BY Num_Piste");

    while (query.next() ) {
        QSqlRecord rec=query.record();
        QString temp;
        QString Num= rec.value("Num_Piste").toString();

        temp = Num.rightJustified(2,'0') + " - " + rec.value("Titre").toString().replace("$","'") + "(" + rec.value("Duree").toString() + ")";
        titres << temp << rec.value("Id_Titre").toString();
    }
    return titres;
}
int BDDMp3::ajouterMp3(MP3Gestion mp3)
{
    QString chemin = AjouterPochette(mp3);
    mp3.Id_Poch=lireIDPoch(chemin);
    mp3.Id_Artiste=lireIDArtiste(mp3.Artiste,mp3.Id_Poch);
    mp3.Id_Album=lireIDAlbum(mp3.Album,mp3.Id_Poch,mp3.Id_Artiste,mp3.Annee,mp3.Type);
    mp3.Id_Titre=lireIDTitre(mp3.Titre,mp3.Id_Album,mp3.Id_Artiste,mp3.Id_Poch,mp3.Num_Piste,mp3.Duree);
    int Id_Mp3= lireIdMp3(mp3.Id_Titre,mp3.CheminFichier,mp3.Type);
    return Id_Mp3;
}
int BDDMp3::lireIdMp3(int IdTitre,QString cheminBDD,QString type)
{
    QString  queryStr = "Select Id_MP3 As 'MP3' from MP3 WHERE IdTitre='" + QString::number(IdTitre)+"' ";
    QSqlQuery query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO MP3 VALUES (null,'"+QString::number(IdTitre) + "','"+ cheminBDD +"','"+ type+"')";
        query = madatabase.exec(queryStr);

        //On v�rifie si le titre existe dans la table MP3 ou non
        queryStr = "Select Id_MP3 As 'MP3' from MP3 WHERE  IdTitre='" + QString::number(IdTitre)+"' ";
        query = madatabase.exec(queryStr);
        query.next();

    }
    QSqlRecord rec = query.record();
    int Id_Mp3 = rec.value( "MP3" ).toInt();
    return Id_Mp3;
}
void BDDMp3::SupprimerMp3(int Id_Titre,int Id_Mp3)
{
    QString queryStri =  "DELETE FROM MP3 WHERE Id_Mp3='"+QString::number(Id_Mp3)+"'";
    QSqlQuery query = madatabase.exec(queryStri);

    MP3Gestion mp3=RecupererInfosMp3(Id_Titre);
    qDebug() << "suppression de " << mp3.Id_Titre;
    bool titre=supprimerTitre(mp3.Id_Album,mp3.Id_Titre);
    if(titre)
    {
        EnleverAccents(mp3.Artiste);
        EnleverAccents(mp3.Album);
        QString Chemin="./Pochettes/"+mp3.Artiste+"/"+mp3.Album+".jpg";
        bool album=supprimerAlbum(mp3.Id_Album,Chemin);
        if (album)
        {
            QString CheminArtiste="./Pochettes/"+mp3.Artiste;
            bool artiste=supprimerArtiste(mp3.Id_Artiste,CheminArtiste);
            if(artiste)
            {
                supprimerPoch(mp3.Id_Poch);
            }
        }
    }
}
MP3Gestion BDDMp3::RecupererInfosMp3(int Id_Titre)
{
    MP3Gestion mp3;
    QString queryStr="Select T.Id_Titre As 'Titre', T.Id_Artiste As 'Id_Artiste', B.Album As 'Album', T.Id_Pochette As 'Id_Pochette' , T.Id_Album As 'Id_Album', A.Artiste As 'Artiste' from Album 'B', Titre 'T', Artiste 'A' WHERE B.Id_Album=T.Id_Album AND T.Id_Artiste= A.Id_Artiste AND T.Id_Titre="+Id_Titre;
    QSqlQuery query =  madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();

    mp3.Album=rec.value("Album").toString();
    mp3.Artiste=rec.value("Artiste").toString();
    mp3.Id_Album=rec.value("Titre").toInt();
    mp3.Id_Artiste=rec.value("Id_Artiste").toInt();
    mp3.Id_Poch=rec.value("Id_Pochette").toInt();

    return mp3;
}
