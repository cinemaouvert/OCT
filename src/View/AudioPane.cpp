#include "AudioPane.h"
#include "ui_audiopane.h"


AudioPane::AudioPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPane),
    m_file(NULL),
    m_stream(NULL)
{
    ui->setupUi(this);
    fillAudioCodecComboBox();
}

AudioPane::AudioPane(Model::File *file,Model::Stream *stream, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPane),
    m_file(file),
    m_stream(stream)
{
    ui->setupUi(this);
    fillAudioCodecComboBox();
}

void AudioPane::fillAudioCodecComboBox() {
    QStringList list = (QStringList() << "AAC" << "MP1" << "MP2" << "MP3" << "FLAC");
    ui->comboBox_AudioCodec->addItems( list );
}

AudioPane::~AudioPane()
{
    delete ui;
}
