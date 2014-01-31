#ifndef ONGLETMP3_H
#define ONGLETMP3_H

#include <QWidget>
#include "bddinterface.h"
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
    void lectureMp3(bool lect);
public slots:
    void on_Artistes_currentTextChanged(const QString &arg1);
private slots:
    void on_Categories_currentTextChanged(const QString &currentText);
    void on_Lecture_clicked();
    void on_Stop_clicked();

private:
    Ui::OngletMp3 *ui;
    BDDInterface m_bddInterface;
};

#endif // ONGLETMP3_H
