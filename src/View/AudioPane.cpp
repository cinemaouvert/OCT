#include "AudioPane.h"
#include "ui_audiopane.h"


AudioPane::AudioPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPane),
    m_file(NULL),
    m_stream(NULL)
{
    ui->setupUi(this);
}

AudioPane::AudioPane(Model::File *file,Model::Stream *stream, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPane),
    m_file(file),
    m_stream(stream)
{
    ui->setupUi(this);
}

AudioPane::~AudioPane()
{
    delete ui;
}
