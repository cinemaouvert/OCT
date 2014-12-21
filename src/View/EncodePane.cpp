#include "EncodePane.h"
#include "ui_encodepane.h"

EncodePane::EncodePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EncodePane)
{
    ui->setupUi(this);
}

EncodePane::~EncodePane()
{
    delete ui;
}

void EncodePane::refresh()
{

}
