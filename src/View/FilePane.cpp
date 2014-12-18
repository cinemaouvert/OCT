#include "FilePane.h"
#include "ui_filepane.h"

#include <QFileDialog>
#include <QDebug>
#include "src/Model/Attachment.h"



FilePane::FilePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilePane)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
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
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open"));
    this->m_dispatcher->addFile(filePath);
}

void FilePane::refresh()
{
    QStringList names;
    list.clear();
    foreach(Model::File *f , *(this->m_dispatcher->getCurrentProject()->fileList())){
        list << f->getFilePath();
        QStringList name = f->getFilePath().split("/");
        names << name.at(name.length()-1);
    }
    foreach(Model::Attachment *a , *(this->m_dispatcher->getCurrentProject()->attachments())){
        list << a->filepath();
        QStringList name = a->filepath().split("/");
        names << name.at(name.length()-1);

    }
    model->setStringList(names);
    ui->listView_2->setModel(model);

}

void FilePane::on_pushButton_clicked()
{
    QStringList names = model->stringList();
    if (names.size() != 0){
        QModelIndexList indexes = ui->listView_2->selectionModel()->selectedIndexes();
        if(indexes.size() != 0){
            QString filePath = list.at(indexes.at(0).row());
            this->m_dispatcher->removeFile(filePath);
        }
    }

}
