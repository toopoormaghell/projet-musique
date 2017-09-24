#ifndef BDDVERIFICATION_H
#define BDDVERIFICATION_H
#include <QString>


class BDDVersion5
{
public:
    BDDVersion5();
    void VirguleArtistes();
    void CompilsPhysiqueMp3();
    void SupprimerDoublonsArtiste();
    void SupprimerDoublonsAlbum();
    void ReformatageCompletEntites();
    void ChangerArtisteDansCompilAlbum();
    void DoublonsTitresEnlever();
    void ChangerCategorie();
    void passageversion5();
    void ModificationBDD();
    void MajusculesCompletEntites();
private:
    void Reformatage(QString Entite, QString Id_Entite, int Categorie);
 void Majuscules(QString Entite, QString Id_Entite, int Categorie);
    void ExecutionRequeteFormate(QString queryStr, int Categorie);
  void ExecutionRequeteMajuscules(QString queryStr, int Categorie);
};

#endif // BDDVERIFICATION_H
