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
    lireIDPhys(album.Id_Album,album.Type,album.CodeBarres);

    // On s'occupe des titres
    for(int cpt=0;cpt<album.titres.count();cpt++)
    {
        album.titres[cpt].Id_Titre = lireIDTitre(album.titres[cpt].Titre.replace("'","$"),album.Id_Album,album.Id_Artiste,album.Id_Poch,album.titres[cpt].Num_Piste,album.titres[cpt].Duree);
        lireIDRelation(album.Id_Album,album.Id_Artiste,album.titres[cpt].Id_Titre,album.Id_Poch);
    }

    if (album.ErreurPochette==true)
    {
        AjouterErreur(album);
    }
}
void BDDPhys::AjouterCompil(CompilGestion album)
{
    QString CheminPochette= AjouterPochette(album).replace("'","$");
    album.Id_Poch= lireIDPoch(CheminPochette);
    album.Id_Artiste=lireIDArtiste(album.Artiste,album.Id_Poch);
    album.Id_Album=lireIDAlbum(album.Album.replace("'","$"),album.Id_Poch,album.Id_Artiste,album.Annee,album.Type);
    lireIDPhys(album.Id_Album,album.Type,album.CodeBarres);

    //On s'occupe des titres et des artistes concernés
    for(int cpt=0;cpt<album.titres.count();cpt++)
    {
        MP3Gestion titre=album.titres[cpt];

        qDebug() << titre.Artiste;
        int artiste = lireIDArtiste(titre.Artiste,album.Id_Poch);
        album.titres[cpt].Id_Titre = lireIDTitre(titre.Titre.replace("'","$"),album.Id_Album,artiste,album.Id_Poch,titre.Num_Piste,titre.Duree);
        lireIDRelation(album.Id_Album,artiste,album.titres[cpt].Id_Titre,album.Id_Poch);
    }

    if (album.ErreurPochette==true)
    {
        AjouterErreur(album);
    }
}

void BDDPhys::AjouterErreur(AlbumGestion album)
{
    QString chemin="./pochettes/"+album.Artiste+"/"+album.Album+".jpg";

    //On vérifie que la pochette n'est déjà pas encore à faire
    QString queryStr="SELECT Id_Pochette FROM Pochette P, ErreurPochettes E WHERE P.Chemin ='"+album.Chem_Poch_Alt+"' OR E.Chemin = '"+chemin+"'";
    QSqlQuery query = madatabase.exec(queryStr);

    if(!query.first())
    {

        queryStr="INSERT INTO ErreurPochettes VALUES(null,'"+QString::number(album.Id_Poch)+"','"+album.Chem_Poch_Alt+"')";
        madatabase.exec(queryStr);
    }
}

void BDDPhys::ModifierAlbum(AlbumGestion album)
{

    AlbumGestion AncienAlbum = InfosAlbum(QString::number(album.Id_Album));

    bool ArtisteChange=false;

    //L'année, le type ou le nom de l'album ont changé, on met à jour
    if (album.Annee!=AncienAlbum.Annee ||  album.Album!=AncienAlbum.Album || album.Type!=AncienAlbum.Type)
    {
        QString NomSSAcc=album.Album;
        EnleverAccents(NomSSAcc);
        madatabase.exec("UPDATE Album SET Album='"+album.Album+"',AlbumSSAccents='"+NomSSAcc+"',Annee='"+album.Annee+"',Type='"+album.Type+"' WHERE Id_Album='"+QString::number(album.Id_Album)+"'");
        madatabase.exec("UPDATE Phys SET Categorie='"+album.Type+"' WHERE Id_Album='"+QString::number(album.Id_Album)+"'");
    }

    if (album.Artiste!=AncienAlbum.Artiste)
    {
        album.Id_Artiste= lireIDArtiste(album.Artiste,album.Id_Poch);
        ArtisteChange=true;

    }
    for (int cpt=0;cpt<AncienAlbum.titres.count();cpt++)
    {
        TitreGestion titre=album.titres[cpt];
        qDebug() << titre.Id_Titre << titre.Titre;
        if(ArtisteChange==true)
        {
            supprimerRelation(AncienAlbum.titres[cpt].Id_Relation);
            lireIDRelation(album.Id_Album,album.Id_Artiste,AncienAlbum.titres[cpt].Id_Titre,album.Id_Poch);

            bool test=supprimerArtiste(AncienAlbum.Id_Artiste);
            qDebug() << test;
        }
    }


}

