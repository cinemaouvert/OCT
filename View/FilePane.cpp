#include "FilePane.h"
#include "ui_filepane.h"

FilePane::FilePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilePane)
{
    ui->setupUi(this);
}

FilePane::~FilePane()
{
    delete ui;
}
