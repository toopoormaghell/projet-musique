#ifndef BARREAVANCEMENT_H
#define BARREAVANCEMENT_H



#include <QProgressBar>
class QString;



/**
 * @brief Proxy class for progress bar
 */
class BarreAvancement : public QProgressBar
{
    Q_OBJECT

public:
    explicit BarreAvancement( QWidget* parent = 0 );
    ~BarreAvancement();

public slots:
    /**
     * @brief Set the progress bar to its default state (nil value and no message)
     */
    void reset();

    /**
     * @brief Changes the position of the bar and show the given message
     * @param percent Percentage (between 0 and 1) of the bar to display
     * @param message Text to show above the bar
     */
    void update( const float percent, const QString& message = QString() );
};

#endif // BARREAVANCEMENT_H
