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

void FilePane::setDispatcher(Controller::OCTDispatcher *dispatcheur)
{
    this->m_dispatcher = dispatcheur;
}

FilePane::~FilePane()
{
    delete ui;
}

void FilePane::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"));
    this->m_dispatcher->addFile(fileName);

}
