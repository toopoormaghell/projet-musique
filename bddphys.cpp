#include "bddphys.h"
#include "bddsingleton.h"
#include <qtsql>
BDDPhys::BDDPhys(QObject *parent):
    BDDCommun(parent)
{
}
void BDDPhys::AjouterAlbum(AlbumGestion album)
{
    QString CheminPochette= AjouterPochette(album).replace("'","$");
    album.Id_Poch= lireIDPoch(CheminPochette);
    album.Id_Artiste=lireIDArtiste(album.Artiste,album.Id_Poch);
    album.Id_Album=lireIDAlbum(album.Album.replace("'","$"),album.Id_Poch,album.Id_Artiste,album.Annee,album.Type);
    int IdPhys = lireIDPhys(album.Id_Album,album.Type,album.CodeBarres);

    // On s'occupe des titres
    for(int cpt=0;cpt<album.titres.count();cpt++)
    {
        album.titres[cpt].Id_Titre = lireIDTitre(album.titres[cpt].Titre.replace("'","$"),album.Id_Album,album.Id_Artiste,album.Id_Poch,album.titres[cpt].Num_Piste,album.titres[cpt].Duree);
    }

    if (album.ErreurPochette==true)
    {
      AjouterErreur(album);

    }

}
void BDDPhys::AjouterErreur(AlbumGestion album)
{
    QString chemin="./pochettes/"+album.Artiste+"/"+album.Album+".jpg";
        //On v�rifie que la pochette n'est d�j� pas encore � faire
    QString queryStr="SELECT Id_Pochette FROM Pochette P, ErreurPochettes E WHERE P.Chemin ='"+album.Chem_Poch_Alt+"' OR E.Chemin = '"+chemin+"'";
    QSqlQuery query = madatabase.exec(queryStr);

    if(!query.first())
    {
        qDebug() << "passe l�";
        queryStr="INSERT INTO ErreurPochettes VALUES(null,'"+QString::number(album.Id_Poch)+"','"+album.Chem_Poch_Alt+"')";
        madatabase.exec(queryStr);
    }
}

int BDDPhys::lireIDPhys(int Id_Album,QString Type,QString CodeBarres)
{
    //On v�rifie si l'album existe dans la table Phys ou non
    QString queryStr = "Select Id_Phys As 'Phys' from Phys WHERE Id_Album='" +QString::number(Id_Album)+ "'";
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Phys VALUES (null,'"+QString::number(Id_Album)+"','"+Type+"','"+CodeBarres+"')";
        query = madatabase.exec(queryStr);

        queryStr = "Select Id_Phys As 'Phys' from Phys WHERE Id_Album='" +QString::number(Id_Album)+"'";
        query = madatabase.exec(queryStr);
        query.next();
    }
    QSqlRecord rec = query.record();
    int IdPhys = rec.value( "Phys" ).toInt();

    return IdPhys;
}

void BDDPhys::SupprimerAlbumPhys(QString Id_Album)
{
    //On r�cup�re les infos de l'album
    AlbumGestion album = InfosAlbum(Id_Album);
    album.Id_Album=Id_Album.toInt();
    //Pour chaque titre, on v�rifie si on peut effacer les titres
    bool titres=true;bool boolalbum=false;bool artiste=false;

    for (int cpt=0;cpt<album.titres.count();cpt++)
    {
        bool supp = supprimerTitre(album.titres[cpt].Id_Titre);

        if( !supp && titres)
        {
            qDebug() << "suppression du Titre" <<   album.titres[cpt].Id_Titre;
            titres=false;
        }

    }

    //Si on �limine tous les titres, on fait l'album et l'artiste, puis la pochette
    if(titres=true)
    {
        boolalbum = supprimerAlbum(album.Id_Album);
        if(boolalbum)
        {
            qDebug() << " Album supprim� : " << album.Album;
            artiste=supprimerArtiste(album.Id_Artiste,album.Artiste);

            if(artiste)
            {
                qDebug() << " Artiste supprim� : " << album.Artiste;
                supprimerPoch(album.Id_Poch,album.Artiste,album.Album);
            }
        }
    }

}
QStringList  BDDPhys::listeArtistes(QString Categorie)
{
    QStringList liste;

    Categorie=choixCategorie(Categorie);

    QString queryStr="SELECT DISTINCT Ar.Artiste, Ar.Id_Artiste FROM Artiste Ar, Album Al, Phys P WHERE P.Id_Album=Al.Id_Album AND Al.Id_Artiste = Ar.Id_Artiste AND (P.Categorie="+Categorie+") ORDER BY Ar.Artiste";

    QSqlQuery query= madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        liste << rec.value("Artiste").toString().replace("$","'");
        liste << rec.value("Id_Artiste").toString();

    }

    return liste;
}
QString BDDPhys::choixCategorie(QString Categorie)
{
    if (Categorie=="Tout")
    {
        Categorie="'Album' OR P.Categorie='Single'";
    }else {
        Categorie="'"+Categorie+"'";
    }
    return Categorie;
}

