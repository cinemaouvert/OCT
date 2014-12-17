#include "VideoPlayer.h"
#include "ui_videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent) :
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}
