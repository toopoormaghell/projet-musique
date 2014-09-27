#ifndef DIALOGUEARTISTESINVERSES_H
#define DIALOGUEARTISTESINVERSES_H

#include <QDialog>
#include "bddinterface.h"
namespace Ui {
class DialogueArtistesInverses;
}

class DialogueArtistesInverses : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogueArtistesInverses(QWidget *parent = 0);
    ~DialogueArtistesInverses();
    
    void AfficherListeArtistes(QStringList ListeArtistes);

    QStringList InitialiserListeArtistes();
    QStringList InitialiserListeArtistesInverses();
    void EchangerListeArtistes();
    void GererListeArtistes(QStringList Liste);
    QStringList RecupererListeArtiste();
    void GererListeArtistesInvers(QStringList Liste);
    void AfficherListeInversee(QStringList ListeArtistes);
    void EnregistrerArtistes();
private slots:
    void on_ListeArtistes_currentRowChanged(int currentRow);

    void on_ListeInversee_currentRowChanged(int currentRow);

    void on_Inversion_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogueArtistesInverses *ui;
    BDDInterface m_bddInterface;
};

#endif // DIALOGUEARTISTESINVERSES_H
