#ifndef BDDGESTIONMP3_H
#define BDDGESTIONMP3_H

#include <QObject>
#include <fileref.h>
#include <id3v2/frames/attachedpictureframe.h>
#include <id3v2/id3v2tag.h>
#include <QStringList>
#include <QMap>

/************************************************************************
** Fonctions de la classe:
*************************************************************************
**      ActualiserMP3:
*************************************************************************
 * demarrerActualiser()
 *  initialise la liste des catégories ( m_Categories ) par l'appel de la fonction listeCategoriesActualiser()
 *  init()
 *      initialise m_type ( dossiercategorie() )
 *      creerfilefichiers()
 *          initialise m_Chemins ( recupererMp3() )
 *          dossiercategorie() et getdossierpardef()
 *              initialise m_filelist
 *      step()
 *          boucle tant que m_filelist n'est pas finie
 *              actualiserMP3()
 *                  SousCatParChemin() -> permet de faire des sous-categories selon le chemin
 *                  ImageAlbum() -> récupère une image du fileref de taglib
 *                  Entre dans la BDD les infos du MP3
 *          boucle finie
 *              supprimerAnciensMp3()
 *                  supprstep()
 *                      boucle tant que m_chemins n'est pas finie
 *                          si l'id du mp3 n'a pas été trouvé
 *                              SupprimerenBDDMP3()
 *                                  Supprime dans la BDD les infos du MP3
 *                      boucle sur les catégories
 *                      appel de la fonction qui supprime les dossiers vides
*************************************************************************
** ViderBDD() : permet d'enlever les MP3 de la BDD
** stop-clique() : arrête d'actualiser les mp3
** pourcentage() et fin() sont des signaux pour l'ongletMP3
*************************************************************************/
class BDDGestionMp3 : public QObject
{
    Q_OBJECT
public:
    explicit BDDGestionMp3( QObject *parent = 0 );
    void demarreractualiser();

    QString m_fichierlu;
    int m_pourcentage;
    void ViderBDD();
signals:
    void pourcentage();
    void fin();
private slots:
    void init();
    void step();
    void stop_clique();
    void supprstep();
private:
    //Actualiser MP3 + fonctions associées
    void actualiserMp3( QString chemin );
    QString getdossierpardef();
    void SousCatParChemin( QString chemin );
    QImage ImageAlbum( const TagLib::FileRef& f );
    void creerfilefichiers();
    //Actualiser MP3 + Supprimer MP3
    void supprimerAnciensMP3();
    void recupererMp3( int Type );
    void SupprimerenBDDMP3( int Id );
    void listeCategoriesActualiser();
    QString dossiercategorie();

    QStringList m_filelist;
    QMap < int, QStringList > m_Chemins;
    int m_type;
    int m_iteration;
    int m_souscat;
    QList<int> m_Categories;
    QMap < int, QStringList >::const_iterator m_iterateur;


};

#endif // BDDGESTIONMP3_H


