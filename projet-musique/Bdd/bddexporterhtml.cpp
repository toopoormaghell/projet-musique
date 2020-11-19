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

    QStringList listeChemin = listeImages();

    for (int i =0 ; i< listeChemin.count() ; i++ )
    {
        exporterImage( listeChemin[i] );
    }


}
QStringList BDDExporterHTML::listeImages()
{
    QStringList liste;

    QString queryStr = "SELECT P.Chemin FROM Pochette P, Phys Ph, Album A WHERE P.Id_Pochette = A.Id_Pochette AND Ph.Id_Album = A.Id_Album ";
    QSqlQuery query = madatabase.exec( queryStr );

    while ( query.next() )
    {
        QSqlRecord rec = query.record();
        QString temp = rec.value("Chemin").toString();
        liste << temp;

    }


    return liste;
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
