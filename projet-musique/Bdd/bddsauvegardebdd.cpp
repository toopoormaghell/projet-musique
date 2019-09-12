#include "bddsauvegardebdd.h"
#include "bddsingleton.h"
#include <QObject>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QImage>
#include <QtSql>

BDDSauvegardeBDD::BDDSauvegardeBDD( QObject* parent ):
    QObject( parent ),
    m_outils ( new OutilsBDD )
{

}
void BDDSauvegardeBDD::sauvegarde()
{
    //Vidage sur le DD du dossier Pochettes
    QString chemin = "H:\\Dropbox\\Projet Musique\\Pochettes";
    m_outils->removeDir( chemin, false );

    //On supprime le fichier def.jpg
    QFile::remove("H:\\Dropbox\\Projet Musique\\Pochettes\\def.jpg");

    //On supprime la BDD
    QFile::remove("H:\\Dropbox\\Projet Musique\\Musique.db");

    //Deuxième étape : on copie la BDD
    QFile::copy("C:\\Projet Musique\\Musique.db","H:\\Dropbox\\Projet Musique\\Musique.db");


    //Troisième étape : on copie le dossier Pochettes
    //  copyDirectoryFiles("C:\\Projet Musique\\Pochettes","H:\\Dropbox\\Projet Musique\\Pochettes",false);
    listePoch();

}

void BDDSauvegardeBDD::listePoch()
{
    QString QueryStr = "SELECT DISTINCT Chemin FROM Pochette";
    QSqlQuery query = madatabase.exec( QueryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        exporterImage( rec.value("Chemin").toString() );
    }

}
void BDDSauvegardeBDD::exporterImage(QString chemin)
{
    QImage image;
    image.load( chemin);
    image.scaled( 100,100 );

    chemin.remove(0, 1);

    chemin.prepend("H:/Dropbox/Projet Musique");

    QDir dossier;
    QDir toCreate( QFileInfo( chemin ).dir() );
    dossier.mkpath( toCreate.path() );

    image.save( chemin );

}
