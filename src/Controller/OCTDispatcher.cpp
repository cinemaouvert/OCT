/**********************************************************************************
 * This file is part of Open Cinema Transcoder (OCT).
 *
 * Copyright (C) 2014 Catalogue Ouvert du Cinéma <dev@cinemaouvert.fr>
 *
 * Authors: Romain Boutin <romain.boutin@etu.univ-poitiers.fr>
 *          Thibaud Lamarche <lamarchethibaud@hotmail.com>
 *          William Le Coroller <william.le.coroller@gmail.com>
 *          Denis Saunier <saunier.denis.86@gmail.com>
 *
 * Open Cinema Transcoder is an initiative of Catalogue Ouvert du Cinéma.
 * The software was developed by four students of University of Poitiers
 * as school project.
 *
 * Open Cinema Transcoder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Open Cinema Transcoder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open Cinema Transcoder. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************************/
#include <exception>
#include <vector>

using namespace std;

#include "src/Controller/OCTDispatcher.h"
#include "src/Controller/StreamLoader.h"
#include "src/Controller/Updater.h"
#include "src/Controller/Merger.h"
#include "src/Controller/Exporter.h"
#include "src/Controller/TreatmentThread.h"
#include "src/Controller/Transcoder.h"

#include "src/View/MainWindow.h"

#include "src/Model/Project.h"
#include "src/Model/File.h"
#include "src/Model/Video.h"
#include "src/Model/Audio.h"
#include "src/Model/Subtitle.h"
#include "src/Model/StreamWrapper.h"

#include "loggersingleton.h"

#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QTranslator>
//#include <QIODEVICE>
#include <QMimeDatabase>
#include <QApplication>

#include <src/Model/Attachment.h>
#include <src/Model/Audio.h>
#include <src/Model/StreamWrapper.h>
#include <src/Model/Serializable.h>
#include <src/Model/Project.h>

#include <src/View/FilePane.h>
#include <src/View/EncodePane.h>

