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

    this->loadFile("H:\\Media\\movie1.mkv");

}

VideoPane::~VideoPane()
{
    delete ui;
}

void VideoPane::on_playButton_clicked()
{
    if(!player->isPlaying()){
        player->play();
        if(player->isPlaying())
            ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_pause.png"));
    }else if(player->isPaused()){
        player->pause(false);
        ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_pause.png"));
    }else{
        player->pause(true);
        ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_play.png"));
    }
}


void VideoPane::on_stopButton_clicked()
{
    if(player->isPlaying()){
        player->stop();
        ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_play.png"));
    }
}

void VideoPane::loadFile(QString filepath)
{
    player->load("H:\\Media\\movie1.mkv",false);
    ui->startSlider->setMaximum(player->duration());
    ui->stopSlider->setMaximum(player->duration());
}

void VideoPane::on_stopSlider_sliderReleased()
{
    player->setStopPosition(qint64(ui->stopSlider->value()));
    player->setPosition(qint64(ui->stopSlider->value()));
}

void VideoPane::on_startSlider_sliderReleased()
{
    player->setStartPosition(qint64(ui->startSlider->value()));
    player->setPosition(qint64(ui->startSlider->value()));
}
