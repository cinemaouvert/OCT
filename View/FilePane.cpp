#include "FilePane.h"
#include "ui_filepane.h"

#include <QFileDialog>
#include <QDebug>

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

    QStringList list = model->stringList();
    QStringList path = filePath.split("/");
    qDebug() << path;
    list << path.at(path.length()-1);

    model->setStringList(list);
    ui->listView_2->setModel(model);


}

void FilePane::addItem(QString name)
{

}

void FilePane::on_pushButton_clicked()
{
    QStringList list = model->stringList();
    if (list.size() != 0){
        QModelIndexList indexes = ui->listView_2->selectionModel()->selectedIndexes();
        if(indexes.size() != 0){
            QString filePath = list.at(indexes.at(0).row());
            /*
            this->m_dispatcher->removeFile(filePath);
            list.removeAt(indexes.at(0).row());
            model->setStringList(list);
            ui->listView_2->setModel(model);
            */
        }
    }

}
