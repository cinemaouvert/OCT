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
}

View::MainWindow::~MainWindow()
{
    delete ui;
}