// ========================================================================== //
// == Constructor =========================================================== //
// ========================================================================== //
Controller::OCTDispatcher::OCTDispatcher() :m_currentProject(NULL) ,
    m_mainWindow(NULL) ,
    m_settings(NULL) ,
    m_streamLoader(NULL) ,
    m_updater(NULL) ,
                                            m_merger(NULL) ,
                                            m_exporter(NULL) ,
                                            m_projects(NULL) ,
                                            m_treatmentThread(NULL) ,
                                            m_transcoder(NULL),
                                            m_OCPMvalidation(NULL),
                                            m_informationMovieStruct(NULL) {
    //Init Projects
    m_projects = new QList<Model::Project*>();
    //Creation of the Project
    m_currentProject = new Model::Project();
    m_projects->push_back(m_currentProject);
    //Creations of the settings
    m_settings = new QSettings("CinemaOuvert", "OpenCinemaTranscoder");
    initSettings();
    //Creation of the controllers
    m_streamLoader = new StreamLoader();
    m_updater= new Updater();
    m_merger= new Merger();
    //ne pas init ici
    //m_exporter= new Exporter();
    m_informationMovieStruct = Exporter::getInformations();

    m_transcoder= new Transcoder();

    m_treatmentThread= new TreatmentThread(m_projects,m_transcoder,m_merger,m_exporter);

    m_OCPMvalidation = new Model::OCPMValidation(this);

    //Initialisation of the parameters lists
    Model::Video::initStaticParameters();
    Model::Audio::initStaticParameters();
    Model::Subtitle::initStaticParameters();

    //Creation of the view

    QTranslator *translator = new QTranslator();
    QString translationFile = "oct_";
    translationFile += m_settings->value("language").toString();

    if(translationFile != "oct_"){
        translator->load(translationFile, qApp->applicationDirPath()+QDir::separator()+"languages");
        qApp->installTranslator(translator);
    }


    m_mainWindow = new View::MainWindow(0,this);
    m_mainWindow->show();

    /****** TRY YOUR WORK IN HERE **********/

    /*****Thibaud Test *****/
/*
    addFile("H:\\Media\\movie2.mkv");
    addFile("H:\\Media\\movie1.mkv");
    addFile("C:\\Users\\Thibaud\\Downloads\\dom.srt");
    addFile("C:\\Users\\Thibaud\\Downloads\\2838-etoiles-fin-fond-univers-WallFizz.jpg");

    Model::Stream *os = this->m_currentProject->fileList()->at(1)->getStreamWrappers()->at(0)->oldStream();
    Model::Stream *ns = new Model::Video((Model::Video&)*os);
    ns->getParameters()->value(Model::Stream::CODEC_NAME)->setValue("avi");

    this->m_currentProject->fileList()->at(1)->getStreamWrappers()->at(0)->setNewStream(ns);


    Model::Stream *os2 = this->m_currentProject->fileList()->at(0)->getStreamWrappers()->at(1)->oldStream();
    Model::Stream *ns2 = new Model::Audio((Model::Audio&)*os2);
    ns2->getParameters()->value(Model::Stream::CODEC_NAME)->setValue("flac");

    this->m_currentProject->fileList()->at(0)->getStreamWrappers()->at(1)->setNewStream(ns2);

    Model::Stream *os = this->m_currentProject->fileList()->at(0)->getStreamWrappers()->at(0)->oldStream();
    Model::Stream *ns = new Model::Video((Model::Video&)*os);
    ns->getParameters()->value(Model::Stream::RESOLUTION)->setValue("1920x1080");

    this->m_currentProject->fileList()->at(0)->getStreamWrappers()->at(0)->setNewStream(ns);

*/

    /***********************/
    /*****Romain Test *****/



/*
    qDebug() <<  *m_currentProject->getMergeCommandLine();

    m_merger->createMKVFile(m_currentProject);
*/

/*    addFile("C:\\Users\\Moi\\Documents\\GitHub\\build-OCT_Project-Desktop_Qt_5_3_MinGW_32bit-Debug\\test\\test2.mkv");
    addFile("C:\\Users\\Moi\\Documents\\GitHub\\build-OCT_Project-Desktop_Qt_5_3_MinGW_32bit-Debug\\test\\test.mp3");
    addFile("C:\\Users\\Moi\\Documents\\GitHub\\build-OCT_Project-Desktop_Qt_5_3_MinGW_32bit-Debug\\test\\test.ass");
    addFile("C:\\Users\\Moi\\Documents\\GitHub\\build-OCT_Project-Desktop_Qt_5_3_MinGW_32bit-Debug\\test\\test.jpg");
    addFile("C:\\Users\\Moi\\Documents\\GitHub\\build-OCT_Project-Desktop_Qt_5_3_MinGW_32bit-Debug\\test\\test.xml");

    Model::Stream *os = this->m_currentProject->fileList()->at(0)->getStreamWrappers()->at(0)->oldStream();
    Model::Stream *ns = new Model::Video((Model::Video&)*os);
    ns->getParameters()->take(Model::Stream::CODEC_NAME)->setValue("mpeg4");
    this->m_currentProject->fileList()->at(0)->getStreamWrappers()->at(0)->setNewStream(ns);


    this->startTreatment();
*/
    /***********************/
    /*****Denis Test *****/
    //this->startTreatment();

    /***********************/
    /*****William Test *****/


    /***********************/
}

// ========================================================================== //
// == Destructor ============================================================ //
// ========================================================================== //
Controller::OCTDispatcher::~OCTDispatcher() {
    if(m_currentProject) delete m_currentProject  ;
    if(m_mainWindow) delete m_mainWindow  ;
    if(m_settings) delete m_settings  ;
    if(m_streamLoader) delete m_streamLoader   ;
    if(m_updater) delete m_updater  ;
    if(m_merger) delete m_merger  ;
    if(m_exporter) delete  m_exporter ;
    if(m_projects) delete  m_projects ;
    if(m_treatmentThread) delete  m_treatmentThread ;
    if(m_transcoder) delete m_transcoder  ;
    if(m_OCPMvalidation) delete  m_OCPMvalidation ;
    LoggerSingleton::destroyInstance();
}

