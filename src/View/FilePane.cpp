#include "FilePane.h"
#include "ui_filepane.h"
#include "MyModel.h"
#include "MyDelegate.h"

#include "src/Model/Attachment.h"
#include "src/Model/StreamWrapper.h"
#include "src/Model/Subtitle.h"

#include <QFileDialog>
#include <QDebug>
#include <typeinfo>
#include <QResource>
#include <QXmlQuery>
#include <QStandardItemModel>

// ========================================================================== //
// == CONSTRUCTORS AND DESTRUCTORS ========================================== //
// ========================================================================== //
FilePane::FilePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilePane)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);
    splitterNoCollapsing();
   // ui->tableView_ImportFile->horizontalHeader()->setVisible(false);
    ui->tableView_ImportFile->verticalHeader()->setVisible(false);
  //  ui->tableView_ImportFile->setAlternatingRowColors(true);
    //ui->tableView_ImportFile->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_ImportFile->resizeColumnsToContents();
    ui->listView_ImportFile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_Export->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //  ui->listView_Export->setAlternatingRowColors(true);

    ui->listView_Export->setFocusPolicy(Qt::NoFocus);


    ui->comboBox_Preconfig->clear();

}

FilePane::~FilePane()
{
    if(ui) delete ui;
    if(m_model) delete m_model;
}

// ========================================================================== //
// == ACCESSORS AND MUTATORS ================================================ //
// ========================================================================== //
void FilePane::setDispatcher(Controller::OCTDispatcher *dispatcheur)
{
    this->m_dispatcher = dispatcheur;
    connectInterface();

    QResource preconfigs(":/ocpm/resources/ocpm");

    m_preConfigsDir = QDir(preconfigs.absoluteFilePath());

    if(m_preConfigsDir.isReadable()){
        foreach (QString file, m_preConfigsDir.entryList()) {
            ui->comboBox_Preconfig->insertItem(0,file.remove(".xml"));
        }
    }
    ui->comboBox_Preconfig->insertItem(0,tr("None"));
    ui->comboBox_Preconfig->setCurrentIndex(0);

}

