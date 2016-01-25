#include "lecteurmodele.h"
#include "lecteurvue.h"
#include <QMediaPlayer>



LecteurModele::LecteurModele( QObject* parent ) :
    QObject( parent )
  , m_vue( new LecteurVue )
  , m_player( new QMediaPlayer )
{
    connecteSignauxDeGui();
}



LecteurModele::~LecteurModele()
{
}



QWidget* LecteurModele::getGui() const
{
    return m_vue;
}



void LecteurModele::on_lectureDemandee()
{
    qDebug() << "LectureModele::on_lectureDemandee()";
}



void LecteurModele::on_pauseDemandee()
{
    qDebug() << "LectureModele::on_pauseDemandee()";
}



void LecteurModele::connecteSignauxDeGui()
{
    if ( m_vue != NULL )
    {
        // Connecte au signal indiquant que la lecture a été demandee
        QObject::connect( m_vue, SIGNAL( lectureDemandee() ), this, SLOT( on_lectureDemandee() ) );
        // Connecte au signal indiquant que la pause a été demandee
        QObject::connect( m_vue, SIGNAL( pauseDemandee() ), this, SLOT( on_pauseDemandee() ) );
    }
}



void LecteurModele::deconnecteSignauxDeGui()
{
    if ( m_vue != NULL )
    {
        // Deconnecte du signal indiquant que la lecture a été demandee
        QObject::disconnect( m_vue, SIGNAL( lectureDemandee() ), this, SLOT( on_lectureDemandee() ) );
        // Connecte au signal indiquant que la pause a été demandee
        QObject::disconnect( m_vue, SIGNAL( pauseDemandee() ), this, SLOT( on_pauseDemandee() ) );
    }
}
