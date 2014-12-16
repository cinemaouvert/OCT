#-------------------------------------------------
#
# Project created by QtCreator 2014-11-18T10:54:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):
    QT += widgets
    QT += xml
    QT += network

TARGET = OCT_Project
TEMPLATE = app

SOURCES += main.cpp\
    Controller/Exporter.cpp \
    Controller/Merger.cpp \
    Controller/OCTDispatcher.cpp \
    Controller/StreamLoader.cpp \
    Controller/Transcoder.cpp \
    Controller/TreatmentThread.cpp \
    Controller/Updater.cpp \
    Model/Attachment.cpp \
    Model/Audio.cpp \
    Model/Database.cpp \
    Model/File.cpp \
    Model/Information.cpp \
    Model/Parameter.cpp \
    Model/Project.cpp \
    Model/Stream.cpp \
    Model/Subtitle.cpp \
    Model/Video.cpp \
    View/MainWindow.cpp \
    Controller/Utils.cpp \
    Model/Serializable.cpp \
    Model/StreamWrapper.cpp \
    View/FilePane.cpp

HEADERS  += \
    Controller/Exporter.h \
    Controller/Merger.h \
    Controller/OCTDispatcher.h \
    Controller/StreamLoader.h \
    Controller/Transcoder.h \
    Controller/TreatmentThread.h \
    Controller/Updater.h \
    Model/Attachment.h \
    Model/Audio.h \
    Model/Database.h \
    Model/File.h \
    Model/Information.h \
    Model/Parameter.h \
    Model/Project.h \
    Model/Serializable.h \
    Model/Stream.h \
    Model/Subtitle.h \
    Model/Video.h \
    View/MainWindow.h \
    configOCT.h \
    Controller/Utils.h \
    Model/StreamWrapper.h \
    View/FilePane.h

FORMS    += \
<<<<<<< HEAD
    View/mainwindow.ui \
    View/filepane.ui
=======
    mainwindow.ui \
>>>>>>> origin/master
