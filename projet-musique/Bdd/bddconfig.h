#ifndef BDDCONFIG_H
#define BDDCONFIG_H

#include <QObject>
#include "bdd_global.h"

class BDDSHARED_EXPORT BDDConfig : public QObject
{
    Q_OBJECT
public:
    explicit BDDConfig( QObject* parent = nullptr );

    static  QString recupdossierpardef();
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
