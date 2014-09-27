#ifndef SAISIETOKENSAPI_H
#define SAISIETOKENSAPI_H

#include <QDialog>

namespace Ui {
class SaisieTokensAPI;
}

class SaisieTokensAPI : public QDialog
{
    Q_OBJECT
    
public:
    explicit SaisieTokensAPI( const QString& jetonAcces, const QString& jetonSecret, QWidget *parent = 0);
    ~SaisieTokensAPI();

    QString getJetonAcces() const;
    QString getJetonSecret() const;
    
private:
    Ui::SaisieTokensAPI *ui;

    void initTokens( const QString& jetonAcces, const QString& jetonSecret );
};

#endif // SAISIETOKENSAPI_H
