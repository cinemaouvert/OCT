#include "SubtitlePane.h"
#include "ui_subtitlepane.h"


SubtitlePane::SubtitlePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubtitlePane),
    m_file(NULL),
    m_stream(NULL)
{
    ui->setupUi(this);
}

SubtitlePane::SubtitlePane(Model::File *file,Model::Stream *stream,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubtitlePane),
    m_file(file),
    m_stream(stream)
{
    ui->setupUi(this);
}

SubtitlePane::~SubtitlePane()
{
    delete ui;
}
