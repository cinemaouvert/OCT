#include "InformationPane.h"
#include "ui_informationpane.h"

InformationPane::InformationPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformationPane)
{
    ui->setupUi(this);
}

InformationPane::~InformationPane()
{
    delete ui;
}
