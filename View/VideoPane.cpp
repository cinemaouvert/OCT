#include "VideoPane.h"
#include "ui_videopane.h"

#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlaylist>

#include <QDebug>
VideoPane::VideoPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane)
{

    ui->setupUi(this);

    player = new QMediaPlayer(ui->videoWidget);


    player->setVideoOutput(ui->videoWidget);

    ui->videoWidget->show();
}

VideoPane::~VideoPane()
{
    delete ui;
}

void VideoPane::on_playButton_clicked()
{
    //player->setMedia(QUrl::fromLocalFile("H:\\Media\\Zone-Telechargement.com.HGGMS.VOSTFR.XviD.avi"));
    //player->play();
}
