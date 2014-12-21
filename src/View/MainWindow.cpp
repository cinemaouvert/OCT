#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "src/Model/StreamWrapper.h"

#include "src/Model/Stream.h"

View::MainWindow::MainWindow(QWidget *parent,Controller::OCTDispatcher *theDispatcher) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dispatcher(theDispatcher)
{
    ui->setupUi(this);
    ui->tab_files->setDispatcher(m_dispatcher);
    ui->tabWidgetVideo->clear();
    ui->tabWidgetSubtitle->clear();
    ui->tabWidgetAudio->clear();
    setOCPMState(false);
}

void View::MainWindow::refresh()
{
    ui->tab_files->refresh();

    /** video pane **/
    ui->tabWidgetVideo->clear();
    ui->tabWidgetSubtitle->clear();
    ui->tabWidgetAudio->clear();

    foreach (Model::File *file, *(m_dispatcher->getCurrentProject()->fileList())) {
        foreach (Model::StreamWrapper *streamW, *(file->getStreamWrappers())) {
            switch (streamW->getOldStream()->getType()) {
                case Model::Stream::AUDIO:
                    ui->tabWidgetAudio->addTab(new AudioPane(file,streamW->getOldStream()),file->getName() + " piste : " +streamW->getOldStream()->getUID());
                    break;
                case Model::Stream::VIDEO:
                    ui->tabWidgetVideo->addTab(new VideoPane(file,streamW->getOldStream()),file->getName() + " piste : " +streamW->getOldStream()->getUID());
                    break;
                case Model::Stream::SUBTITLE:
                    ui->tabWidgetSubtitle->addTab(new SubtitlePane(file,streamW->getOldStream()),file->getName() + " piste : " +streamW->getOldStream()->getUID());
                    break;
                default:

                    break;
            };
        }
    }

    ui->tab_encode->refresh();
}

View::MainWindow::~MainWindow()
{
    delete ui;
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

void View::MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->labelStatus1->setStyleSheet("background-color: rgb(203, 203, 203);border-radius:5px;");
    ui->labelStatus2->setStyleSheet("background-color: rgb(203, 203, 203);border-radius:5px;");
    ui->labelStatus3->setStyleSheet("background-color: rgb(203, 203, 203);border-radius:5px;");
    ui->labelStatus4->setStyleSheet("background-color: rgb(203, 203, 203);border-radius:5px;");
    ui->labelStatus5->setStyleSheet("background-color: rgb(203, 203, 203);border-radius:5px;");
    switch (index) {
    case 0:
        ui->labelStatus1->setStyleSheet("background-color: rgb(141, 141, 141);border-radius:5px;");
        break;
    case 1:
        ui->labelStatus3->setStyleSheet("background-color: rgb(141, 141, 141);border-radius:5px;");
        break;
    case 2:
        ui->labelStatus3->setStyleSheet("background-color: rgb(141, 141, 141);border-radius:5px;");
        break;
    case 3:
        ui->labelStatus3->setStyleSheet("background-color: rgb(141, 141, 141);border-radius:5px;");
        break;
    case 4:
        ui->labelStatus4->setStyleSheet("background-color: rgb(141, 141, 141);border-radius:5px;");
        break;
    case 5:
        ui->labelStatus5->setStyleSheet("background-color: rgb(141, 141, 141);border-radius:5px;");
        break;
    default:
        break;
    }
}