// ========================================================================== //
// == CLASS METHODS ========================================================= //
// ========================================================================== //
void FilePane::refresh()
{
    QIcon i_ok = QIcon(":/icons/resources/glyphicons/glyphicons_206_ok_2.png");
    QIcon i_nok = QIcon(":/icons/resources/glyphicons/glyphicons_207_remove_2.png");
    MyDelegate *md = new MyDelegate();
    QStandardItemModel* sim;
    sim = new QStandardItemModel(this);

    //////REFRESH FIELDS/////
    ui->lineEdit_ExportName->setText(this->m_dispatcher->getCurrentProject()->name());


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
    m_model->setStringList(names);
    ui->listView_ImportFile->setModel(m_model);

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
    QString out_tView = "";

    foreach(Model::File *f , *(this->m_dispatcher->getCurrentProject()->fileList())){
        foreach( Model::StreamWrapper *sw, *(f->getDatas())){

            if(sw->getRelevantStream()->getType() == Model::Stream::VIDEO){
                i++;
                m->setItem(i,0,tr("piste: %2 : %1").arg(f->getName()).arg(sw->getRelevantStream()->getUID()));
                Model::Parameter *p = sw->getRelevantStream()->getParameters()->find(Model::Stream::CODEC_NAME).value();
                m->setItem(i,1,p->value());
                out_tView = "Flux video " + sw->getRelevantStream()->getUID() + " from "+ f->getName() + " - " + p->value();

                p = sw->getRelevantStream()->getParameters()->find(Model::Stream::VIDEO_FRAME_RATE).value();
                m->setItem(i,2,p->value());

                p = sw->getRelevantStream()->getParameters()->find(Model::Stream::RESOLUTION).value();
                m->setItem(i,3,p->value().remove("scale="));
                out_tView = out_tView + " - résolution " + p->value().remove("scale=");

                ui->tableView_ImportFile->setSpan(i, 4, 1, 5);

                QStandardItem* item;
                if(this->m_dispatcher->checkStreamValidation(sw->getRelevantStream())){
                    item = new QStandardItem(i_ok,out_tView);
                    m->setItem(i,4,QString("OK"));
                }
                else{
                    item = new QStandardItem(i_nok,out_tView);
                    m->setItem(i,4,QString("NOK"));
                }
                sim->appendRow(item);



            }
            else if(sw->getRelevantStream()->getType() == Model::Stream::AUDIO){
                j++;
                m->setItem(j,0,tr("Piste: %2 : %1").arg(f->getName()).arg(sw->getRelevantStream()->getUID()));
                Model::Parameter *p = sw->getRelevantStream()->getParameters()->find(Model::Stream::CODEC_NAME).value();
                m->setItem(j,1,p->value());
                out_tView = "Piste Audio " + sw->getRelevantStream()->getUID() + " from "+ f->getName() + " - " + p->value();

                p = sw->getRelevantStream()->getParameters()->find(Model::Stream::AUDIO_SAMPLE_RATE).value();
                m->setItem(j,2,p->value());

                p = sw->getRelevantStream()->getParameters()->find(Model::Stream::RESOLUTION).value();
                m->setItem(j,3,p->value());

                p = sw->getRelevantStream()->getParameters()->find(Model::Stream::AUDIO_CHANNELS).value();
                m->setItem(j,4,p->value());


                QStandardItem* item;
                if(this->m_dispatcher->checkStreamValidation(sw->getRelevantStream())){
                    item = new QStandardItem(i_ok,out_tView);
                    m->setItem(j,5,QString("OK"));
                }
                else{
                    item = new QStandardItem(i_nok,out_tView);
                    m->setItem(j,5,QString("NOK"));
                }
                sim->appendRow(item);
            }
            else if(sw->getRelevantStream()->getType() == Model::Stream::SUBTITLE){
                k++;
                m->setItem(k,0,tr("Piste: %2 : %1").arg(f->getName()).arg(sw->getRelevantStream()->getUID()));
                Model::Parameter *p = sw->getRelevantStream()->getParameters()->find(Model::Stream::CODEC_NAME).value();
                m->setItem(k,1,p->value());                
                out_tView = "sous titre " + sw->getRelevantStream()->getUID() + " from "+ f->getName() + " - " + p->value();



                QStandardItem* item;
                if(this->m_dispatcher->checkStreamValidation(sw->getRelevantStream())){
                    item = new QStandardItem(i_ok,out_tView);
                    m->setItem(k,4,QString("OK"));
                }
                else{
                    item = new QStandardItem(i_nok,out_tView);
                    m->setItem(k,4,QString("NOK"));
                }
                sim->appendRow(item);

                ui->tableView_ImportFile->setSpan(k, 4, 1, 5);
            }

        }
        ui->tableView_ImportFile->resizeColumnsToContents();
        ui->tableView_ImportFile->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
        ui->tableView_ImportFile->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
        ui->tableView_ImportFile->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
        ui->tableView_ImportFile->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
        ui->tableView_ImportFile->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
        ui->tableView_ImportFile->horizontalHeader()->setSectionResizeMode(5,QHeaderView::ResizeToContents);

    }

    foreach(Model::Attachment *a , *(this->m_dispatcher->getCurrentProject()->attachments())){
       /* m->setItem(i,0,QString("attachment"));
        QStringList name = a->filepath().split("/");
        m->setItem(i,1,name.at(name.length()-1));
        i++;*/
    }

    //Champs informations renseigné

    int curInfo = -1;
    int totInfo = -1;

    if(this->m_dispatcher->informationMovieStruct())
        totInfo = this->m_dispatcher->informationMovieStruct()->size();
    if(this->m_dispatcher->getCurrentProject()->informations())
        curInfo = this->m_dispatcher->getCurrentProject()->informations()->size();

    m->setItem(k+1,0,tr("Champs d'informations"));
    m->setItem(k+1,1, QString::number(curInfo) + tr(" champ remplie sur ") + QString::number(totInfo));
    m->setItem(k+2,0,tr("Pieces Jointes"));
    m->setItem(k+2,1,QString::number(this->m_dispatcher->getCurrentProject()->attachments()->size()));

    ui->tableView_ImportFile->setSpan(k+1, 1, 1, 6);
    ui->tableView_ImportFile->setSpan(k+2, 1, 1, 6);

    sim->sort(0);

    QStandardItem* item;
    //capture par défaut
    if(true){
        item = new QStandardItem(i_ok,"capture par default");
    }
    else{
        item = new QStandardItem(i_nok,"capture par default");
    }
    sim->appendRow(item);

    //affiche
    if(this->m_dispatcher->checkPosterValidation()){
        item = new QStandardItem(i_ok,"affiche");
    }
    else{
        item = new QStandardItem(i_nok,"affiche");
    }
    sim->appendRow(item);

    //pack communication
    if(true){
        item = new QStandardItem(i_ok,tr("pack communication"));
    }
    else{
        item = new QStandardItem(i_nok,tr("pack communication"));
    }
    sim->appendRow(item);


    //Champs informations renseigné
    int difInfo = this->m_dispatcher->checkInformationValidation();
    if(difInfo == 0){
        item = new QStandardItem(i_ok,tr("Champs informations renseigné"));
    }
    else{
        item = new QStandardItem(i_nok,tr("Champs informations renseigné: ")+ QString::number(difInfo) +tr(" champs manquant"));
    }
    sim->appendRow(item);

    ui->listView_Export->setModel(sim);
    ui->listView_Export->setItemDelegate(md);
}

