#include "VideoPane.h"
#include "ui_videopane.h"

VideoPane::VideoPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane)
{
    ui->setupUi(this);
}

VideoPane::~VideoPane()
{
    delete ui;
}
