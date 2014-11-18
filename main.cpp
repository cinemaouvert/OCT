#include "Controller/OCTDispatcher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller::OCTDispatcher dispatcher;

    return a.exec();
}