void FilePane::splitterNoCollapsing()
{
    ui->splitter->setChildrenCollapsible(false);
    ui->splitter_2->setChildrenCollapsible(false);
}

// ========================================================================== //
// == EVENT METHODS ========================================================= //
// ========================================================================== //
void FilePane::connectInterface()
{
    connect(ui->lineEdit_ExportName, SIGNAL(textChanged(QString)), m_dispatcher, SLOT(treatProjectNameChanged(QString)));
}

void FilePane::on_pushButton_DeleteFile_clicked()
{
    QStringList names = m_model->stringList();
    if (names.size() != 0){
        QModelIndexList indexes = ui->listView_ImportFile->selectionModel()->selectedIndexes();
        if(indexes.size() != 0){
            QString filePath = list.at(indexes.at(0).row());
            this->m_dispatcher->removeFile(filePath);
        }
    }
    m_dispatcher->checkProjectValidation();
}

void FilePane::on_pushButton_AddFile_clicked()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(this,tr("Open"));
    foreach (QString filePath, filePaths) {
        this->m_dispatcher->addFile(filePath);
    }
    m_dispatcher->checkProjectValidation();
}

void FilePane::on_comboBox_Preconfig_currentTextChanged(const QString &arg1)
{
    if(arg1 == "None"){
        m_dispatcher->getOCPMValidation()->setExist(false);
    }else if(arg1 != ""){
        QFile file(m_preConfigsDir.filePath(arg1).append(".xml"));
        if(file.exists() && m_dispatcher != NULL){
            m_dispatcher->getOCPMValidation()->loadPreConfXML(&file);
            this->mainWindow()->updateReco();
            this->refresh();
        }
    }

}

void FilePane::on_findExport_clicked()
{
    QUrl filePath = QFileDialog::getSaveFileName(this, tr("Choisir fichier de sortie"),"",tr("Matroska (*.mkv)"));
    m_dispatcher->treatProjectNameChanged(filePath.toString());
    ui->lineEdit_ExportName->setText(filePath.toString());
}

View::MainWindow *FilePane::mainWindow() const
{
    return m_mainWindow;
}

void FilePane::setMainWindow(View::MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

