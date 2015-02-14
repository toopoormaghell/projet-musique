#include "bddmp3.h"
#include "bddsingleton.h"
#include <QtSql>
#include <QDir>

BDDMp3::BDDMp3(QObject *parent):
    BDDCommun(parent)
{

}
// *****************************************************************
// *****************************************************************
// Fonction permettant de parcourir les dossiers et de remplir la BDD
// *****************************************************************
// *****************************************************************
void BDDMp3::actualiserMp3(QString type)
{
    //Première étape: on met en QMap les chemins des MP3
    //Sous la forme de Id_Mp3 (en clé) et Id_Titre,Chemin,Booléen (en valeurs)
    QMap < int, QStringList > Chemins = recupererMp3(type);

    QString selectDir;

    if (type=="Album")
    {
        selectDir = getdossierpardef();
    }
    if (type=="Compil")
    {
        selectDir="F:/Compil";
    }

    // On remplit une QStringList avec chacun des filtres désirés ici "*.mp3" .
    QStringList listFilter;
    listFilter << "*.mp3";

    // On déclare un QDirIterator dans lequel on indique que l'on souhaite parcourir un répertoire et ses sous-répertoires.
    // De plus, on spécifie le filtre qui nous permettra de récupérer uniquement les fichiers du type souhaité.
    QDirIterator dirIterator(selectDir, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    // Variable qui contiendra tous les fichiers correspondant à notre recherche
    QStringList fileList;
    // Tant qu'on n'est pas arrivé à la fin de l'arborescence...
    while(dirIterator.hasNext())
    {
        // ...on va au prochain fichier correspondant à notre filtre
        fileList << dirIterator.next();
    }

    int copt=0;
    //Pour chaque fichier, on va tenter de le rentrer dans la BDD
    while (copt<fileList.size())
    {
        //Ouverture du fichier MP3
        QString chemin = fileList[copt];
        qDebug() << chemin;
        // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
        QByteArray arrFileName = QFile::encodeName(chemin);
        const char *encodedName = arrFileName.constData();
        TagLib::FileRef f(encodedName);

        notifierObservateurs( chemin, (float)copt / (float)fileList.size() );

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

        MP3Gestion mp3;
        mp3.Album= TStringToQString(album).replace("'","$");
        mp3.Artiste=TStringToQString(artist).replace("'","$");
        mp3.Titre=TStringToQString(title).replace( "'","$");
        mp3.Annee=QString::number(date);
        mp3.Duree= QString::number(min)+":"+QString::number(sec).rightJustified(2,'0');
        mp3.Num_Piste=track;
        mp3.Type=type;
        mp3.Pochette=ImageAlbum(f);
        mp3.CheminFichier=chemin.replace("'","$");

        int IdMp3=ajouterMp3(mp3);

        if ( Chemins.find( IdMp3 ) != Chemins.end() )
        {
            Chemins[IdMp3][2] = "trouvé";

        }
        copt++;
    }
    //On parcourt la Map des chemins pour trouver ceux qui n'ont jamais été trouvés.
    QMap < int, QStringList >::const_iterator iterateur;

    for (iterateur = Chemins.constBegin(); iterateur != Chemins.constEnd() ; ++iterateur)
    {
        int cle = iterateur.key ();

        QStringList ligne = iterateur.value ();

        if (ligne[2]!="trouvé")
        {
            QString key;
            key.setNum(cle);
            int Id_Titre=ligne[0].toInt();
            SupprimerMp3(Id_Titre);
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
        const QString Titre = rec.value( "Id_Relation" ).toString();
        const QString Chem = rec.value( "Chemin" ).toString();

        infos << Titre << Chem << "Pas Trouvé";

        Chemins.insert(Mp3,infos);

    }
    return Chemins;
}
QImage BDDMp3::ImageAlbum(const TagLib::FileRef& f)
{
    //On s'occupe de la pochette de l'album qu'on enregistre
    QImage Image;
    TagLib::ID3v2::Tag Tag(f.file(),0);
    TagLib::ID3v2::FrameList Liste = Tag.frameListMap()["APIC"];
    TagLib::ID3v2::AttachedPictureFrame *Pic = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(Liste.front());

    if ( ( Pic != NULL ) || Pic->picture().isEmpty() )
    {
       Image.fromData("./Pochettes/def.jpg");

    }
    else
    {
       Image.loadFromData((const uchar *) Pic->picture().data(), Pic->picture().size());
    }

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
QStringList  BDDMp3::listeArtistes(QString Categorie)
{
    QStringList liste;

    QString queryStr="SELECT DISTINCT Ar.Artiste, Ar.Id_Artiste FROM Artiste Ar, Mp3 M, Relations R WHERE R.Id_Artiste = Ar.Id_Artiste AND R.Id_Relation=M.Id_Relation AND M.Categorie='"+Categorie+"' ORDER BY Ar.Artiste";

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
    QSqlQuery query=madatabase.exec("SELECT DISTINCT Al.Album, Al.Annee, Al.Id_Album FROM Album Al, MP3 M,Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = R.Id_Album AND R.Id_Relation = M.Id_Relation AND M.Categorie='Album' ORDER BY Al.Annee DESC");

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
    QString queryStr="SELECT DISTINCT Titre, Duree, Num_Piste, T.Id_Titre FROM Titre T, Mp3 M, Relations R WHERE R.Id_Titre = T.Id_Titre AND R.Id_Album="+Id_Album+" AND R.Id_Relation=M.Id_Relation AND M.Categorie='Album' ORDER BY Num_Piste";
    QSqlQuery query=madatabase.exec(queryStr);

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
    mp3.Id_Relation=lireIDRelation(mp3.Id_Album,mp3.Id_Artiste,mp3.Id_Titre,mp3.Id_Poch);
    int Id_Mp3= lireIdMp3(mp3.Id_Relation,mp3.CheminFichier,mp3.Type);

    return Id_Mp3;
}
int BDDMp3::lireIdMp3(int IdRelation,QString cheminBDD,QString type)
{
    QString temp=QString::number(IdRelation);

    QString  queryStr = "Select Id_MP3 As 'MP3' from MP3 WHERE Id_Relation='" + temp+"' ";
    QSqlQuery query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO MP3 VALUES (null,'"+temp + "','"+ cheminBDD +"','"+ type+"')";
        madatabase.exec(queryStr);

        //On vérifie si le titre existe dans la table MP3 ou non
        queryStr = "Select Id_MP3 As 'MP3' from MP3 WHERE  Id_Relation='" + temp+"' ";
        query = madatabase.exec(queryStr);
        query.next();

    }
    QSqlRecord rec = query.record();
    int Id_Mp3 = rec.value( "MP3" ).toInt();

    return Id_Mp3;
}
void BDDMp3::SupprimerMp3(int Id_Titre)
{
    MP3Gestion mp3=RecupererInfosMp3(Id_Titre);

    QString queryStri =  "DELETE FROM MP3 WHERE Id_Relation='"+QString::number(mp3.Id_Relation)+"'";
    QSqlQuery query = madatabase.exec(queryStri);

    qDebug() << "suppression de " << mp3.Titre << " de " << mp3.Artiste << " sur " << mp3.Album;
    bool titre=supprimerTitredeMp3(mp3.Id_Album,mp3.Id_Titre,mp3.Id_Relation);

    if(titre)
    {
        EnleverAccents(mp3.Artiste);
        EnleverAccents(mp3.Album);
        QString Chemin="./Pochettes/"+mp3.Artiste+"/"+mp3.Album+".jpg";
        bool album=supprimerAlbum(mp3.Id_Album);
        if (album)
        {
            QString CheminArtiste="./Pochettes/"+mp3.Artiste;
            bool artiste=supprimerArtiste(mp3.Id_Artiste);
            if(artiste)
            {
                supprimerPoch(mp3.Id_Poch,CheminArtiste,Chemin);
            }
        }
    }
}
void BDDMp3::ViderMp3(QString Type)
{
    QString queryStr= "SELECT R.Id_Titre As 'Id_Titre' FROM MP3 M, Relations R WHERE M.Categorie='"+Type+"' AND R.Id_Relation=M.Id_Relation";

    QSqlQuery query= madatabase.exec(queryStr);

    while (query.next())
    {
        QSqlRecord rec= query.record();
        int Id_Titre=rec.value("Id_Titre").toInt();

        SupprimerMp3(Id_Titre);
    }
}

MP3Gestion BDDMp3::RecupererInfosMp3(int Id_Titre)
{
    MP3Gestion mp3;

    QString queryStr="Select T.Id_Titre As 'Id_Titre',B.Type AS 'Type', R.Id_Artiste As 'Id_Artiste', B.Album As 'Album', R.Id_Pochette As 'Id_Pochette' , R.Id_Album As 'Id_Album', A.Artiste As 'Artiste',T.Duree As 'Duree',T.Num_Piste AS 'Num_Piste', B.Annee As 'Annee',T.Titre AS 'Titre', R.Id_Relation AS 'Id_Relation' from Album 'B', Titre 'T', Artiste 'A', Relations R WHERE R.Id_Album=B.Id_Album AND R.Id_Titre=T.Id_Titre AND R.Id_Artiste= A.Id_Artiste AND R.Id_Titre="+QString::number(Id_Titre);

    QSqlQuery query =  madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();

    mp3.Album=rec.value("Album").toString().replace("$","'");
    mp3.Artiste=rec.value("Artiste").toString().replace("$","'");
    mp3.Titre=rec.value("Titre").toString().replace("$","'");
    mp3.Id_Titre=rec.value("Id_Titre").toInt();
    mp3.Id_Album=rec.value("Id_Album").toInt();
    mp3.Id_Artiste=rec.value("Id_Artiste").toInt();
    mp3.Id_Poch=rec.value("Id_Pochette").toInt();
    mp3.Duree=rec.value("Duree").toString();
    mp3.Num_Piste=rec.value("Num_Piste").toInt();
    mp3.Type=rec.value("Type").toString();
    mp3.Annee=rec.value("Annee").toString();
    mp3.Pochette=afficherPochette(QString::number(mp3.Id_Poch),"Pochette");
    mp3.TitreenMp3etPhys=verifierTitreMp3Phys(Id_Titre);
    mp3.Id_Relation=rec.value("Id_Relation").toInt();
    return mp3;
}

QString BDDMp3::getPathFromIdMp3(const QString &mp3Id)
{
    QString queryStr="Select Chemin From Mp3 M, Relations R where M.Id_Relation=R.Id_Relation AND R.Id_Titre=" + mp3Id;
    QSqlQuery query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();
    return rec.value( "Chemin" ).toString().replace( "$", "'" );
}
QMap<int, MP3Gestion> BDDMp3::similaires(QString Id)
{
    QMap<int, MP3Gestion> simi;

    int cpt=0;
    QString queryStr;

    //Première étape: on récupère le TitreSSAccents, et on voit si on peut en tirer un titre sans titre de remix
    queryStr="SELECT TitreSSAccents FROM Titre WHERE Id_Titre='"+Id+"'";
    QSqlQuery query = madatabase.exec((queryStr));
    query.next();
    QSqlRecord rec=query.record();
    QString TitreSSAccents= rec.value("TitreSSAccents").toString();

    QStringList tmp=TitreSSAccents.split(" (");
    TitreSSAccents=tmp.at(0);
    tmp=TitreSSAccents.split("[");
    TitreSSAccents=tmp.at(0);

    //Deuxième étape: on essaie de trouver les titres similaires
    queryStr="SELECT DISTINCT T.Id_Titre FROM Titre T, MP3 M, Relations R WHERE T.Id_Titre!="+Id+" AND R.Id_Relation=M.Id_Relation AND T.Id_Titre=R.Id_Titre AND (T.TitreSSAccents LIKE '"+TitreSSAccents+"%mix%' OR T.TitreSSAccents LIKE '"+TitreSSAccents+"%')";
    query = madatabase.exec((queryStr));
    while (query.next())
    {
        MP3Gestion Titre;
        rec=query.record();
        Titre= RecupererInfosMp3(rec.value("Id_Titre").toInt());
        simi.insert(cpt,Titre);
        cpt++;
    }
    return simi;
}
bool BDDMp3::ActualiserAlbums()
{
    bool resultat=false;
    QString queryStr="Select Valeur From Configuration where Intitule='ActualiserAlbums'";
    QSqlQuery query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();
    QString temp=rec.value( "Valeur" ).toString();
    if (temp=="Oui")
    {
        resultat=true;
    }
    return resultat;
}
bool BDDMp3::ActualiserCompil()
{
    bool resultat=false;
    QString queryStr="Select Valeur From Configuration where Intitule='ActualiserCompil'";
    QSqlQuery query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();
    QString temp=rec.value( "Valeur" ).toString();
    if (temp=="Oui")
    {
        resultat=true;
    }
    return resultat;
}
bool BDDMp3::ActualiserLives()
{
    bool resultat=false;
    QString queryStr="Select Valeur From Configuration where Intitule='ActualiserLives'";
    QSqlQuery query = madatabase.exec(queryStr);
    query.next();
    QSqlRecord rec = query.record();
    QString temp=rec.value( "Valeur" ).toString();
    if (temp=="Oui")
    {
        resultat=true;
    }
    return resultat;
}
void BDDMp3::EnregistrerActuAlbums(bool check)
{
    QString queryStr="Update Configuration SET Valeur=";

    if(check)
    {
        queryStr+="'Oui'";
    } else
    {
        queryStr+="'Non'";
    }
    queryStr+=" WHERE Intitule='ActualiserAlbums'";

    QSqlQuery query = madatabase.exec(queryStr);
}
void BDDMp3::EnregistrerActuCompil(bool check)
{
    QString queryStr="Update Configuration SET Valeur=";

    if(check)
    {
        queryStr+="'Oui'";
    } else
    {
        queryStr+="'Non'";
    }
    queryStr+=" WHERE Intitule='ActualiserCompil'";

    QSqlQuery query = madatabase.exec(queryStr);
}
void BDDMp3::EnregistrerActuLives(bool check)
{
    QString queryStr="Update Configuration SET Valeur=";

    if(check)
    {
        queryStr+="'Oui'";
    } else
    {
        queryStr+="'Non'";
    }
    queryStr+=" WHERE Intitule='ActualiserLives'";

    QSqlQuery query = madatabase.exec(queryStr);
}
QList<int> BDDMp3::ListeMp3Compil(QString annee)
{
    QList<int> listeMp3;

    QString queryStr="SELECT T.Id_Titre From Mp3 M,Titre T, Album A, Relations R WHERE M.Categorie='Compil' AND R.Id_Titre=T.Id_Titre AND R.Id_Relation=M.Id_Relation AND A.Id_Album=R.Id_Album AND"+annee+" ORDER BY Annee";

    QSqlQuery query=madatabase.exec(queryStr);
    while (query.next() ) {
        QSqlRecord rec=query.record();
        listeMp3 << rec.value("Id_Titre").toInt();
    }
    return listeMp3;
}
int BDDMp3::NombreMP3()
{
    QString QueryStr="SELECT COUNT(*) AS 'Nb' FROM MP3";
    QSqlQuery query=madatabase.exec(QueryStr);

    while (query.next())
    {
        QSqlRecord rec=query.record();
        return rec.value("Nb").toInt();
    }
}
