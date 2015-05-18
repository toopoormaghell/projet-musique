#ifndef BDDGENERAL_H
#define BDDGENERAL_H

#include <QObject>

class bddgeneral : public QObject
{
public:
    explicit bddgeneral(QObject* parent=0);

    //Confguration du projet
    QString getdossierpardef();
    void EnregistrerDossierParDef(QString doss);
    void CopierBDD();
    void ChargerBDD();
    void verifierBDD();

    //COnfiguration de l'actualiser MP3
    bool ActualiserAlbums();
    bool ActualiserCompil();
    bool ActualiserLives();
    void EnregistrerActuAlbums(bool check);
    void EnregistrerActuCompil(bool check);
    void EnregistrerActuLives(bool check);

    //En rapport avec l'API
    QString getjetonAcces();
    QString getjetonSecret();
    void changerjetonSecret(QString jeton);
    void changerjetonAcces(QString jeton);

};

#endif // BDDGENERAL_H
