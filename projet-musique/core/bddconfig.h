#ifndef BDDCONFIG_H
#define BDDCONFIG_H

#include <QObject>

class BDDConfig : public QObject
{
    Q_OBJECT
public:
    explicit BDDConfig( QObject* parent = 0 );

    QString recupdossierpardef();
    void EnregistrerDossierParDef( QString doss );
    bool ActualiserAlbums();
    bool ActualiserCompil();
    bool ActualiserLives();
    void EnregistrerActuAlbums( bool check );
    void EnregistrerActuCompil( bool check );
    void EnregistrerActuLives( bool check );
private:

};

#endif // BDDCONFIG_H
