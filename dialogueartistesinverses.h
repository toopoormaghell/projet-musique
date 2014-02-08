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
    void EchangerListeArtistes(QStringList &Liste, int Position, QString Changement);
    void GererListeArtistes(QStringList Liste);
    QStringList RecupererListeArtiste();
    QStringList RecupererListeArtisteInvers();
    void GererListeArtistesInvers(QStringList Liste);
    void AfficherListeInversee(QStringList ListeArtistes);
private slots:
    void on_ListeArtistes_currentRowChanged(int currentRow);

    void on_ListeInversee_currentRowChanged(int currentRow);

    void on_Inversion_clicked();

private:
    Ui::DialogueArtistesInverses *ui;
    BDDInterface m_bddInterface;
};

#endif // DIALOGUEARTISTESINVERSES_H
