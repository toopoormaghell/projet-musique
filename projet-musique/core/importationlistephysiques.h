#ifndef IMPORTATIONLISTEPHYSIQUES_H
#define IMPORTATIONLISTEPHYSIQUES_H

#include <QDialog>

namespace Ui {
class ImportationListePhysiques;
}

class ImportationListePhysiques : public QDialog
{
    Q_OBJECT

public:
    explicit ImportationListePhysiques(QWidget *parent = 0);
    ~ImportationListePhysiques();

    void initFromFile( const QString& fileName );

private slots:
    void on_m_vueTable_cellClicked(int row, int column);

private:
    Ui::ImportationListePhysiques *ui;

    void afficherContenuFichierSauvegarde( const QString& fileName );
};

#endif // IMPORTATIONLISTEPHYSIQUES_H
