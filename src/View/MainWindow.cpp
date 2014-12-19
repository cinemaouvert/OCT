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
