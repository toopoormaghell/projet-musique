#include "bddexporterhtml.h"
#include <QtSql>
#include "bddsingleton.h"
#include "bddalbum.h"
#include "bddtype.h"
#include "bddsauvegardebdd.h"
#include <QObject>
#include <QDir>
#include <QFile>
#include "bddpoch.h"
#include <QDebug>

BDDExporterHTML::BDDExporterHTML( QObject* parent ) :
    QObject( parent ),
    m_outils ( new OutilsBDD )
{

}

void BDDExporterHTML::exporterHTML()
{

    //Vidage sur le DD du dossier Pochettes
    QString chemin = "H:\\Site\\pochettes";
    m_outils->removeDir( chemin, false );

    for ( int i = 1; i < 5; i++ )
    {
        QStringList albart = ListeAlbumSauvegarde( i );
        QString chemin = "H:/Site/Tout.html";
        switch ( i )
        {
        case 1 :
            chemin = "H:/Site/Albums.html";
            exporterAlbum( albart, chemin );
            break;
        case 2 :
            chemin = "H:/Site/Compils.html";
            exporterCompil(albart, chemin);
            break;
        case 3 :
            chemin = "H:/Site/Singles.html";
            exporterAlbum( albart, chemin );
            break;
        case 4 :
            chemin = "H:/Site/Chansons.html";
            exporterChansons( albart, chemin );
            break;
        }

    }


}

QStringList BDDExporterHTML::ListeAlbumSauvegarde(int Cate)
{
    QStringList albart;
    QString QueryStr;

    switch ( Cate )
    {
    case 1 :
        QueryStr = "SELECT DISTINCT B.Album, Ar.Artiste, Poch.Chemin, Ar.Id_Artiste FROM Phys P, Album B, Artiste Ar, Relations R, Pochette Poch WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album AND R.Id_Artiste = Ar.Id_Artiste AND P.Support='1' AND Poch.Id_Pochette=B.Id_Pochette ORDER BY Ar.Artiste, B.Album";
        break;
    case 2 :
        QueryStr = "SELECT DISTINCT B.Album, B.Annee, Poch.Chemin FROM Phys P,Album B,Relations R, Pochette Poch WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album  AND P.Support='2'  AND Poch.Id_Pochette=B.Id_Pochette GROUP BY Album ORDER BY B.Annee DESC, B.Album";
        break;
    case 3 :
        QueryStr = "SELECT DISTINCT B.Album, Ar.Artiste, Poch.Chemin, Ar.Id_Artiste FROM Phys P, Album B, Artiste Ar, Relations R, Pochette Poch WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album AND R.Id_Artiste = Ar.Id_Artiste AND P.Support='3' AND Poch.Id_Pochette=B.Id_Pochette ORDER BY Ar.Artiste, B.Album";
        break;
    case 4 :
        QueryStr = "SELECT DISTINCT Album, Titre, Artiste FROM Phys P,Album B,Relations R, Titre T, Artiste Ar WHERE P.Id_Album=R.Id_Album AND R.Id_Album=B.Id_Album  AND P.Support='2' AND T.Id_Titre=R.Id_Titre AND Ar.Id_Artiste=R.Id_Artiste GROUP BY Titre ORDER BY Artiste, Titre";
        break;
    }

    QSqlQuery query = madatabase.exec( QueryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        switch ( Cate )
        {
        case 1:
            albart <<  rec.value( "Album" ).toString().replace( "$", " " ) << rec.value( "Artiste" ).toString().replace( "$", " " ) << rec.value( "Chemin" ).toString() << nombrecdparartiste( rec.value( "Id_Artiste" ).toString(), "1" );
            break;
        case 2 :
            albart << rec.value( "Album" ).toString().replace( "$", " " ) << rec.value( "Annee" ).toString() <<  rec.value( "Chemin" ).toString();
            break;
        case 3:
            albart <<  rec.value( "Album" ).toString().replace( "$", " " ) << rec.value( "Artiste" ).toString().replace( "$", " " ) << rec.value( "Chemin" ).toString() << nombrecdparartiste( rec.value( "Id_Artiste" ).toString(), "3" );
            break;
        case 4:
            albart << rec.value( "Artiste" ).toString().replace( "$", " " ) << rec.value( "Album" ).toString().replace( "$", " " ) << rec.value( "Titre" ).toString().replace( "$", " " );
            break;
        default:
            albart <<  rec.value( "Album" ).toString().replace( "$", " " ) << rec.value( "Artiste" ).toString().replace( "$", " " ) << rec.value( "Chemin" ).toString() << nombrecdparartiste( rec.value( "Id_Artiste" ).toString(), "1" );

        }

    }
    return albart;

}
QString BDDExporterHTML::nombrecdparartiste( QString Id_Artiste, QString Support )
{
    QString QueryStr =" SELECT COUNT( DISTINCT B.Album ) AS 'Nb' FROM Phys P, Album B WHERE B.Id_Album = P.Id_Album AND B.Id_Artiste='" + Id_Artiste + "' AND P.Support = '" + Support + "' ";
    QSqlQuery query = madatabase.exec( QueryStr );

    if ( query.first() )
    {
        QSqlRecord rec = query.record();

        return rec.value("Nb").toString();
    } else
    {
        return "0";
    }

}
void BDDExporterHTML::exporterCompil(QStringList albart, QString chemin)
{
    QString an="";
    //Récupère le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName =  chemin;
    QFile fichier( fileName );
    fichier.open( QIODevice::WriteOnly | QIODevice::Text );
    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux( &fichier );
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8

    flux << textedebut();

    for ( int cpt = 0; cpt < albart.count(); cpt = cpt + 3 )
    {
        QString alb = albart[cpt];
        QString annee = albart[cpt + 1 ];
        QString chemin_poch = albart[cpt + 2];

        if ( annee != an)
        {
            flux << "<h2>" << annee  <<" </h2>";
            an = annee;
        }

        flux << "<img src ='" <<  chemin_poch << "' alt='" << chemin_poch << "' title='" << alb.replace( "'", " " ) << "' height='100px'>" << endl;
        exporterImage( chemin_poch );
    }

    flux <<textefin();
}
void BDDExporterHTML::exporterChansons( QStringList albart, QString chemin )
{
    //Récupère le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName = chemin;
    QFile fichier( fileName );
    fichier.open( QIODevice::WriteOnly | QIODevice::Text );
    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux( &fichier );
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8

    flux << textedebut() << "<table>";
    int compartiste = 0;

    for ( int cpt = 0; cpt < albart.count(); cpt = cpt + 3 )
    {
        if ( compartiste % 2 == 0 )
        {
            flux << "<tr bgcolor='beige'><td>" << QString::number( ( cpt / 2 ) + 1 ).rightJustified( 3, '0' ) << "</td><td>" << albart[cpt] << "</td><td>"  << albart[cpt + 2] << "</td><td>" << albart[cpt + 1] << "</td></tr>" << endl;
        }
        else
        {
            flux << "<tr bgcolor='coral'><td>" << QString::number( ( cpt / 2 ) + 1 ).rightJustified( 3, '0' ) << "</td><td>" << albart[cpt] << "</td><td>"  << albart[cpt + 2] << "</td><td>" << albart[cpt + 1] << "</td></tr>" << endl;
        }
        compartiste++;
    }
    flux << textefin();
}
void BDDExporterHTML::exporterAlbum( QStringList albart, QString Chemin )
{
    QString artiste="";
    //Récupère le fichier et l'ouvre avec lecture lignes par lignes
    QString fileName = Chemin;
    QFile fichier( fileName );
    fichier.open( QIODevice::WriteOnly | QIODevice::Text );
    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux( &fichier );
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8

    flux << textedebut();

    for ( int cpt = 0; cpt < albart.count(); cpt = cpt + 4 )
    {
        QString alb = albart[cpt];
        QString art = albart[cpt + 1 ];
        QString chemin_poch = albart[cpt + 2];
        QString nb_alb = "0";
        nb_alb = albart[cpt + 3 ];


        if ( art != artiste)
        {
            flux << "<h2>" << art  <<" (" << nb_alb << ")</h2>";
            artiste = art;
        }

        flux << "<img src ='" <<  chemin_poch << "' alt='" << chemin_poch << "' title='" << alb.replace( "'", " " ) << "' height='100px'>" << endl;
        exporterImage( chemin_poch);

    }
    flux << textefin();
}

