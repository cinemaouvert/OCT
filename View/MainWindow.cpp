
#include "View/MainWindow.h"
#include "Controller/OCTDispatcher.h"
#include "View/FilePane.h"

#include "../View/MainWindow.h"
#include "ui_mainwindow.h"

View::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

View::MainWindow::~MainWindow()
{
    delete ui;
}
