#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "src/Model/StreamWrapper.h"

#include "src/Model/Stream.h"

View::MainWindow::MainWindow(QWidget *parent,Controller::OCTDispatcher *theDispatcher) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dispatcher(theDispatcher),
    m_settingsW(NULL)
{
    ui->setupUi(this);
    ui->tab_files->setDispatcher(m_dispatcher);
    ui->tab_encode->setDispatcher(m_dispatcher);
    ui->tab_infos->setDispatcher(m_dispatcher);
    ui->tabWidgetVideo->clear();
    ui->tabWidgetSubtitle->clear();
    ui->tabWidgetAudio->clear();
    setOCPMState(false);

    m_settingsW = new ParametersDialog();
    connect(ui->actionPreferences, SIGNAL(triggered()),SLOT(on_OpenSettings()));
}

void View::MainWindow::refresh()
{
    ui->tab_files->refresh();

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
