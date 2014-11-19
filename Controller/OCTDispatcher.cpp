#include <exception>
#include <vector>


using namespace std;

#include "Controller/OCTDispatcher.h"
#include "Controller/StreamLoader.h"
#include "Controller/Updater.h"
#include "Controller/Merger.h"
#include "Controller/Exporter.h"
#include "Controller/TreatmentThread.h"
#include "Controller/Transcoder.h"
#include "Model/Project.h"
#include "Model/Video.h"
#include "View/MainWindow.h"

#include <QDebug>

#include <Model/parameters.h>

Controller::OCTDispatcher::OCTDispatcher() :m_currentProject(NULL) ,
                                            m_mainWindow(NULL) ,
                                            m_settings(NULL) ,
                                            m_streamLoader(NULL) ,
                                            m_updater(NULL) ,
                                            m_merger(NULL) ,
                                            m_exporter(NULL) ,
                                            m_projects(NULL) ,
                                            m_treatmentThread(NULL) ,
                                            m_transcoder(NULL)  {
    //Init Projects
    m_projects = new QList<Model::Project*>();
    //Creation of the Project
    m_currentProject = new Model::Project();
    m_projects->push_back(m_currentProject);
    //Creation of the view
    m_mainWindow = new View::MainWindow(0,this);
    m_mainWindow->show();
    //Creations of the settings
    m_settings = new QSettings("CinemaOuvert", "OpenCinemaTranscoder");
    initSettings();
    //Creation of the controllers
    m_streamLoader = new StreamLoader();
    m_updater= new Updater();
    m_merger= new Merger();
    m_exporter= new Exporter();
    m_treatmentThread= new TreatmentThread(m_projects,m_transcoder,m_merger,m_exporter);
    m_transcoder= new Transcoder();
    //Initialisation of the parameters lists
    Model::Parameters::init();


    /****** TRY YOUR WORK IN HERE **********/





    /***************************************/
    /*****Thibaud Test *****/
    Model::Parameter param = *(Model::Parameters::getVideoParameter("language"));
    param.setValue("eng");
    qDebug() << param.commandAndValue();

    /***********************/
}

void Controller::OCTDispatcher::addFile(QString filePath) {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::save() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::load() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::startTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::pauseTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::restartTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::stopTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::addToQueue() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::checkForUpdate() {
    throw "Not yet implemented";
}

void Controller::OCTDispatcher::initSetting(const QString &key, const QVariant &value)
{
    if(!m_settings->contains(key)){
        addSetting(key,value);
    }
}

void Controller::OCTDispatcher::initSettings()
{
    initSetting("ffmpeg","E:\\M2\\Projet\\Dependances\\ffmpeg-20141020-git-b5583fc-win64-static\\bin\\ffmpeg.exe");
    initSetting("ffprobe","E:\\M2\\Projet\\Dependances\\ffmpeg-20141020-git-b5583fc-win64-static\\bin\\ffprobe.exe");
    initSetting("mkvToolnix","E:\\M2\\Projet\\Dependances\\mkvtoolnix\\mkvinfo.exe");

}

void Controller::OCTDispatcher::addSetting(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

QVariant Controller::OCTDispatcher::getSetting(QString key)
{
    return m_settings->value(key);
}


