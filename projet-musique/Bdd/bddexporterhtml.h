#ifndef BDDEXPORTERHTML_H
#define BDDEXPORTERHTML_H

#include <QObject>
#include "bdd_global.h"
#include "outilsbdd.h"

class BDDSHARED_EXPORT BDDExporterHTML: public QObject
{
    Q_OBJECT
public:
   explicit BDDExporterHTML( QObject* parent = nullptr );
     void exporterHTML();
     QStringList ListeAlbumSauvegarde( int Cate );

private:
    static QString nombrecdparartiste(QString Id_Artiste , QString Support);
    OutilsBDD* m_outils;
    void exporterCompil(QStringList albart, QString chemin);
    void exporterChansons(QStringList albart, QString chemin);
    void exporterAlbum(QStringList albart, QString Chemin);

    void exporterImage(QString chemin_poch);
    QString textedebut();
    QString textefin();
};

#endif // BDDEXPORTERHTML_H
