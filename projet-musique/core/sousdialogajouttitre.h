#ifndef SOUSDIALOGAJOUTTITRE_H
#define SOUSDIALOGAJOUTTITRE_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class SousDialogAjoutTitre;
}

class SousDialogAjoutTitre : public QDialog
{
    Q_OBJECT

public:
    explicit SousDialogAjoutTitre(int Type, QWidget *parent = 0 );
    ~SousDialogAjoutTitre();

    QString m_Duree;
    QString m_Titre;
    QString m_Artiste;
signals:
    void enregistr(QString, QString, QString);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_Sauvegarde_clicked();

private:
    Ui::SousDialogAjoutTitre *ui;

    void RecupererDonnees();
};

#endif // SOUSDIALOGAJOUTTITRE_H
