#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddinterface.h"
#include "affichagecommun.h"
namespace Ui {
class OngletMp3;
}

class OngletMp3 : public QWidget
{
    Q_OBJECT
    
public:
    explicit OngletMp3(QWidget *parent = 0);
    ~OngletMp3();

    void afficherListeArtiste();
    void afficherListeCategories();
    void afficherListeAlbum();
    void afficherTitresAlbum(QString Album);
    void afficherInfosTitre();
    void afficherSimilaires();

    QString getSelectedTitleId() const;

    QString choixCategorie();
    QString choixArtiste();
    QString choixMp3();
    QString choixSimilaires();

    int changerAlbum(int Id_Titre);
    void changerMp3();
    int changerArtiste(int Id_Artiste);
    void afficherListeAnnees();
    void afficherListeMp3Compil();
    QString AnneesSwitch(int annee);

    void Playlist();
    void vider(QString Type);

public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);
private slots:
    void on_Categories_currentTextChanged(const QString &currentText);

    void on_Albums_currentRowChanged(int currentRow);

    void on_Similaires_doubleClicked(const QModelIndex &index);

    void on_Bouton_Playlist_clicked();

private:
    Ui::OngletMp3 *ui;
    BDDInterface m_bddInterface;
    AffichageCommun temp;
    };

#endif // ONGLETMP3_H
