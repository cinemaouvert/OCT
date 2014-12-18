#include "SubtitlePane.h"
#include "ui_subtitlepane.h"

SubtitlePane::SubtitlePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubtitlePane)
{
    ui->setupUi(this);
}

SubtitlePane::~SubtitlePane()
{
    delete ui;
}
