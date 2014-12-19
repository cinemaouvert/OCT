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

}

void View::MainWindow::refresh()
{
    ui->tab_files->refresh();

    /** video pane **/
    ui->tabWidgetVideo->clear();

    foreach (Model::File *file, *(m_dispatcher->getCurrentProject()->fileList())) {
        foreach (Model::StreamWrapper *streamW, *(file->getStreamWrappers())) {
            switch (streamW->getOldStream()->getType()) {
                case Model::Stream::AUDIO:
                    break;
                case Model::Stream::VIDEO:
                    ui->tabWidgetVideo->addTab(new VideoPane(file,streamW->getOldStream()->getUID().toInt()),file->getName());
                    break;
                case Model::Stream::SUBTITLE:
                    break;
                default:

                    break;
            };
        }
    }
}

View::MainWindow::~MainWindow()
{
    delete ui;
}

// ========================================================================== //
// == EVENT METHODS ========================================================= //
// ========================================================================== //
/*
void View::MainWindow::on_GroupBox_Import_clicked() {
    ui->groupBox_Import->setStyleSheet("background-color: red");
    ui->groupBox_Config->setStyleSheet("background-color: grey");
    ui->groupBox_TracksNaming->setStyleSheet("background-color: grey");
    ui->groupBox_Infos->setStyleSheet("background-color: grey");
    ui->groupBox_Encode->setStyleSheet("background-color: grey");
}

void View::MainWindow::on_GroupBox_Config_clicked() {
    ui->groupBox_Import->setStyleSheet("background-color: red");
    ui->groupBox_Config->setStyleSheet("background-color: red");
    ui->groupBox_TracksNaming->setStyleSheet("background-color: grey");
    ui->groupBox_Infos->setStyleSheet("background-color: grey");
    ui->groupBox_Encode->setStyleSheet("background-color: grey");
}

void View::MainWindow::on_GroupBox_TracksNaming_clicked() {
    ui->groupBox_Import->setStyleSheet("background-color: red");
    ui->groupBox_Config->setStyleSheet("background-color: red");
    ui->groupBox_TracksNaming->setStyleSheet("background-color: red");
    ui->groupBox_Infos->setStyleSheet("background-color: grey");
    ui->groupBox_Encode->setStyleSheet("background-color: grey");
}

void View::MainWindow::on_GroupBox_Infos_clicked() {
    ui->groupBox_Import->setStyleSheet("background-color: red");
    ui->groupBox_Config->setStyleSheet("background-color: red");
    ui->groupBox_TracksNaming->setStyleSheet("background-color: red");
    ui->groupBox_Infos->setStyleSheet("background-color: red");
    ui->groupBox_Encode->setStyleSheet("background-color: grey");
}

void View::MainWindow::on_GroupBox_Encode_clicked() {
    ui->groupBox_Import->setStyleSheet("background-color: red");
    ui->groupBox_Config->setStyleSheet("background-color: red");
    ui->groupBox_TracksNaming->setStyleSheet("background-color: red");
    ui->groupBox_Infos->setStyleSheet("background-color: red");
    ui->groupBox_Encode->setStyleSheet("background-color: red");
}
*/
