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

    this->loadFile("H:\\Downloads\\Strange Empire S01E05 FASTSUB VOSTFR 720p HDTV x264-ADDiCTiON zone-telechargement com\\Strange.Empire.S01E05.FASTSUB.VOSTFR.720p.HDTV.x264-ADDiCTiON.zone-telechargement.com.mkv");

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
    player->load(filepath,false);
    ui->startSlider->setMaximum(player->duration());
    ui->stopSlider->setMaximum(player->duration());
    ui->stopSlider->setValue(player->duration());
    ui->timeStop->setTime(QTime(0,0).addMSecs(player->duration()));

}


void VideoPane::on_stopSlider_sliderMoved(int position)
{
    if(position>ui->startSlider->value()){
        player->setStopPosition(qint64(position));
        ui->timeStop->setTime(QTime(0,0).addMSecs(position));
    }else{
        ui->stopSlider->setValue(ui->startSlider->value());
    }
}

void VideoPane::on_startSlider_sliderMoved(int position)
{
    if(position<ui->stopSlider->value()){
        player->setStartPosition(qint64(position));
        ui->timeStart->setTime(QTime(0,0).addMSecs(position));
    }else{
        ui->startSlider->setValue(ui->stopSlider->value());
    }

}
