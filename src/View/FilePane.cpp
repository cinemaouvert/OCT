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
   // ui->tableView_ImportFile->horizontalHeader()->setVisible(false);
    ui->tableView_ImportFile->verticalHeader()->setVisible(false);
  //  ui->tableView_ImportFile->setAlternatingRowColors(true);
    ui->tableView_ImportFile->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_ImportFile->resizeColumnsToContents();
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
    ui->listView_ImportFile->setModel(model);

    //////////////////////////////TableView////////////////////////////////////////////
    int nbVideo = this->m_dispatcher->getCurrentProject()->nbVideo();
    int nbAudio = this->m_dispatcher->getCurrentProject()->nbAudio();
    int nbSub = this->m_dispatcher->getCurrentProject()->nbSub();
    int i = 1;
    int j = 3 + nbVideo;
    int k = 2 + j + nbAudio;
    MyModel *m = new MyModel( 8 + nbVideo + nbAudio + nbSub, 6 , nbVideo , nbAudio , nbSub);
    ui->tableView_ImportFile->setModel(m);

    m->setItem(0,0,tr("Video"));
    m->setItem(1,0,tr("Nom"));
    m->setItem(1,1,tr("Codec"));
    m->setItem(1,2,tr("IPS"));
    m->setItem(1,3,tr("Taille"));
    m->setItem(1,4,tr("Supporté"));

    m->setItem(j-1,0,tr("Audio"));
    m->setItem(j,0,tr("Nom"));
    m->setItem(j,1,tr("Codec"));
    m->setItem(j,2,tr("Echantillonage"));
    m->setItem(j,3,tr("Profondeur"));
    m->setItem(j,4,tr("Cannaux"));
    m->setItem(j,5,tr("Supporté"));

    m->setItem(k-1,0,tr("Sous Titre"));
    m->setItem(k,0,tr("Nom"));
    m->setItem(k,1,tr("Format"));
    m->setItem(k,2,tr("Encodage"));
    m->setItem(k,3,tr("IPS"));
    m->setItem(k,4,tr("Supporté"));

    ui->tableView_ImportFile->clearSpans();
    ui->tableView_ImportFile->setSpan(0, 0, 1, 6);
    ui->tableView_ImportFile->setSpan(1, 4, 1, 5);
    ui->tableView_ImportFile->setSpan(2+nbVideo, 0, 1, 6);
    ui->tableView_ImportFile->setSpan(4+nbVideo+nbAudio, 0, 1, 6);
    ui->tableView_ImportFile->setSpan(5+nbVideo+nbAudio, 4, 1, 5);


    foreach(Model::File *f , *(this->m_dispatcher->getCurrentProject()->fileList())){
        foreach( Model::StreamWrapper *sw, *(f->getDatas())){

            if(sw->getOldStream()->getType() == Model::Stream::VIDEO){
                i++;
                m->setItem(i,0,tr("piste: %2 : %1").arg(f->getName()).arg(sw->getOldStream()->getUID()));
                Model::Parameter *p = sw->getOldStream()->getParameters()->find("codec_name").value();
                m->setItem(i,1,p->value());

                p = sw->getOldStream()->getParameters()->find("r_frame_rate").value();
                m->setItem(i,2,p->value());

                p = sw->getOldStream()->getParameters()->find("resolution").value();
                m->setItem(i,3,p->value());

                m->setItem(i,4,QString("OK"));
                ui->tableView_ImportFile->setSpan(i, 4, 1, 5);

            }
            else if(sw->getOldStream()->getType() == Model::Stream::AUDIO){
                j++;
                m->setItem(j,0,tr("Piste: %2 : %1").arg(f->getName()).arg(sw->getOldStream()->getUID()));
                Model::Parameter *p = sw->getOldStream()->getParameters()->find("codec_name").value();
                m->setItem(j,1,p->value());

                p = sw->getOldStream()->getParameters()->find("sample_rate").value();
                m->setItem(j,2,p->value());

                p = sw->getOldStream()->getParameters()->find("resolution").value();
                m->setItem(j,3,p->value());

                p = sw->getOldStream()->getParameters()->find("channels").value();
                m->setItem(j,4,p->value());

                m->setItem(j,5,QString("OK"));

            }
            else if(sw->getOldStream()->getType() == Model::Stream::SUBTITLE){
                k++;
                m->setItem(k,0,tr("Piste: %2 : %1").arg(f->getName()).arg(sw->getOldStream()->getUID()));
                Model::Parameter *p = sw->getOldStream()->getParameters()->find("codec_name").value();
                m->setItem(k,1,p->value());

                m->setItem(k,4,QString("OK"));

                ui->tableView_ImportFile->setSpan(k, 4, 1, 5);
            }

        }

    }

    foreach(Model::Attachment *a , *(this->m_dispatcher->getCurrentProject()->attachments())){
       /* m->setItem(i,0,QString("attachment"));
        QStringList name = a->filepath().split("/");
        m->setItem(i,1,name.at(name.length()-1));
        i++;*/
    }
    m->setItem(k+1,0,tr("Champs d'informations"));
    m->setItem(k+1,1,tr("%1 champ remplie sur %2"));
    m->setItem(k+2,0,tr("Pieces Jointes"));
    m->setItem(k+2,1,QString::number(this->m_dispatcher->getCurrentProject()->attachments()->size()));

    ui->tableView_ImportFile->setSpan(k+1, 1, 1, 6);
    ui->tableView_ImportFile->setSpan(k+2, 1, 1, 6);

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