QStringList BDDPhys::listeCategories()
{
    QStringList categories;

    QSqlQuery query= madatabase.exec("SELECT DISTINCT Categorie FROM Phys P ORDER BY Categorie");

    while (query.next() ) {
        QSqlRecord rec=query.record();

        categories << rec.value("Categorie").toString().replace("$","'");

    }
    return categories;
}
QStringList BDDPhys::listeAlbums(QString Id_Artiste,QString Categorie)
{
    QStringList albums;

    Categorie=choixCategorie(Categorie);

    QSqlQuery query=madatabase.exec("SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P WHERE Al.Id_Artiste="+Id_Artiste+" AND Al.Id_Album = P.Id_Album AND (P.Categorie="+Categorie+") ORDER BY Categorie,Al.Annee");

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toString();
    }
    return albums;
}
QList<TitreGestion> BDDPhys::listeTitresAlbum(QString Id_Album)
{
    QList<TitreGestion> titres;

    QSqlQuery query=madatabase.exec("SELECT DISTINCT Titre, Duree, Num_Piste,Id_Titre FROM Titre WHERE Id_Album="+Id_Album+" ORDER BY Num_Piste");

    while (query.next() ) {
        TitreGestion titre;
        QSqlRecord rec=query.record();

        titre.Num_Piste= rec.value("Num_Piste").toInt();
        titre.Titre=rec.value("Titre").toString().replace("$","'");
        titre.Duree=rec.value("Duree").toString().replace("$","'");
        titre.Id_Titre=rec.value("Id_Titre").toInt();
        titres << titre;
    }
    return titres;
}
AlbumGestion BDDPhys::InfosAlbum(QString Id_Album)
{
    AlbumGestion album;

    QSqlQuery query=madatabase.exec("SELECT Al.Album, Annee, P.Categorie, Al.Id_Artiste, Al.Id_Pochette, Ar.Artiste FROM Album Al, Phys P,Artiste Ar WHERE Al.Id_Album=P.Id_Album AND Ar.Id_Artiste = Al.Id_Artiste AND Al.Id_Album="+Id_Album);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        album.Album=rec.value("Album").toString().replace("$","'");
        album.Annee=rec.value("Annee").toString();
        album.Pochette=afficherPochette(Id_Album,"Album");
        album.Type=rec.value("Categorie").toString();
        album.Id_Artiste=rec.value("Id_Artiste").toInt();
        album.Id_Poch=rec.value("Id_Pochette").toInt();
        album.Artiste=rec.value("Artiste").toString().replace("$","'");

        album.titres=listeTitresAlbum(Id_Album);
    }
    return album;
}
void BDDPhys::ExporterHTML(QString Type)
{
    QStringList albart=ListeAlbumArtisteExport(Type);

    QString chemin = "F:/"+Type+".html";
    //R�cup�re le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName = chemin;
    QFile fichier(fileName);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    // Cr�ation d'un objet QTextStream � partir de notre objet QFile
    QTextStream flux(&fichier);
    // On choisit le codec correspondant au jeu de caract�re que l'on souhaite ; ici, UTF-8


    for(int cpt=0;cpt<albart.count();cpt=cpt+2)
    {
        flux << QString::number(cpt/2).rightJustified(3,'0') << " - "<< albart[cpt]<< " " << albart[cpt+1] << "<br>"<< endl;
    }
}
QStringList BDDPhys::ListeAlbumArtisteExport(QString Type)
{
    QStringList albart;
    QString queryType;
    if (Type!="Tout")
    {
        queryType="AND P.Categorie='"+Type+"'";
    }
    QString QueryStr="SELECT Al.Album, Ar.Artiste FROM Phys P,Album Al, Artiste Ar WHERE P.Id_Album=Al.Id_Album AND Al.Id_Artiste = Ar.Id_Artiste "+queryType+" ORDER BY Ar.Artiste";
    QSqlQuery query=madatabase.exec(QueryStr);

    while(query.next())
    {
        QSqlRecord rec=query.record();
        albart << rec.value("Album").toString().replace("$","'") << rec.value("Artiste").toString().replace("$","'");
    }
    return albart;
}
QStringList BDDPhys::ListeAlbumSauvegarde()
{
    QStringList resultat;

    QString QueryStr="SELECT Al.Album, Ar.Artiste, P.Categorie, P.CodeBarres FROM Phys P,Album Al, Artiste Ar WHERE P.Id_Album=Al.Id_Album AND Al.Id_Artiste = Ar.Id_Artiste ORDER BY Ar.Artiste";
    QSqlQuery query=madatabase.exec(QueryStr);

    while(query.next())
    {
        QSqlRecord rec=query.record();
        resultat << rec.value("Album").toString().replace("$","'") << rec.value("Artiste").toString().replace("$","'") << rec.value("Categorie").toString() << rec.value("CodeBarres").toString();
    }
    return resultat;
}
void BDDPhys::SauvegarderAlbums()
{
    QStringList resultat=ListeAlbumSauvegarde();

    QString chemin = "H:/Codebarres.txt";
    //R�cup�re le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName = chemin;
    QFile fichier(fileName);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    // Cr�ation d'un objet QTextStream � partir de notre objet QFile
    QTextStream flux(&fichier);
    // On choisit le codec correspondant au jeu de caract�re que l'on souhaite ; ici, UTF-8
    flux.setCodec("UTF-8");

    for(int cpt=0;cpt<resultat.count();cpt=cpt+4)
    {
        flux << resultat[cpt]<< " " << resultat[cpt+1] << " " << resultat[cpt+2] << " " << resultat[cpt+3] << endl;
    }
}
QString BDDPhys::getjetonAcces()
{
    QString QueryStr="SELECT Valeur FROM Configuration WHERE Intitule='JetonAcces'";
    QSqlQuery query=madatabase.exec(QueryStr);

    while (query.next())
    {
        QSqlRecord rec=query.record();
        return rec.value("Valeur").toString();
    }
}
QString BDDPhys::getjetonSecret()
{
    QString QueryStr="SELECT Valeur FROM Configuration WHERE Intitule='JetonSecret'";
    QSqlQuery query=madatabase.exec(QueryStr);

    while (query.next())
    {
        QSqlRecord rec=query.record();
        return rec.value("Valeur").toString();
    }
}
void BDDPhys::changerjetonAcces(QString jeton)
{
    QString QueryStr="UPDATE Configuration SET Valeur='"+jeton+"' WHERE Intitule='JetonAcces'";
    QSqlQuery query=madatabase.exec(QueryStr);
}
void BDDPhys::changerjetonSecret(QString jeton)
{
    QString QueryStr="UPDATE Configuration SET Valeur='"+jeton+"' WHERE Intitule='JetonSecret'";
    QSqlQuery query=madatabase.exec(QueryStr);
}
