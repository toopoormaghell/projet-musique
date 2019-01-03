#include "bddsauvegardebdd.h"
#include "bddsingleton.h"
#include <QObject>
#include <QDir>
#include <QFile>
#include <QDebug>

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
    copyDirectoryFiles("C:\\Projet Musique\\Pochettes","H:\\Dropbox\\Projet Musique\\Pochettes",false);

}
bool BDDSauvegardeBDD::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /* if directory don't exists, build it */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();

    foreach(QFileInfo fileInfo, fileInfoList){

        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /* if it is directory, copy recursively */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }
        else{            /* if coverFileIfExist == true, remove old file first */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            // files copy
            if(!QFile::copy(fileInfo.filePath(),
                            targetDir.filePath(fileInfo.fileName()))){
                return false;
            }
        }
    }
    return true;
}