void BDDPhys::AjouterErreur(CompilGestion album)
{
    QString chemin="./pochettes/Compils/"+album.Album+".jpg";

    //On vérifie que la pochette n'est déjà pas encore à faire
    QString queryStr="SELECT Id_Pochette FROM Pochette P, ErreurPochettes E WHERE P.Chemin ='"+album.Chem_Poch_Alt+"' OR E.Chemin = '"+chemin+"'";
    QSqlQuery query = madatabase.exec(queryStr);

    if(!query.first())
    {

        queryStr="INSERT INTO ErreurPochettes VALUES(null,'"+QString::number(album.Id_Poch)+"','"+album.Chem_Poch_Alt+"')";
        madatabase.exec(queryStr);
    }
}
int BDDPhys::lireIDPhys(int Id_Album,QString Type,QString CodeBarres)
{
    //On vérifie si l'album existe dans la table Phys ou non
    QString queryStr = "Select Id_Phys As 'Phys' from Phys WHERE Id_Album='" +QString::number(Id_Album)+ "'";
    QSqlQuery  query = madatabase.exec(queryStr);

    if (!query.first()) {
        queryStr="INSERT INTO Phys VALUES (null,'"+QString::number(Id_Album)+"','"+Type+"','"+CodeBarres+"')";
        madatabase.exec(queryStr);

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
    //On récupère les infos de l'album
    AlbumGestion album = InfosAlbum(Id_Album);
    album.Id_Album=Id_Album.toInt();
    //Pour chaque titre, on vérifie si on peut effacer les titres
    int cptnbtitres=0;

    for (int cpt=0;cpt<album.titres.count();cpt++)
    {
        bool supp = supprimerTitredePhys(album.titres[cpt].Id_Titre,album.titres[cpt].Id_Relation);

        if( supp )
        {
            qDebug() << "suppression du Titre" <<   album.titres[cpt].Titre;
          cptnbtitres++;



        }

    }

    //Si on élimine tous les titres, on fait l'album et l'artiste, puis la pochette
    if( cptnbtitres==album.titres.count() )
    {

        bool suppalb= supprimerAlbum(album.Id_Album);
        if( suppalb)
        {
            supprimerPhys(album.Id_Album);
            qDebug() << " Album supprimé : " << album.Album;
            bool artiste=supprimerArtiste(album.Id_Artiste);

            if(artiste)
            {
                qDebug() << " Artiste supprimé : " << album.Artiste;
                supprimerPoch(album.Id_Poch,album.Artiste,album.Album);
            }
        }
    }

}
void BDDPhys::supprimerPhys(int Id_Album)
{
    QString queryStr = "DELETE FROM Phys WHERE Id_Album='"+QString::number(Id_Album)+"'";
    madatabase.exec(queryStr);

}

void BDDPhys::SupprimerCompilPhys(QString Id_Album)
{
    //On récupère les infos de l'album
    CompilGestion album = InfosCompil(Id_Album);

    album.Id_Album=Id_Album.toInt();
    //Pour chaque titre, on vérifie si on peut effacer les titres
    bool titres=true;

    for (int cpt=0;cpt<album.titres.count();cpt++)
    {
        bool supp = supprimerTitredePhys(album.titres[cpt].Id_Titre,album.Id_Relation);
        bool artiste=supprimerArtiste(album.titres[cpt].Id_Artiste);
        qDebug() << album.titres[cpt].Id_Artiste;
        if(artiste)
        {
            qDebug() << " Artiste supprimé : " << album.Artiste;
            supprimerPoch(album.Id_Poch,album.Artiste,album.Album);
            artiste=false;
        }

        if( !supp && titres)
        {
            qDebug() << "suppression du Titre" <<   album.titres[cpt].Id_Titre;
            titres=false;
        }

    }

    //Si on élimine tous les titres, on fait l'album et l'artiste, puis la pochette
    if(titres)
    {
        supprimerAlbum(album.Id_Album);
    }
}


QStringList  BDDPhys::listeArtistes(QString Categorie)
{
    QStringList liste;

    Categorie=choixCategorie(Categorie);

    QString queryStr="SELECT DISTINCT Ar.Artiste, Ar.Id_Artiste FROM Artiste Ar,Relations R, Phys P WHERE P.Id_Album=R.Id_Album AND R.Id_Artiste = Ar.Id_Artiste AND (P.Categorie="+Categorie+") ORDER BY Ar.Artiste";

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
    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al, Phys P, Relations R WHERE R.Id_Artiste="+Id_Artiste+" AND R.Id_Album=P.Id_Album AND Al.Id_Album = P.Id_Album AND (P.Categorie="+Categorie+") ORDER BY Categorie,Al.Annee";
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toString();
    }
    return albums;
}
QStringList BDDPhys::listeCompils(QString Annee)
{
    QStringList albums;

    QString queryStr="SELECT DISTINCT Al.Id_Album FROM Album Al,Phys P WHERE Al.Annee="+Annee+" AND Al.Id_Album=P.Id_Album AND P.Categorie='Compil' ORDER By Al.Album";

    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        albums << rec.value("Id_Album").toString();
    }
    return albums;


}
QList<MP3Gestion> BDDPhys::listeTitresCompil(QString Id_Album)
{
    QList<MP3Gestion> titres;

    QString queryStr="SELECT DISTINCT Titre, Duree, Num_Piste,T.Id_Titre,R.Id_Relation, R.Id_Artiste, Ar.Artiste FROM Titre T, Relations R, Artiste Ar WHERE R.Id_Album="+Id_Album+" AND T.Id_Titre=R.Id_Titre AND Ar.Id_Artiste=R.Id_Artiste ORDER BY Num_Piste";
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        MP3Gestion titre;
        QSqlRecord rec=query.record();

        titre.Num_Piste= rec.value("Num_Piste").toInt();
        titre.Titre=rec.value("Titre").toString().replace("$","'");
        titre.Duree=rec.value("Duree").toString().replace("$","'");
        titre.Id_Titre=rec.value("Id_Titre").toInt();
        titre.Id_Relation=rec.value("Id_Relation").toInt();
        titre.Artiste = rec.value("Artiste").toString().replace("$","'");
        titre.Id_Artiste =rec.value("Id_Artiste").toInt();

        titres << titre;
    }
    return titres;
}

