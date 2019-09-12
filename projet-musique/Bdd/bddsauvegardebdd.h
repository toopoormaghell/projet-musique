#ifndef BDDSAUVEGARDEBDD_H
#define BDDSAUVEGARDEBDD_H

#include "outilsbdd.h"
#include "bdd_global.h"
#include <QObject>
#include <QDir>

class BDDSHARED_EXPORT BDDSauvegardeBDD: public QObject
{
public:
    explicit  BDDSauvegardeBDD(QObject* parent = nullptr);
    void sauvegarde();

//    bool copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist);

    void exporterImage(QString chemin);
    void listePoch();
private:
    OutilsBDD* m_outils;

};

#endif // BDDSAUVEGARDEBDD_H
