#include "src/Controller/OCTDispatcher.h"
#include <QApplication>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QDebug>




int main(int argc, char *argv[])
{



    QApplication a(argc, argv);

    Controller::OCTDispatcher dispatcher;

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    qInstallMessageHandler(Controller::OCTDispatcher::customMessageHandler);



    int z = QFontDatabase::addApplicationFont(":/icons/resources/font/foundation-icons/foundation-icons.ttf");

    qDebug() << "font: "<< z;
     qDebug() << QFontDatabase::applicationFontFamilies(0);


    return a.exec();
}


