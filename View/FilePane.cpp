#include "FilePane.h"
#include "ui_filepane.h"

#include <QFileDialog>
#include <QDebug>

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

void FilePane::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Image"));

    qDebug()<< fileName;
}
