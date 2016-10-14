#ifndef DIALOGAJOUTTITRE_H
#define DIALOGAJOUTTITRE_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui
{
    class DialogAjoutTitre;
}

class DialogAjoutTitre : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjoutTitre( int Type, int Nb_Piste, QWidget* parent = 0 );
    ~DialogAjoutTitre();

    QString m_Piste;
    QString m_Titre;
    QString m_Artiste;
    void ActualiserOnglet( int Type );

signals:
    void enregistr( QString, QString, QString );

private slots:
    void on_buttonBox_clicked( QAbstractButton* button );
    void on_Sauvegarde_clicked();
    void Raccourci();
private:
    Ui::DialogAjoutTitre* ui;
    void RecupererDonnees();
    void AjouterListeTitres();
    void AjouterListeArtistes();
};

#endif // DIALOGAJOUTTITRE_H
