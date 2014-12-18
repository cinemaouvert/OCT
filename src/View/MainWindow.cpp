#include "mainwindow.h"
#include "ui_mainwindow.h"

View::MainWindow::MainWindow(QWidget *parent,Controller::OCTDispatcher *theDispatcher) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dispatcher(theDispatcher)
{
    ui->setupUi(this);
    ui->tab_files->setDispatcher(m_dispatcher);
}

View::MainWindow::~MainWindow()
{
    delete ui;
}
