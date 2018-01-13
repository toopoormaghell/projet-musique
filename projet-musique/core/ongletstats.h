#ifndef ONGLETSTATS_H
#define ONGLETSTATS_H
#include "bddstats.h"
#include <QWidget>

namespace Ui
{
    class OngletStats;
}

class OngletStats : public QWidget
{
    Q_OBJECT

public:
    explicit OngletStats( QWidget* parent = 0 );
    ~OngletStats();
    void AfficherInfos();
private slots:
    void on_ArtistesDansCompil_currentRowChanged( int currentRow );

    void on_VoirListeAlbSSMP3_clicked();

private:
    Ui::OngletStats* ui;
    bddstats m_bddInterface;

    void AfficherInfosCategoriesMP3();
    void AfficherInfosCategoriesPhys();
    void AfficherArtistesCompilMP3();
    int choixArtiste();
    void AfficherMP3ArtisteCompilMP3();
    void AfficherDoublonsMP3();
};

#endif // ONGLETSTATS_H
