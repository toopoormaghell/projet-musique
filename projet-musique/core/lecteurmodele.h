#ifndef LECTEURMODELE_H
#define LECTEURMODELE_H



#include <QObject>
class LecteurVue;



class LecteurModele : public QObject
{
    Q_OBJECT
public:
    explicit LecteurModele( QObject* parent = 0 );
    virtual ~LecteurModele();

    // Permet de modifier la GUI liee au modele
    void setGui( const LecteurVue& gui );



private:
    // GUI du lecteur
    LecteurVue const* m_vue;
};



#endif // LECTEURMODELE_H
