#include "saisietokensapi.h"
#include "ui_saisietokensapi.h"

SaisieTokensAPI::SaisieTokensAPI(const QString &jetonAcces, const QString &jetonSecret, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaisieTokensAPI)
{
    ui->setupUi(this);
    initTokens( jetonAcces, jetonSecret );
}

SaisieTokensAPI::~SaisieTokensAPI()
{
    delete ui;
}

QString SaisieTokensAPI::getJetonAcces() const
{
    return ui->m_jetonAcces->text();
}

QString SaisieTokensAPI::getJetonSecret() const
{
    return ui->m_jetonSecret->text();
}

void SaisieTokensAPI::initTokens(const QString &jetonAcces, const QString &jetonSecret)
{
    ui->m_jetonAcces->setText( jetonAcces );
    ui->m_jetonSecret->setText( jetonSecret );
}
