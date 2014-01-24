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

    //Première étape: on met en QMap les chemins des MP3
    //Sous la forme de Id_Mp3 (en clé) et Id_Titre,Chemin,Booléen (en valeurs)
    QMap < int, QStringList > Chemins;
    QString selectDir;

    if (type=="Album")
    {
        // On sélectionne le répertoire à partir duquel on va rechercher les fichiers MP3
        selectDir = "F:/Albums";
    }
    if (type=="Compil")
    {
        selectDir="F:/Compil";

    }

    QString queryStri = "Select * FROM MP3 WHERE Categorie="+type+" ORDER BY Id_MP3";
    QSqlQuery  query =  madatabase.exec(queryStri);

    while ( query.next() ) {
        QStringList infos;
        QSqlRecord rec = query.record();
        const int Mp3 = rec.value( "Id_MP3").toInt();
        const QString Titre = rec.value( "Id_Titre" ).toString();
        const QString Chem = rec.value( "Chemin" ).toString();
        infos << Titre << Chem << "Pas Trouvé";
        Chemins.insert(Mp3,infos);

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

        // conversion du QString pour le nom du fichier MP3 ainsi que son chemin
        QByteArray arrFileName = QFile::encodeName(chemin);
        const char *encodedName = arrFileName.constData();
        TagLib::FileRef f(encodedName);

        qDebug() << chemin;
        notifierObservateurs( chemin, (float)copt / (float)fileList.size() );
        //qDebug() << chemin << " " << (float)copt / (float)fileList.size();

        //On récupère l'artiste, l'album, le titre et le numéro de piste
        TagLib::String artist = f.tag()->artist();
        TagLib::String album =  f.tag()->album();
        TagLib::uint date= f.tag()->year();
        TagLib::String title =  f.tag()->title();
        TagLib::uint track = f.tag() -> track();
        int dureesec=f.audioProperties()->length();
        int min=dureesec/60;
        int sec=dureesec%60;
        QString duree=QString::number(min)+":"+QString::number(sec).rightJustified(2,'0');

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
        QString NomAlbum = TStringToQString(album).replace("'","$");
        QString NomArtiste = TStringToQString(artist).replace("'","$");
        QString NomTitre = TStringToQString(title).replace( "'","$");

        QString annee=QString::number(date);
        QString num = QString::number(track);

        //On s'occupe de la pochette de l'album qu'on enregistre
        QImage Image;
        TagLib::ID3v2::Tag Tag(TagLib::FileRef(TagLib::FileName(encodedName)).file(),0);
        TagLib::ID3v2::FrameList Liste = Tag.frameListMap()["APIC"];
        TagLib::ID3v2::AttachedPictureFrame *Pic = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(Liste.front());
        Image.loadFromData((const uchar *) Pic->picture().data(), Pic->picture().size());

        //On crée le dossier qui correspond aux pochettes de l'artiste
        QString chempoch="./Pochettes/"+ NomArtiste;
        EnleverAccents(chempoch);
        QDir dossier;
        dossier.mkdir(chempoch);

        chempoch+="/"+NomAlbum+".jpg";
        EnleverAccents(chempoch);
        Image.save(chempoch,0,75);

        QString CheminPochBDD = chempoch.replace("'","$");

        //Déclaration des variables servant à récupérer les Id utiles.
        QString IdPoch;
        QString IdArtiste;
        QString IdAlbum;
        QString IdTitre;
        QStringList temp;

        //On vérifie si la pochette existe, puis l'artiste, puis l'album puis le titre enfin
        IdPoch= lireIDPoch(CheminPochBDD);
        temp << NomArtiste << IdPoch;

        IdArtiste= lireIDArtiste(temp);
        temp.clear();
        temp << NomAlbum << IdArtiste << IdPoch <<  "Album" << annee;
        IdAlbum= lireIDAlbum(temp);
        temp.clear();
        temp << NomTitre << IdAlbum << IdArtiste << IdPoch << num << duree;
        IdTitre = lireIDTitre(temp);

        QString cheminBDD=chemin.replace("'","$");

        //On vérifie si le titre existe dans la table MP3 ou non
        QString  queryStr = "Select Id_MP3 As 'MP3' from MP3 WHERE IdTitre='" + IdTitre+"' ";
        QSqlQuery query = madatabase.exec(queryStr);

        if (!query.first()) {
            queryStr="INSERT INTO MP3 VALUES (null,'"+ IdTitre + "','"+ cheminBDD +"','"+ type+"')";
            query = madatabase.exec(queryStr);

            //On vérifie si le titre existe dans la table MP3 ou non
            queryStr = "Select Id_MP3 As 'MP3' from MP3 WHERE  IdTitre='" + IdTitre+"' ";
            query = madatabase.exec(queryStr);
            query.next();
        }
        //ON DOIT METTRE A JOUR LA QMAP
        QSqlRecord rec = query.record();
        const   int IdMp3 = rec.value("MP3").toInt();

        if ( Chemins.find( IdMp3 ) != Chemins.end() )
        {
            Chemins[IdMp3][2] = "trouvé";
        }
        copt++;
    }
    //On parcourt la Map des chemins pour trouver ceux qui n'ont jamais été trouvés.
    QMap < int, QStringList >::const_iterator iterateur;

    for (iterateur = Chemins.constBegin(); iterateur != Chemins.constEnd() ; iterateur++)
    {
        int cle = iterateur.key ();

        QStringList ligne = iterateur.value ();

        if (ligne[2]!="trouvé")
        {
            QString key;
            key.setNum(cle);

            queryStri =  "DELETE FROM "+type+" WHERE Id_Mp3='"+key+"'";
            query = madatabase.exec(queryStri);

            //On vérifie si le titre existe dans la table MP3 ou non
            queryStri = "Select T.Id_Titre As 'Titre', T.Id_Artiste As 'Id_Artiste', B.Album As 'Album', T.Id_Pochette As 'Id_Pochette' , T.Id_Album As 'Id_Album', A.Artiste As 'Artiste' from Album 'B', Titre 'T', Artiste 'A' WHERE B.Id_Album=T.Id_Album AND T.Id_Artiste= A.Id_Artiste AND T.Id_Titre="+ligne[0];
            query =  madatabase.exec(queryStri);

            query.next();
            QSqlRecord rec = query.record();

            const QString Id_Artiste = rec.value( "Id_Artiste" ).toString();
            const QString Id_Album = rec.value( "Id_Album" ).toString();
            const QString Poch = rec.value( "Id_Pochette" ).toString();
            const QString Artiste = rec.value("Artiste").toString();
            const QString NomAlbum = rec.value("Album").toString();
            const QString CheminPoch = "./Pochettes/"+Artiste+"/"+NomAlbum+".jpg";

            //On efface le titre
            QStringList temp;
            temp << "MP3" << ligne[0] << Id_Album ;
            supprimerTitre(temp);

            //On efface l'album
            temp.clear();
            temp << Id_Album << CheminPoch;
            supprimerAlbum(temp);

            //On efface l'artiste
            temp.clear();
            temp << Id_Artiste << Artiste;
            supprimerArtiste(temp);


            //On efface la pochette
            supprimerPoch(Poch);
        }
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
