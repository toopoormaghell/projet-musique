#include "lecteurmodele.h"
#include "lecteurvue.h"



LecteurModele::LecteurModele( QObject* parent ) :
    QObject( parent )
  , m_vue( NULL )
{
}



LecteurModele::~LecteurModele()
{
}



void LecteurModele::setGui( const LecteurVue& gui )
{
    delete m_vue;
    m_vue = &gui;
}
