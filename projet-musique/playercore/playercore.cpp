#include "playercore.h"
#include <QMediaPlayer>



// Private implementation
class PlayerCoreImpl
{
public:
    // Qt object which is able to read multimedia files
    QMediaPlayer m_player;
};




PlayerCore::PlayerCore():
    m_p( new PlayerCoreImpl )
{

}



PlayerCore::~PlayerCore()
{
}
