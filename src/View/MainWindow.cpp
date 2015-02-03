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

    foreach (Model::File *file, *(m_dispatcher->getCurrentProject()->fileList())) {
        foreach (Model::StreamWrapper *streamW, *(file->getStreamWrappers())) {
            QWidget *s;
            switch (streamW->oldStream()->getType()) {
                case Model::Stream::AUDIO:
                    s = new AudioPane(file,streamW->oldStream());
                    ui->tabWidgetAudio->addTab(s,file->getName() + " piste : " +streamW->oldStream()->getUID());
                    ((AudioPane*)s)->setDispatcher(m_dispatcher);
                    break;
                case Model::Stream::VIDEO:
                    s = new VideoPane(file,streamW->oldStream());
                    ui->tabWidgetVideo->addTab(s,file->getName() + " piste : " +streamW->oldStream()->getUID());
                    ((VideoPane*)s)->setDispatcher(m_dispatcher);
                    break;
                case Model::Stream::SUBTITLE:
                    s = new SubtitlePane(file,streamW->oldStream());
                    ui->tabWidgetSubtitle->addTab(s,file->getName() + " piste : " +streamW->oldStream()->getUID());
                    ((SubtitlePane*)s)->setDispatcher(m_dispatcher);
                    break;
                default:

                    break;
            };
        }
    }

    ui->tab_encode->refresh();
    ui->tab_infos->refresh();
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
            qDebug()<< "------------------------------";
            int i =0;
            while(this->ui->tabWidgetVideo->widget(i)){
                ((VideoPane*)this->ui->tabWidgetVideo->widget(i))->applyReco();
                qDebug()<< i;
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

QObjectList View::MainWindow::getVideoPanes()
{
    return ui->tab_video->children();
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
