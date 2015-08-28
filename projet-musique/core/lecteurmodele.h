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



private:
    LecteurVue* m_vue;
};



#endif // LECTEURMODELE_H
