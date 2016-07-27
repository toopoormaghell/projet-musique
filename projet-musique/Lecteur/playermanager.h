#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStringList>

class DialogControles;
namespace Ui {
class PlayerManager;
}

class PlayerManager : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerManager(QWidget *parent = 0);
    ~PlayerManager();
    void setDialogControles( DialogControles* dialogControles);
    void setPlaylist(QStringList temp);

signals:
    void changerMp3(QString temp);
    void PremierMP3 ( QString temp);
    void SupprimerdansPlaylist ( QStringList temp);

private slots:
    void on_Precedent_clicked();
    void on_Suivant_clicked();

    void on_Aleatoire_clicked();

    void on_Dossiers_clicked();

    void on_Suppression_clicked();

    void on_Playlist_clicked(const QModelIndex &index);

private:
    Ui::PlayerManager *ui;
    DialogControles* m_controles;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    bool m_aleatoire;
    void afficherPlaylist();
    QString ExtraireInfosMp3(QString mp3);
    void afficherIcones();
    QStringList m_listechemins;
};

#endif // PLAYERMANAGER_H
