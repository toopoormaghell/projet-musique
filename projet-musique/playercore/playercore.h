#ifndef PLAYERCORE_H
#define PLAYERCORE_H



#include "playercore_global.h"
#include <QScopedPointer>
class PlayerCoreImpl;
class QMediaPlaylist;



class PLAYERCORESHARED_EXPORT PlayerCore
{
public:
    // Default constructor
    PlayerCore();
    // Destructor
    ~PlayerCore();



private:
    // Private implementation of the player
    QScopedPointer<PlayerCoreImpl> m_p;

    // Default copy constructor, not implemented on purpose
    PlayerCore( const PlayerCore& other );
    // Default assignement operator, not implemented on purpose
    PlayerCore& operator=( const PlayerCore& rhs );
};



#endif // PLAYERCORE_H
