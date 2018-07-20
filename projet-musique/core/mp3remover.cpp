#include "mp3remover.h"
#include <QStringList>

MP3Remover::MP3Remover(ListOfPathsType const& listOfPaths, QObject *parent) :
    QObject(parent)
  , m_listOfPaths(listOfPaths)
{
}

void MP3Remover::process()
{
    ListOfPathsType::const_iterator item = m_listOfPaths.constBegin();
    int counter = 0;
    for ( ; item != m_listOfPaths.constEnd(); ++item )
    {
        const int& key = item.key();
        const QStringList& value = item.value();
        if ( value[1] != "trouve" )
        {
            emit askedRemoval(key);
        }
        ++counter;
        emit processedAnotherMP3(counter, m_listOfPaths.size());
    }
    emit finished();
}
