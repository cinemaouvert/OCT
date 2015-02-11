#include "src/Controller/OCTDispatcher.h"
#include <QApplication>
#include <QStyleFactory>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller::OCTDispatcher dispatcher;

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    qInstallMessageHandler(Controller::OCTDispatcher::customMessageHandler);

    return a.exec();
}


