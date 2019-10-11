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

private:

    OutilsBDD* m_outils;


    void exporterImage(QString chemin_poch);

    QStringList listeImages();
};

#endif // BDDEXPORTERHTML_H
