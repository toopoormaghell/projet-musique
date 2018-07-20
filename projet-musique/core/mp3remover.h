#ifndef MP3REMOVER_H
#define MP3REMOVER_H

#include <QObject>
#include <QMap>
class QStringList;

class MP3Remover : public QObject
{
    Q_OBJECT

    typedef QMap<int, QStringList> ListOfPathsType;
public:
    explicit MP3Remover(ListOfPathsType const& listOfPaths, QObject *parent = nullptr);

signals:
    void finished();
    void askedRemoval(int id);
    void processedAnotherMP3(int currentValue, int totalCount);

public slots:
    void process();

private:
    ListOfPathsType m_listOfPaths;
};

#endif // MP3REMOVER_H
