#include "MainWindow.h"
#include "ui_mainwindow.h"

View::MainWindow::MainWindow(QWidget *parent,Controller::OCTDispatcher *theDispatcher) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dispatcher(theDispatcher)
{
    ui->setupUi(this);
    ui->tab_files->setDispatcher(m_dispatcher);
}

void View::MainWindow::refresh()
{
    ui->tab_files->refresh();

    /** video pane **/
   /* (QTabWidget*)((QWidget*)(ui->tab_video)->children()->at(0))->clear();
    foreach (Model::File *file, m_dispatcher->getCurrentProject()->fileList()) {
        file->getFilePath();
        ((QTabWidget)ui->tab_video->childAt(0)).insertTab(0,new VideoPane(file,0),file->getFilePath());
    }
    */
}

View::MainWindow::~MainWindow()
{
    delete ui;
}
