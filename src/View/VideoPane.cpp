#include "VideoPane.h"
#include "ui_videopane.h"

#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlaylist>
#include <AVPlayer.h>

VideoPane::VideoPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane)
{

    ui->setupUi(this);

    player = new QtAV::AVPlayer;
    player->setRenderer(ui->videoWidget);

    ui->videoWidget->show();



}

VideoPane::~VideoPane()
{
    delete ui;
}

void VideoPane::on_playButton_clicked()
{
    player->play("H:\\Media\\movie1.mkv");
}

void VideoPane::on_pauseButton_clicked()
{
    if(player->isPaused()){
        player->pause(false);
    }else{
        player->pause(true);
    }
}

void VideoPane::on_stopButton_clicked()
{
    if(player->isPlaying()){
        player->stop();
    }
}
