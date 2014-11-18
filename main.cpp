#include "View/MainWindow.h"
#include "Controller/OCTDispatcher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View::MainWindow w;
    Controller::OCTDispatcher dispatcher;
    w.show();

    return a.exec();
}
