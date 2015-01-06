#include "FilePane.h"
#include "ui_filepane.h"
#include "MyModel.h"
#include <QFileDialog>
#include <QDebug>
#include <typeinfo>
#include "src/Model/Attachment.h"
#include <src/Model/StreamWrapper.h>
#include <src/Model/Subtitle.h>



FilePane::FilePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilePane)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    splitterNoCollapsing();
}

void FilePane::setDispatcher(Controller::OCTDispatcher *dispatcheur)
{
    this->m_dispatcher = dispatcheur;
}

FilePane::~FilePane()
{
    if(ui) delete ui;
    if(model) delete model;
}

void FilePane::on_pushButton_AddFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open"));
    this->m_dispatcher->addFile(filePath);
}

void FilePane::on_EditLine_Name_Changed()
{

}

void FilePane::refresh()
{
    ///////////////////////////////ListView2/////////////////////////////////////////
    QStringList names;
    list.clear();
    foreach(Model::File *f , *(this->m_dispatcher->getCurrentProject()->fileList())){
        list << f->getFilePath();
        names << f->getName();
    }
    foreach(Model::Attachment *a , *(this->m_dispatcher->getCurrentProject()->attachments())){
        list << a->filepath();
        QStringList name = a->filepath().split("/");
        names << name.at(name.length()-1);
    }
    model->setStringList(names);
    ui->listView_ImportFile->setModel(model
                                      );

    //////////////////////////////TableView////////////////////////////////////////////
    int nbVideo = this->m_dispatcher->getCurrentProject()->nbVideo();
    int nbAudio = this->m_dispatcher->getCurrentProject()->nbAudio();
    int nbSub = this->m_dispatcher->getCurrentProject()->nbSub();
    int i = 0;
    int j = 1 + nbVideo;
    int k = 1 + j + nbAudio;
    MyModel *m = new MyModel( 3 + nbVideo + nbAudio + nbSub, 6);
    ui->tableView_ImportFile->setModel(m);

    m->setItem(0,0,QString("Nom"));
    m->setItem(0,1,QString("Codec"));
    m->setItem(0,2,QString("IPS"));
    m->setItem(0,3,QString("Taille"));
    m->setItem(0,4,QString("Supporté"));

    m->setItem(j,0,QString("Nom"));
    m->setItem(j,1,QString("Codec"));
    m->setItem(j,2,QString("Echantillonage"));
    m->setItem(j,3,QString("Profondeur"));
    m->setItem(j,4,QString("Cannaux"));
    m->setItem(j,5,QString("Supporté"));

    m->setItem(k,0,QString("Nom"));
    m->setItem(k,1,QString("Format"));
    m->setItem(k,2,QString("Encodage"));
    m->setItem(k,3,QString("Ips"));
    m->setItem(k,4,QString("Supporté"));



    foreach(Model::File *f , *(this->m_dispatcher->getCurrentProject()->fileList())){
        foreach( Model::StreamWrapper *sw, *(f->getDatas())){

            if(sw->getOldStream()->getType() == Model::Stream::VIDEO){
                i++;
                m->setItem(i,0,QString("Vidéo piste: %2 : %1").arg(f->getName()).arg(sw->getOldStream()->getUID()));
                Model::Parameter *p = sw->getOldStream()->getParameters()->find("codec_name").value();
                m->setItem(i,1,p->value());

                p = sw->getOldStream()->getParameters()->find("r_frame_rate").value();
                m->setItem(i,2,p->value());

                p = sw->getOldStream()->getParameters()->find("resolution").value();
                m->setItem(i,3,p->value());

                m->setItem(i,4,QString("ok"));


            }
            else if(sw->getOldStream()->getType() == Model::Stream::AUDIO){
                j++;
                m->setItem(j,0,QString("Audio Piste: %2 : %1").arg(f->getName()).arg(sw->getOldStream()->getUID()));
                Model::Parameter *p = sw->getOldStream()->getParameters()->find("codec_name").value();
                m->setItem(j,1,p->value());

                p = sw->getOldStream()->getParameters()->find("sample_rate").value();
                m->setItem(j,2,p->value());

                p = sw->getOldStream()->getParameters()->find("resolution").value();
                m->setItem(j,3,p->value());

                p = sw->getOldStream()->getParameters()->find("channels").value();
                m->setItem(j,4,p->value());

                m->setItem(j,5,QString("ok"));

            }
            else if(sw->getOldStream()->getType() == Model::Stream::SUBTITLE){
                 qDebug() << "sub";
            }

        }

    }

    foreach(Model::Attachment *a , *(this->m_dispatcher->getCurrentProject()->attachments())){
       /* m->setItem(i,0,QString("attachment"));
        QStringList name = a->filepath().split("/");
        m->setItem(i,1,name.at(name.length()-1));
        i++;*/
    }


   // ui->tableView->->setStyleSheet("* { background-color: rgb(250, 50, 50); }");
    /*

    if (role == Qt::BackgroundRole) {
               int row = index.row();
              // QColor color = calculateColorForRow(row);
               QColor c = Qt::red;
               return QBrush(c);
    }

    */





    ui->tableView_ImportFile->setSpan(0, 4, 1, 5);
    ui->tableView_ImportFile->setSpan(k, 4, 1, 5);
    ui->tableView_ImportFile->setAlternatingRowColors(true);
    qDebug() << ui->tableView_ImportFile->styleSheet();

  //  ui->tableView->setSpan(0, 1, 0, 2);

}

void FilePane::on_pushButton_DeleteFile_clicked()
{
    QStringList names = model->stringList();
    if (names.size() != 0){
        QModelIndexList indexes = ui->listView_ImportFile->selectionModel()->selectedIndexes();
        if(indexes.size() != 0){
            QString filePath = list.at(indexes.at(0).row());
            this->m_dispatcher->removeFile(filePath);
        }
    }
}

void FilePane::splitterNoCollapsing() {
    ui->splitter->setChildrenCollapsible(false);
    ui->splitter_2->setChildrenCollapsible(false);
}
