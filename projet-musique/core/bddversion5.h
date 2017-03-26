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
private:
    void Reformatage(QString Entite, QString Id_Entite, int Categorie);
    void ExecutionRequeteFormate(QString queryStr, int Categorie);

};

#endif // BDDVERIFICATION_H
