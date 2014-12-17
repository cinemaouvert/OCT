#include "VideoPane.h"
#include "ui_videopane.h"


VideoPane::VideoPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane),
    qvideoWidget(NULL)
{
    ui->setupUi(this);
    qvideoWidget = new QVideoWidget(this);
    qvideoWidget->show();
    //ui->videoWidget->children().insert();
}

VideoPane::~VideoPane()
{
    delete ui;
    delete qvideoWidget;
}
