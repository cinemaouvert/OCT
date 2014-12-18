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
    QT += multimediawidgets
    QT += multimedia

CONFIG += av

TARGET = OCT_Project
TEMPLATE = app

SOURCES += src/main.cpp\
    src/Controller/Exporter.cpp \
    src/Controller/Merger.cpp \
    src/Controller/OCTDispatcher.cpp \
    src/Controller/StreamLoader.cpp \
    src/Controller/Transcoder.cpp \
    src/Controller/TreatmentThread.cpp \
    src/Controller/Updater.cpp \
    src/Model/Attachment.cpp \
    src/Model/Audio.cpp \
    src/Model/Database.cpp \
    src/Model/File.cpp \
    src/Model/Information.cpp \
    src/Model/Parameter.cpp \
    src/Model/Project.cpp \
    src/Model/Stream.cpp \
    src/Model/Subtitle.cpp \
    src/Model/Video.cpp \
    src/View/MainWindow.cpp \
    src/Controller/Utils.cpp \
    src/Model/Serializable.cpp \
    src/Model/StreamWrapper.cpp \
    src/View/FilePane.cpp \
    src/View/VideoPane.cpp \
    src/View/AudioPane.cpp \
    src/View/InformationPane.cpp \
    src/View/SubtitlePane.cpp \
    src/View/EncodePane.cpp \
    src/View/VideoPlayer.cpp

HEADERS  += \
    src/Controller/Exporter.h \
    src/Controller/Merger.h \
    src/Controller/OCTDispatcher.h \
    src/Controller/StreamLoader.h \
    src/Controller/Transcoder.h \
    src/Controller/TreatmentThread.h \
    src/Controller/Updater.h \
    src/Model/Attachment.h \
    src/Model/Audio.h \
    src/Model/Database.h \
    src/Model/File.h \
    src/Model/Information.h \
    src/Model/Parameter.h \
    src/Model/Project.h \
    src/Model/Serializable.h \
    src/Model/Stream.h \
    src/Model/Subtitle.h \
    src/Model/Video.h \
    src/View/MainWindow.h \
    src/configOCT.h \
    src/Controller/Utils.h \
    src/Model/StreamWrapper.h \
    src/View/FilePane.h \
    src/View/VideoPane.h \
    src/View/AudioPane.h \
    src/View/InformationPane.h \
    src/View/SubtitlePane.h \
    src/View/EncodePane.h \
    src/View/VideoPlayer.h

FORMS    += \
    src/View/mainwindow.ui \
    src/View/filepane.ui \
    src/View/videopane.ui \
    src/View/audiopane.ui \
    src/View/informationpane.ui \
    src/View/subtitlepane.ui \
    src/View/encodepane.ui \
    src/View/videoplayer.ui

RESOURCES += images.qrc