// ========================================================================== //
// == Accessor and mutator methods ========================================== //
// ========================================================================== //
Model::Project *Controller::OCTDispatcher::getCurrentProject() const {
    return this->m_currentProject;
}

QList<Model::Project *> *Controller::OCTDispatcher::getProjects() {
    return this->m_projects;
}

Model::OCPMValidation *Controller::OCTDispatcher::getOCPMValidation() {
    return this->m_OCPMvalidation;
}

Controller::TreatmentThread *Controller::OCTDispatcher::getTreatmentThread() {
    return this->m_treatmentThread;
}

void Controller::OCTDispatcher::addSetting(const QString &key, const QVariant &value) {
    m_settings->setValue(key, value);
}

QVariant Controller::OCTDispatcher::getSetting(QString key) {
    return m_settings->value(key);
}

QStringList *Controller::OCTDispatcher::informationMovieStruct() const {
    return m_informationMovieStruct;
}

// ========================================================================== //
// == Class methods ========================================================= //
// ========================================================================== //
void Controller::OCTDispatcher::addFile(QString filePath) {
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(filePath);
    if(mime.name().contains("video") || mime.name().contains("audio") || mime.name().contains("subrip") || mime.name().contains("ssa") || mime.name().contains("ass")){
        QString infos(m_transcoder->getInfo(filePath));
        Model::File *file = new Model::File(filePath,infos);
        this->m_currentProject->addFileToList(file);
    }
    else{
        Model::Attachment *attachement = new Model::Attachment(filePath);
        this->m_currentProject->addAttachment(attachement);
    }
    this->m_mainWindow->refresh();
}

void Controller::OCTDispatcher::removeFile(QString filePath) {
    this->m_currentProject->removeFile(filePath);
    this->m_mainWindow->refresh();
}

void Controller::OCTDispatcher::save(QString path) {
    if(path == "")
        path = m_currentProject->getSavePath();
    else
        m_currentProject->setSavePath(path);
    QFile file(path);
    file.open(QIODevice::ReadWrite);
    QDataStream out(&file);
    out << *m_currentProject;
    file.close();
}

void Controller::OCTDispatcher::load(QString path) {
    QFile file(path);
    file.open(QIODevice::ReadWrite);
    QDataStream in(&file);
    m_currentProject = new Model::Project;
    in >> *m_currentProject;
    m_projects->append(m_currentProject);
    this->m_mainWindow->refresh();
    file.close();
    //Refresh Information Struct
    this->m_mainWindow->infosFromBDD(NULL);
}

void Controller::OCTDispatcher::startTreatment() {
    m_treatmentThread->initTreatment();

    m_startTreatmentThread = new QThread();
    m_treatmentThread->moveToThread(m_startTreatmentThread);
    /*
    connect(m_startTreatmentThread, SIGNAL(started()), m_treatmentThread, SLOT(startTreatment()));
    connect(m_treatmentThread, SIGNAL(finished()), m_startTreatmentThread, SLOT(quit()));
    //connect(m_transcoder, SIGNAL(finished()), m_transcoder, SLOT(deleteLater()));

    connect(m_startTreatmentThread, SIGNAL(finished()), m_startTreatmentThread, SLOT(deleteLater()));
    //*/
    connect(m_startTreatmentThread, SIGNAL(started()), m_treatmentThread, SLOT(startTreatment()));
    connect(m_treatmentThread, SIGNAL(finished()), m_startTreatmentThread, SLOT(quit()));
    connect(m_treatmentThread, SIGNAL(finished()), m_treatmentThread, SLOT(deleteLater()));
    connect(m_startTreatmentThread, SIGNAL(finished()), m_startTreatmentThread, SLOT(deleteLater()));

    m_startTreatmentThread->start();
}

