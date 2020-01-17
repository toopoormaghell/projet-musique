#ifndef DIALOGAJOUTPOCH_H
#define DIALOGAJOUTPOCH_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
    class DialogAjoutPoch;
}

class DialogAjoutPoch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAjoutPoch( QString artiste, QWidget *parent = nullptr);
    ~DialogAjoutPoch();

signals:
    void fini();
private slots:
    void on_Parcourir_clicked();
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogAjoutPoch *ui;
    QString m_artiste;
    QString m_chemin;
    QString m_album;
    QImage m_poch;
    void AfficherPoch();
    void EnregistrerPochette();
};

#endif // DIALOGAJOUTPOCH_H