void BDDExporterHTML::exporterImage(QString chemin_poch)
{

    QImage image;
    image.load( chemin_poch);
    image.scaled( 100,100 );

    chemin_poch.remove(0, 1);

    chemin_poch.prepend("H:/Site");

    QDir dossier;
    QDir toCreate( QFileInfo( chemin_poch ).dir() );

    if ( ! dossier.mkpath( toCreate.path() ) )
    {
        qDebug() << chemin_poch;
}

        image.save( chemin_poch );

}
QString BDDExporterHTML::textedebut()
{
    return "<html><head><script  src='https://code.jquery.com/jquery-3.2.1.js'></script><script  src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script><head><body><input type='text' id='findField' value='' size='20' /><button id='but'>Chercher</button>";
}

QString BDDExporterHTML::textefin()
{
    return "<script type='text/javascript'>        function FindNext () {            var str = document.getElementById ('findField').value;            if (str == '') {                alert ('Champs vide');             return;            }             var supported = true; var found = false;   			 if (window.find) {    	supported = false;  found = window.find (str);            }            else {                if (document.selection && document.selection.createRange) {                     var textRange = document.selection.createRange ();  if (textRange.findText) {    supported = true;     if (textRange.text.length > 0) { textRange.collapse (true); textRange.move ('character', 1);           } found = textRange.findText (str); if (found) { textRange.select ();  }  }   }   }      }    </script>  <script>  $(document).ready(function() {  $('#but').on('click', function() { 		var val = $('#search').val();		FindNext (); }); $('#findField').on('focus', function() { $('html, body').animate({scrollTop: 0},'slow'); }); }); </script> </body> </html>";
}
