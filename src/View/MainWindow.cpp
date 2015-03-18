#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "src/Model/StreamWrapper.h"

#include "src/Model/Stream.h"

#include "src/View/FilePane.h"
#include "src/View/AudioPane.h"
#include "src/View/VideoPane.h"
#include "src/View/SubtitlePane.h"
#include "src/View/InformationPane.h"
#include "src/View/EncodePane.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>

View::MainWindow::MainWindow(QWidget *parent,Controller::OCTDispatcher *theDispatcher) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dispatcher(theDispatcher),
    m_settingsW(NULL)
{
    ui->setupUi(this);
    setOCPMState(false);
    m_settingsW = new ParametersDialog();
    connect(ui->actionPreferences, SIGNAL(triggered()),SLOT(on_OpenSettings()));
    connect(ui->actionMise_jour, SIGNAL(triggered()),SLOT(on_UpdateVersion()));
    connect(ui->actionNouveau_projet, SIGNAL(triggered()),SLOT(on_NewProject()));
    connect(ui->actionSauvegarder_le_projet, SIGNAL(triggered()),SLOT(on_SaveProject()));
    connect(ui->actionSauvegarder_sous, SIGNAL(triggered()),SLOT(on_SaveProjectSous()));
    connect(ui->actionOuvrir_un_projet, SIGNAL(triggered()),SLOT(on_LoadProject()));
    connect(ui->actionVoir_les_torrents, SIGNAL(triggered()),SLOT(on_viewTorrent()));

    ui->tab_encode->setDispatcher(m_dispatcher);
    ui->tab_infos->setDispatcher(m_dispatcher);
    ui->tabWidgetVideo->clear();
    ui->tabWidgetSubtitle->clear();
    ui->tabWidgetAudio->clear();

    ui->tab_files->setMainWindow(this);
    ui->tab_files->setDispatcher(m_dispatcher);


}

void View::MainWindow::refresh()
{
    ui->tab_files->refresh();

    ui->tabWidgetVideo->clear();
    ui->tabWidgetSubtitle->clear();
    ui->tabWidgetAudio->clear();
    m_videoFileNames.clear();

    QList<SubtitlePane*> sPanes;
    QList<Model::Stream*> vStreams;
    QList<Model::File*> vFiles;

    foreach (Model::File *file, *(m_dispatcher->getCurrentProject()->fileList())) {
        foreach (Model::StreamWrapper *streamW, *(file->getStreamWrappers())) {
            QWidget *s;
            switch (streamW->getRelevantStream()->getType()) {
                case Model::Stream::AUDIO:
                    s = new AudioPane(file,streamW->oldStream(),this);
                    ui->tabWidgetAudio->addTab(s,file->getName() + " piste : " +streamW->getRelevantStream()->getUID());
                    ((AudioPane*)s)->setDispatcher(m_dispatcher);
                    break;
                case Model::Stream::VIDEO:
                    s = new VideoPane(file,streamW->oldStream(),this);
                    ui->tabWidgetVideo->addTab(s,file->getName() + " piste : " +streamW->getRelevantStream()->getUID());
                    ((VideoPane*)s)->setDispatcher(m_dispatcher);
                    m_videoFileNames.append(file->getName() + " : stream "+streamW->getRelevantStream()->getUID());
                    vStreams.append(streamW->getRelevantStream());
                    vFiles.append(file);
                    break;
                case Model::Stream::SUBTITLE:
                    s = new SubtitlePane(file,streamW->oldStream(),this);
                    ui->tabWidgetSubtitle->addTab(s,file->getName() + " piste : " +streamW->getRelevantStream()->getUID());
                    ((SubtitlePane*)s)->setDispatcher(m_dispatcher);
                    sPanes.append((SubtitlePane*)s);
                    break;
                default:

                    break;
            };
        }
    }

    foreach (SubtitlePane *sP, sPanes) {
        int i=0;
        foreach (Model::Stream *sT, vStreams) {
            sP->videoStreamAdded(vFiles.at(i),sT);
            i++;
        }
    }

    ui->tab_encode->refresh();
    ui->tab_infos->refresh();
}

QStringList View::MainWindow::getVideoFileNames(){
    return m_videoFileNames;
}

void View::MainWindow::refreshProjectPane()
{
    ui->tab_encode->refreshProjectPane();
}

View::MainWindow::~MainWindow()
{
    if(ui) delete ui;
    if(m_settingsW) delete m_settingsW;
}

void View::MainWindow::setOCPMState(bool isValid)
{
    if(isValid){
        ui->labelStatusOKNOK->setStyleSheet("background-color:  rgba(0, 255, 0, 100);border-radius:5px;");
        ui->labelStatusOKNOK->setText("OCPM valide");
    }else{
        ui->labelStatusOKNOK->setStyleSheet("background-color:  rgba(255, 0, 0, 100);border-radius:5px;");
        ui->labelStatusOKNOK->setText("OCPM invalide");
    }

}

