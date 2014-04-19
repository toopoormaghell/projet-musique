#ifndef DIALOGUEAJOUTERPHYSIQUE_H
#define DIALOGUEAJOUTERPHYSIQUE_H

#include <QDialog>
#include "bddinterface.h"
namespace Ui {
class DialogueAjouterPhysique;
}

class DialogueAjouterPhysique : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogueAjouterPhysique(QWidget *parent = 0);
    ~DialogueAjouterPhysique();

    QString getCodeBarre() const;
    QString getType() const;
    
    void ajouterAlbum();
    void listeNumeros();
    void AffichageArtistesCompil();

private slots:
    void on_AjouterTitre_clicked();
    void on_Supprimer_clicked();
    void on_ChangerPochette_clicked();
    void on_buttonBox_accepted();
    void on_AjouterTitre_2_clicked();
    void on_m_type_currentIndexChanged(const QString &arg1);
    void on_Codebarres_clicked();

private:
    Ui::DialogueAjouterPhysique *ui;
  BDDInterface m_bddInterface;
};

#endif // DIALOGUEAJOUTERPHYSIQUE_H
