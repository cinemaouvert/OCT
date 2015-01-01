#include "ParametersDialog.h"
#include "ui_ParametersDialog.h"

#include <QFileDialog>

ParametersDialog::ParametersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametersDialog)
{
    ui->setupUi(this);
}

ParametersDialog::~ParametersDialog()
{
    delete ui;
}

void ParametersDialog::on_ffmpegButton_clicked()
{
    ui->ffmpegTextEdit->setText(getExecutablePath());
}

void ParametersDialog::on_ffmprobeButton_clicked()
{
    ui->ffprobeTextEdit->setText(getExecutablePath());
}

void ParametersDialog::on_mkvtoolniksButton_clicked()
{
    ui->mkvtoolniksTextEdit->setText(getExecutablePath());
}

void ParametersDialog::on_buttonBox_accepted()
{

}

QString ParametersDialog::getExecutablePath(){
    return QFileDialog::getOpenFileName(this,tr("Open"));
}
