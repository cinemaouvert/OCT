#include "ParametersDialog.h"
#include "ui_ParametersDialog.h"

#include <QFileDialog>
#include <QDebug>

ParametersDialog::ParametersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametersDialog),
    m_settings(NULL)
{
    ui->setupUi(this);
    m_settings = new QSettings("CinemaOuvert", "OpenCinemaTranscoder");

}

void ParametersDialog::showWithRefresh(){
    ui->languageComboBox->clear();
    QDir languageDir(qApp->applicationDirPath()+QDir::separator()+"language");
    QStringList readableFiles;
    qDebug() << languageDir.entryList();
    foreach (QString file, languageDir.entryList()) {
        if(file != "." && file != "..")
            readableFiles.append(file.remove("oct_").split(".").at(0));
    }
    ui->languageComboBox->insertItems(0,readableFiles);


    ui->ffmpegTextEdit->setText(m_settings->value("ffmpeg").toString());
    ui->ffprobeTextEdit->setText(m_settings->value("ffprobe").toString());
    ui->mkvtoolniksTextEdit->setText(m_settings->value("mkvmerge").toString());
    ui->magentLinkTextEdit->setText(m_settings->value("magnetLink").toString());
    ui->mkTorrentTextEdit->setText(m_settings->value("mkTorrent").toString());
    ui->languageComboBox->setCurrentText(m_settings->value("language").toString());
    this->show();
}

ParametersDialog::~ParametersDialog()
{
    if(ui)          delete ui;
    if(m_settings)  delete m_settings;
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
    m_settings->setValue("mkvmerge",ui->mkvtoolniksTextEdit->text());
    m_settings->setValue("ffprobe",ui->ffprobeTextEdit->text());
    m_settings->setValue("ffmpeg",ui->ffmpegTextEdit->text());
    m_settings->setValue("magnetLink",ui->magentLinkTextEdit->text());
    m_settings->setValue("mkTorrent",ui->mkTorrentTextEdit->text());
    if(ui->languageComboBox->currentText() != ""){
        m_settings->setValue("language",ui->languageComboBox->currentText());
    }
}

QString ParametersDialog::getExecutablePath(){
    return QFileDialog::getOpenFileName(this,tr("Open"));
}

void ParametersDialog::on_magentLinkButton_clicked()
{
    ui->magentLinkTextEdit->setText(getExecutablePath());
}

void ParametersDialog::on_mkTorrentButton_clicked()
{
    ui->mkTorrentTextEdit->setText(getExecutablePath());
}

