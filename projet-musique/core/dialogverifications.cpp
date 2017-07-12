#include "dialogverifications.h"
#include "ui_dialogverifications.h"
#include "gestionverifications.h"


DialogVerifications::DialogVerifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVerifications)
{
    ui->setupUi(this);
}

DialogVerifications::~DialogVerifications()
{
    delete ui;
}

void DialogVerifications::on_pochvides_clicked()
{
    ui->interaction->append("Début de la suppression des pochettes non utilisées...");
    m_gestion->SuppressionPochettes();
    ui->interaction->append("Fin de la suppression des pochettes non utilisées.");
}

void DialogVerifications::on_auto_2_clicked()
{
    ui->interaction->append("Début de la vérification automatique...");
    m_gestion->verifierbdd();
    ui->interaction->append("Fin de la vérification automatique.");
}

void DialogVerifications::on_mp3phys_clicked()
{
    ui->interaction->append("Début de la synchronisation MP3/Phys...");
    m_gestion->titresphysetmp3();
    ui->interaction->append("Fin de la synchronisation MP3/Phys.");
}

void DialogVerifications::on_PochCompils_clicked()
{
    ui->interaction->append("Début de la modification des pochettes des compilations...");
    m_gestion->PochCompils();
    ui->interaction->append("Fin de la modification des pochettes des compilations.");

    on_pochvides_clicked();
}

void DialogVerifications::on_Reformatage_clicked()
{
    ui->interaction->append("Début de la modification du reformatage des entités en BDD...");
    m_gestion->ReformatageEntites();
    ui->interaction->append("Fin de la modification du reformatage des entités en BDD.");

}
