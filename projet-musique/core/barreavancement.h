#ifndef BARREAVANCEMENT_H
#define BARREAVANCEMENT_H

#include <QWidget>

namespace Ui {
class BarreAvancement;
}

class BarreAvancement : public QWidget
{
    Q_OBJECT
    
public:
    explicit BarreAvancement(QWidget *parent = 0);
    ~BarreAvancement();

    void notifierPouah( const QString& chemin, const float pourcentage );
    void init();
    
private:
    Ui::BarreAvancement *ui;
};

#endif // BARREAVANCEMENT_H
