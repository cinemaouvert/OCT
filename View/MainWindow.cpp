
#include "View/MainWindow.h"
#include "Controller/OCTDispatcher.h"
#include "View/FilePane.h"

#include "../View/MainWindow.h"
#include "ui_mainwindow.h"

View::MainWindow::MainWindow(QWidget *parent,Controller::OCTDispatcher *theDispatcher) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dispatcher(theDispatcher)
{
    ui->setupUi(this);
}

View::MainWindow::~MainWindow()
{
    delete ui;
}
