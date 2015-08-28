#include "lecteurmodele.h"
#include "lecteurvue.h"



LecteurModele::LecteurModele( QObject* parent ) :
    QObject( parent )
  , m_vue( new LecteurVue )
{

}



LecteurModele::~LecteurModele()
{
    delete m_vue;
}
