#include "AudioPane.h"
#include "ui_audiopane.h"

AudioPane::AudioPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPane)
{
    ui->setupUi(this);
}

AudioPane::~AudioPane()
{
    delete ui;
}
