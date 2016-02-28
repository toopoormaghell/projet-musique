#include "dialogconfigactu.h"
#include "ui_dialogconfigactu.h"
#include <QFileDialog>
#include <QAbstractButton>
#include "bddconfig.h"

DialogConfigActu::DialogConfigActu( QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::DialogConfigActu )
{
    ui->setupUi( this );
    AfficherDossParDef();
    AfficherCategories();
}

DialogConfigActu::~DialogConfigActu()
{
    delete ui;
}

void DialogConfigActu::on_buttonBox_accepted()
{
    EnregisDossParDef();
    EnregistrerCategories();
}

void DialogConfigActu::on_Changer_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory( this, tr( "Dossier par défaut" ), ui->DossierParDef->text(), QFileDialog::ShowDirsOnly );

    ui->DossierParDef->setText( fileName );
}
void DialogConfigActu::AfficherDossParDef()
{
    ui->DossierParDef->setText( m_database.recupdossierpardef() );
}
void DialogConfigActu::EnregisDossParDef()
{
    m_database.EnregistrerDossierParDef( ui->DossierParDef->text() );
}
void DialogConfigActu::AfficherCategories()
{
    ui->Albums->setChecked( m_database.ActualiserAlbums() );
    ui->Compils->setChecked( m_database.ActualiserCompil() );
    ui->Lives->setChecked( m_database.ActualiserLives() );
}
void DialogConfigActu::EnregistrerCategories()
{
    m_database.EnregistrerActuAlbums( ui->Albums->isChecked() );
    m_database.EnregistrerActuCompil( ui->Compils->isChecked() );
    m_database.EnregistrerActuLives( ui->Lives->isChecked() );
}
void DialogConfigActu::RemiseaZero()
{
    ui->DossierParDef->setText( "F:/Albums" );
    ui->Albums->setChecked( true );
    ui->Compils->setChecked( false );
    ui->Lives->setChecked( false );
}

void DialogConfigActu::on_buttonBox_clicked( QAbstractButton* button )
{
    if ( ui->buttonBox->standardButton( button ) == QDialogButtonBox::Reset )
    {
        RemiseaZero();
    }
}
