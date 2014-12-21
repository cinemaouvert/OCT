#include "VideoPane.h"
#include "ui_videopane.h"

#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlaylist>
#include <AVPlayer.h>

VideoPane::VideoPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane),
    player(NULL),
    m_file(NULL)
{
    ui->setupUi(this);

    player = new QtAV::AVPlayer;
    player->setRenderer(ui->videoWidget);

    ui->videoWidget->show();


}

VideoPane::VideoPane(Model::File *file,Model::Stream *stream, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane),
    player(NULL),
    m_file(file),
    m_stream(stream)
{
    ui->setupUi(this);

    player = new QtAV::AVPlayer;
    player->setRenderer(ui->videoWidget);

    ui->videoWidget->show();

    this->loadFile(m_file->getFilePath());
    this->m_streamId = stream->getUID().toInt();
    player->setVideoStream(this->m_streamId);
}


VideoPane::~VideoPane()
{
    delete ui;
    delete player;
}

void VideoPane::on_playButton_clicked()
{
    player->setStartPosition(ui->startSlider->value());
    player->setStopPosition(ui->stopSlider->value());

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
    }
    ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_play.png"));
    ui->timeSlider->setValue(0);
    ui->timeLabel->setText(QTime(0,0).toString("hh:mm:ss"));
}

void VideoPane::loadFile(QString filepath)
{
    player->load(filepath,false);

    ui->startSlider->setMaximum(player->duration());
    ui->stopSlider->setMaximum(player->duration());
    ui->stopSlider->setValue(player->duration());
    ui->timeStop->setTime(QTime(0,0).addMSecs(player->duration()));
    ui->timeStop->setMaximumTime(QTime(0,0).addMSecs(player->duration()));
    ui->timeStart->setMaximumTime(QTime(0,0).addMSecs(player->duration()));
    ui->timeSlider->setMaximum(player->duration());

    connect(ui->timeSlider, SIGNAL(sliderMoved(int)), SLOT(seek(int)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider()));
    connect(player, SIGNAL(started()), SLOT(updateSlider()));
    connect(player, SIGNAL(stopped()), SLOT(on_stopButton_clicked()));

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


void VideoPane::seek(int pos)
{
    if (!player->isPlaying())
        return;
    player->seek(pos*1000LL); // to msecs
}

void VideoPane::updateSlider()
{
    ui->timeSlider->setRange(0, int(player->duration()/1000LL));
    ui->timeSlider->setValue(int(player->position()/1000LL));
    ui->timeLabel->setText(QTime(0,0).addMSecs(player->position()).toString("hh:mm:ss"));
}

void VideoPane::on_timeStart_timeChanged(const QTime &time)
{
    ui->startSlider->setValue(QTime(0,0).msecsTo(time));
}

void VideoPane::on_timeStop_timeChanged(const QTime &time)
{
    ui->stopSlider->setValue(QTime(0,0).msecsTo(time));
}