QList<TitreGestion> BDDPhys::listeTitresAlbum(QString Id_Album)
{
    QList<TitreGestion> titres;
    QString queryStr="SELECT DISTINCT Titre, Duree, Num_Piste,T.Id_Titre,R.Id_Relation FROM Titre T, Relations R WHERE R.Id_Album="+Id_Album+" AND T.Id_Titre=R.Id_Titre ORDER BY Num_Piste";
    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        TitreGestion titre;
        QSqlRecord rec=query.record();

        titre.Num_Piste= rec.value("Num_Piste").toInt();
        titre.Titre=rec.value("Titre").toString().replace("$","'");
        titre.Duree=rec.value("Duree").toString().replace("$","'");
        titre.Id_Titre=rec.value("Id_Titre").toInt();
        titre.Id_Relation=rec.value("Id_Relation").toInt();

        titres << titre;
    }
    return titres;
}
AlbumGestion BDDPhys::InfosAlbum(QString Id_Album)
{
    AlbumGestion album;

    QString queryStr="SELECT DISTINCT Al.Album, Annee, P.Categorie, R.Id_Artiste, Al.Id_Pochette, Ar.Artiste FROM Album Al, Phys P,Artiste Ar, Relations R WHERE Al.Id_Album=P.Id_Album AND R.Id_Album=P.Id_Album AND  Ar.Id_Artiste = R.Id_Artiste AND Al.Id_Album="+Id_Album;

    QSqlQuery query=madatabase.exec(queryStr);

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
CompilGestion BDDPhys::InfosCompil(QString Id_Album)
{
    CompilGestion compil;

    QString queryStr="SELECT DISTINCT Al.Album, Annee, P.Categorie, R.Id_Artiste, Al.Id_Pochette, Ar.Artiste FROM Album Al, Phys P,Artiste Ar, Relations R WHERE Al.Id_Album=P.Id_Album AND R.Id_Album=P.Id_Album AND  Ar.Id_Artiste = R.Id_Artiste AND Al.Id_Album="+Id_Album;

    QSqlQuery query=madatabase.exec(queryStr);

    while (query.next() ) {
        QSqlRecord rec=query.record();

        compil.Album=rec.value("Album").toString().replace("$","'");
        compil.Annee=rec.value("Annee").toString();
        compil.Pochette=afficherPochette(Id_Album,"Album");
        compil.Type=rec.value("Categorie").toString();
        compil.Id_Artiste=rec.value("Id_Artiste").toInt();
        compil.Id_Poch=rec.value("Id_Pochette").toInt();
        compil.Artiste=rec.value("Artiste").toString().replace("$","'");

        compil.titres=listeTitresCompil(Id_Album);
    }
    return compil;

}

void BDDPhys::ExporterHTML(QString Type)
{
    QStringList albart=ListeAlbumArtisteExport(Type);

    QString chemin = "F:/"+Type+".html";
    //Récupère le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName = chemin;
    QFile fichier(fileName);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&fichier);
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
    flux << "<Table>";
    int compcouleur= 0;
    for(int cpt=0;cpt<albart.count();cpt=cpt+2)
    {
        if (compcouleur%2==0)
        {
            flux << "<tr bgcolor='beige'><td>" << QString::number((cpt/2)+1).rightJustified(3,'0') << "</td><td>"<< albart[cpt+1]<<"</td><td>"  << albart[cpt] << "</td></tr>"<< endl;
        } else
        {
            flux << "<tr bgcolor='coral'><td>" << QString::number(cpt/2+1).rightJustified(3,'0') << "</td><td>"<< albart[cpt+1]<<"</td><td>"  << albart[cpt] << "</td></tr>"<< endl;
        }
        compcouleur++;
    }
    flux << "</Table>";
}
QStringList BDDPhys::ListeAlbumArtisteExport(QString Type)
{
    QStringList albart;
    QString queryType;
    if (Type!="Tout")
    {
        queryType="AND P.Categorie='"+Type+"'";
    }
    QString QueryStr="SELECT DISTINCT Al.Album, Ar.Artiste FROM Phys P,Album Al, Artiste Ar, Relations R WHERE P.Id_Album=R.Id_Album AND R.Id_Album=Al.Id_Album AND R.Id_Artiste = Ar.Id_Artiste "+queryType+" ORDER BY Ar.Artiste";
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

    QString QueryStr="SELECT Al.Album, Ar.Artiste, P.Categorie, P.CodeBarres FROM Phys P,Album Al, Artiste Ar, Relations R WHERE P.Id_Album=Al.Id_Album AND R.Id_Album=P.Id_Album AND R.Id_Artiste = Ar.Id_Artiste ORDER BY Ar.Artiste";
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
    //Récupère le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName = chemin;
    QFile fichier(fileName);
    fichier.open(QIODevice::WriteOnly | QIODevice::Text);
    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&fichier);
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
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