void View::MainWindow::updateReco()
{
    if(this->ui != NULL){
        if(ui->tabWidgetVideo != NULL){
            int i =0;
            while(this->ui->tabWidgetVideo->widget(i)){
                ((VideoPane*)this->ui->tabWidgetVideo->widget(i))->applyReco();
                i++;
            }
        }
        if(ui->tabWidgetAudio != NULL){
            int i =0;
            while(this->ui->tabWidgetAudio->widget(i)){
                ((AudioPane*)this->ui->tabWidgetAudio->widget(i))->applyReco();
                i++;
            }
        }
        if(ui->tabWidgetSubtitle != NULL){
            int i =0;
            while(this->ui->tabWidgetSubtitle->widget(i)){
                ((SubtitlePane*)this->ui->tabWidgetSubtitle->widget(i))->applyReco();
                i++;
            }
        }

    }
}

FilePane* View::MainWindow::getFilePane()
{
    return ui->tab_files;
}

EncodePane *View::MainWindow::getEncodePane()
{
    return ui->tab_encode;
}

QObjectList View::MainWindow::getAudioPanes()
{
    return ui->tab_sound->children();
}

QTabWidget *View::MainWindow::getVideoPane()
{
    return NULL;
}

InformationPane *View::MainWindow::getInformationPane()
{
    return ui->tab_infos;
}

QObjectList View::MainWindow::getSubtitlePanes()
{
    return ui->tab_subtitle->children();
}

void View::MainWindow::on_tabWidget_currentChanged(int index)
{
    QString inactiveStyle = "background-color: rgb(203, 203, 203);border-radius:5px;";
    QString activeStyle = "background-color: rgb(141, 141, 141);border-radius:5px;";
    ui->labelStatus1->setStyleSheet(inactiveStyle);
    ui->labelStatus3->setStyleSheet(inactiveStyle);
    ui->labelStatus4->setStyleSheet(inactiveStyle);
    ui->labelStatus5->setStyleSheet(inactiveStyle);
    switch (index) {
    case 0:
        ui->labelStatus1->setStyleSheet(activeStyle);
        ui->tab_files->refresh();
        break;
    case 1:
        ui->labelStatus3->setStyleSheet(activeStyle);
        break;
    case 2:
        ui->labelStatus3->setStyleSheet(activeStyle);
        break;
    case 3:
        ui->labelStatus3->setStyleSheet(activeStyle);
        break;
    case 4:
        ui->labelStatus4->setStyleSheet(activeStyle);
        break;
    case 5:
        ui->labelStatus5->setStyleSheet(activeStyle);
        ui->tab_files->refresh();
        break;
    default:
        break;
    }
}

void View::MainWindow::on_OpenSettings()
{
    m_settingsW->showWithRefresh();
}

void View::MainWindow::on_UpdateVersion(){
    m_dispatcher->checkForUpdate();
}

void View::MainWindow::on_SaveProject()
{
    if(m_dispatcher->getCurrentProject()->name() != "" ){
        QString savePath = m_dispatcher->getCurrentProject()->getSavePath();
        if(savePath == "")
            savePath = QFileDialog::getSaveFileName(this,tr("Choisir le fichier de sauvegarde"),"",tr("OCT(*.oct)"));
        if(savePath != "")
            m_dispatcher->save(savePath);
    }else{
        QMessageBox::warning(this,tr("Sauvegarde impossible"),tr("Votre projet n'a pas de chemin d'export."));
    }
}

void View::MainWindow::on_SaveProjectSous()
{
    if(m_dispatcher->getCurrentProject()->name() != "" ){
        QString savePath = QFileDialog::getSaveFileName(this,tr("Choisir le fichier de sauvegarde"),"",tr("OCT(*.oct)"));
        if(savePath != "")
            m_dispatcher->save(savePath);
    }else{
        QMessageBox::warning(this,tr("Sauvegarde impossible"),tr("Votre projet n'a pas de chemin d'export."));
    }
}

void View::MainWindow::on_LoadProject(){
    QString loadPath = QFileDialog::getOpenFileName(this,tr("Choisir le fichier à ouvrir"),"",tr("OCT(*.oct)"));
    if(loadPath != ""){
        m_dispatcher->load(loadPath);
         ui->tab_infos->generateStruct(this->m_dispatcher->getCurrentProject()->informations());
        this->getEncodePane()->refreshProjectPane();
    }
}

void View::MainWindow::on_NewProject(){
    ui->tab_infos->generateEmptyStruct(NULL);
    m_dispatcher->checkProjectValidation();
    m_dispatcher->addToQueue();
}


void View::MainWindow::infosFromBDD(QMap<QString, QString>* infos){
    if(infos != NULL){
        ui->tab_infos->generateStruct(infos);
        //QMessageBox::information(this,tr("Informations pré-remplie"),tr("Les informations pour ce film ont été récupéré"));
    }else{
        QMessageBox::warning(this,tr("Récupération information impossible"),tr("Impossible de trouver des informations pour ce film"));
    }
}

void View::MainWindow::infosFromBDD(){
   ui->tab_infos->generateStruct(NULL);
}

void View::MainWindow::on_viewTorrent(){
    QDesktopServices::openUrl("file:///"+qApp->applicationDirPath()+ "/torrent");
}
