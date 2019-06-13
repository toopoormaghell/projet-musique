#ifndef DISCINFO_H
#define DISCINFO_H

#include <discinfo_export.h>
#include <string>
#include <QObject>
#include <QSslError>
class QNetworkReply;

namespace discinfo
{
class DISCINFO_EXPORT Discogs : public QObject
{
    Q_OBJECT

public:
    // Default constructor
    Discogs() = default;
    // Copy constructor
    Discogs(const Discogs& other) = default;
    // Move constructor
    Discogs(Discogs&& other) = default;
    // Destructor
    ~Discogs() = default;
    // Assignement operator
    Discogs& operator=(const Discogs& rhs) = default;

    /**
     * @brief Get information on a disc from its EAN
     * @param ean Bar code of the disc
     * @return A string containing information on the disc.
     */
    void requestFromEan(const std::string& ean);
    void requestFromReleaseId(const std::string& releaseId);

Q_SIGNAL
    void success(QString reply);

Q_SLOT
    void slotFinished(QNetworkReply* reply);
};
}

#endif