void Controller::OCTDispatcher::pauseTreatment() {
    if(m_startTreatmentThread != NULL){
        qDebug() << "PAUSE";
        m_treatmentThread->pauseTreatment();
    }
}

void Controller::OCTDispatcher::restartTreatment() {
    if(m_startTreatmentThread != NULL){
        qDebug() << "RESTART";
        m_treatmentThread->restartTreatment();
    }
}

void Controller::OCTDispatcher::stopTreatment() {
    if(m_startTreatmentThread != NULL){
        if(m_startTreatmentThread->isRunning())
            m_treatmentThread->stopTreatment();
    }
}

void Controller::OCTDispatcher::addToQueue() {
    Model::Project *project = new Model::Project();
    m_projects->push_back(project);
    m_currentProject = project;
    m_mainWindow->refresh();
}

void Controller::OCTDispatcher::checkForUpdate() {
    m_updater->checkVersion();
}

void Controller::OCTDispatcher::initSetting(const QString &key, const QVariant &value) {
    if(!m_settings->contains(key)){
        addSetting(key,value);
    }
}

void Controller::OCTDispatcher::initSettings() {
    #if defined(Q_OS_WIN)
        initSetting("ffmpeg",qApp->applicationDirPath() +"/ffmpeg-20150129-git-4155f2d-win64-static/bin/ffmpeg.exe");
        initSetting("ffprobe",qApp->applicationDirPath() +"/ffmpeg-20150129-git-4155f2d-win64-static/bin/ffprobe.exe");
        initSetting("mkvToolnix",qApp->applicationDirPath() +"/mkvtoolnix/mkvinfo.exe");
    #endif

}

void Controller::OCTDispatcher::setCurrentProjectIndex(int index) {
    m_currentProject = m_projects->at(index);
    m_mainWindow->refresh();
}

void Controller::OCTDispatcher::duplicateProject(int index) {
    Model::Project *project = new Model::Project(*(m_projects->at(index)));
    m_projects->append(project);
}

void Controller::OCTDispatcher::closeProject(int index)
{
    Model::Project *project = m_projects->takeAt(index);
    if(m_projects->size()==0){
       addToQueue();
    }
    setCurrentProjectIndex(0);
    delete project;
}

// ========================================================================== //
// == Public slot methods =================================================== //
// ========================================================================== //
void Controller::OCTDispatcher::treatProjectNameChanged(QString newName) {
    m_currentProject->setName(newName);
    m_mainWindow->getEncodePane()->refreshProjectPane();
}

bool Controller::OCTDispatcher::checkProjectValidation() {
    bool retVal = true;
    foreach (Model::File *file, *(m_currentProject->fileList())) {
        foreach (Model::StreamWrapper *streamW, *(file->getStreamWrappers())) {
            retVal = retVal && checkStreamValidation(streamW->getRelevantStream());
        }
    }
    retVal = retVal && (checkInformationValidation() == 0) && checkCommunicationValidation() ;

    m_mainWindow->setOCPMState(retVal);
    return retVal;
}

bool Controller::OCTDispatcher::checkStreamValidation(Model::Stream *stream) {
    bool retVal = true;
    switch(stream->getType()){
        case Model::Stream::VIDEO:
            retVal = retVal && m_OCPMvalidation->isValidVideo(stream);
            break;
        case Model::Stream::AUDIO:
            retVal = retVal && m_OCPMvalidation->isValidAudio(stream);
            break;
        case Model::Stream::SUBTITLE:
            retVal = retVal && m_OCPMvalidation->isValidSubtitle(stream);
            break;
    }
    return retVal;
}




int Controller::OCTDispatcher::checkInformationValidation() {
    if(!m_informationMovieStruct || !(this->getCurrentProject()->informations()))
        return -1;
    return m_informationMovieStruct->size() - this->getCurrentProject()->informations()->size();
}

