#ifndef BDDFUSION_H
#define BDDFUSION_H

#include "util.h"
#include "bdd_global.h"


class BDDAlbum;
class BDDPoch;
class BDDMp3;
class BDDSHARED_EXPORT BDDFusion
{

public:
    explicit BDDFusion();

    void fusionalbums(QPair<QString, QString> Choix1_Album, QPair<QImage, QString> Choix1_Pochette, QList<TitresPhys> Choix1_Titres, QPair<QString, QString> Choix2_Album, QPair<QImage, QString> Choix2_Pochette, QList<TitresPhys> Choix2_Titres, int ChoixFusion_Annee, int ChoixFusion_Album, int ChoixFusion_Pochette, QStringList ChoixFusion_Titres);

private:
    void fusionnerAlb(BDDAlbum *Alb, int ChoixFusion_Annee, BDDPoch *Poch);
    void fusionnerAlb(BDDAlbum *Alb, int ChoixFusion_Annee);
    void SupprimerPoch(BDDPoch *Poch, int NouvelId);
    void SupprimerAlbum(BDDAlbum *Alb, int NouvelId);

    QList<TitresPhys> m_Choix1_Titres;
    QList<TitresPhys> m_Choix2_Titres;
    int RecupererMP3(QString choix);
int RecupererNouveauTitre(int Ancien);


void SupprimerTitresEnTrop(QList<TitresPhys> titresph, QString AlbumChoix, int ChoixFusion_Annee, QString PochChoix);
};

#endif // BDDFUSION_H