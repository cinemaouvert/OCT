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
    View/AudioPane.cpp \
    View/EncodePane.cpp \
    View/FilePane.cpp \
    View/InformationPane.cpp \
    View/MainWindow.cpp \
    View/SubtitlePane.cpp \
    View/VideoPane.cpp \
    View/VideoPlayer.cpp \
    Controller/Utils.cpp \
    Model/Serializable.cpp \
    Model/StreamWrapper.cpp

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
    View/AudioPane.h \
    View/EncodePane.h \
    View/FilePane.h \
    View/InformationPane.h \
    View/MainWindow.h \
    View/SubtitlePane.h \
    View/VideoPane.h \
    View/VideoPlayer.h \
    configOCT.h \
    Controller/Utils.h \
    Model/StreamWrapper.h

FORMS    += \
    mainwindow.ui