bool Controller::OCTDispatcher::checkCommunicationValidation() {
    return checkPosterValidation() && checkCaptureValidation();
}

bool Controller::OCTDispatcher::checkPosterValidation() {
    if(this->getCurrentProject()->informations() == NULL) {
        return false;
    } else {
        return this->getCurrentProject()->informations()->contains("affiche");
    }
}

bool Controller::OCTDispatcher::checkCaptureValidation() {
    if(this->getCurrentProject()->informations() == NULL) {
        return false;
    } else {
        return this->getCurrentProject()->informations()->contains("capture");
    }
}

void Controller::OCTDispatcher::parameterChanged(Model::File *file,Model::Stream *stream,QString parameterName, QString value) {
    value = value.toLower();
    foreach (Model::StreamWrapper *sW, *(file->getStreamWrappers())) {
        if(*(sW->oldStream()) == *stream){
            if(sW->newStream() == NULL){
                switch(stream->getType()){
                    case Model::Stream::VIDEO:
                        sW->setNewStream(new Model::Video(*(Model::Video*)(sW->oldStream())));
                    break;
                    case Model::Stream::AUDIO:
                        sW->setNewStream(new Model::Audio(*(Model::Audio*)(sW->oldStream())));
                    break;
                    case Model::Stream::SUBTITLE:
                        sW->setNewStream(new Model::Subtitle(*(Model::Subtitle*)(sW->oldStream())));
                    break;
                }
            }

            Model::Parameter *param = sW->newStream()->getParameters()->value(parameterName);
            if(param == NULL){
                switch(stream->getType()){
                    case Model::Stream::VIDEO:
                        param = Model::Video::getStaticParameter(parameterName);
                    break;
                    case Model::Stream::AUDIO:
                        param = Model::Audio::getStaticParameter(parameterName);
                    break;
                    case Model::Stream::SUBTITLE:
                        param = Model::Subtitle::getStaticParameter(parameterName);
                    break;
                }
                sW->getRelevantStream()->setParameter(parameterName,param);
            }

            param->setValue(value);
            checkProjectValidation();
            return;
        }
    }
}

void Controller::OCTDispatcher::parameterChangedMKV(int p, Model::File *file, Model::Stream *stream, QString value) {
    foreach (Model::StreamWrapper *sW, *(file->getStreamWrappers())) {
        if(*(sW->oldStream()) == *stream){
          /*  if(sW->newStream() == NULL){
                switch(stream->getType()){
                    case Model::Stream::VIDEO:
                        sW->setNewStream(new Model::Video(*(Model::Video*)(sW->oldStream())));
                    break;
                    case Model::Stream::AUDIO:
                        sW->setNewStream(new Model::Audio(*(Model::Audio*)(sW->oldStream())));
                    break;
                    case Model::Stream::SUBTITLE:
                        sW->setNewStream(new Model::Subtitle(*(Model::Subtitle*)(sW->oldStream())));
                    break;
                }
            }*/
            if(p == 1){
                sW->getRelevantStream()->setDelay(value);
            }
            else if (p == 2){
                sW->getRelevantStream()->setName(value);
            }
        }
    }
}

void Controller::OCTDispatcher::customMessageHandler(QtMsgType type, const QMessageLogContext &context,const QString& msg) {
    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1]\n").arg(dt);

    switch (type) {
    case QtDebugMsg:
        txt += QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt += QString("Warning: %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt += QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        txt += QString("Fatal: %1").arg(msg);
        abort();
    default:
        txt += QString("Other: %1").arg(msg);
    }

    QFile outFile("debuglog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
    outFile.close();

    LoggerSingleton::getInstance()->writeMessage(txt);
}

void Controller::OCTDispatcher::getInformations(QString nameMovie){
    this->m_exporter = new Exporter(this->m_currentProject->userKey(), this->m_currentProject->depot());
    this->m_mainWindow->infosFromBDD(this->m_exporter->getMovieInfoByTitle(nameMovie));
}

