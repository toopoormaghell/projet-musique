#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddaffichermp3.h"

namespace Ui {
class OngletMP3;
}

class OngletMP3 : public QWidget
{
    Q_OBJECT

public:
    explicit OngletMP3(QWidget *parent = 0);
    ~OngletMP3();

    void afficherListeArtiste();
    void afficherListeAlbum();
    QString choixArtiste();
    void vider(QString Type);
    void afficherTitresAlbum(QString Album);
    void afficherInfosTitre();
    QString choixMp3();
    void afficherListeType();
    QString choixCategories();
public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);
    void on_Albums_currentRowChanged(int currentRow);
private slots:
    void on_Categories_currentTextChanged(const QString &currentText);

private:
    Ui::OngletMP3 *ui;
    BDDAfficherMp3 m_bddInterface;

};

#endif // ONGLETMP3_H
