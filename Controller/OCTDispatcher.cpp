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

#include "Controller/OCTDispatcher.h"
#include "Controller/StreamLoader.h"
#include "Controller/Updater.h"
#include "Controller/Merger.h"
#include "Controller/Exporter.h"
#include "Controller/TreatmentThread.h"
#include "Controller/Transcoder.h"

#include "View/MainWindow.h"

#include "Model/Project.h"
#include "Model/File.h"
#include "Model/Video.h"
#include "Model/Audio.h"
#include "Model/Subtitle.h"

#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QIODEVICE>

#include <Model/Attachment.h>
#include <Model/Audio.h>
#include <Model/StreamWrapper.h>
#include <Model/Serializable.h>

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
    Model::Video::initStaticParameters();
    Model::Audio::initStaticParameters();
    Model::Subtitle::initStaticParameters();


    /****** TRY YOUR WORK IN HERE **********/
  //  addSetting("ffprobe","C:\\Users\\Moi\\Documents\\M2\\OCT\\ffmpeg-20141020-git-b5583fc-win64-static\\bin\\ffprobe.exe");
    QString program = getSetting("ffprobe").toString();
    QStringList arguments;
        arguments
             <<"-v"<<"quiet"
             << "-print_format"<<"xml"
             <<"-show_streams" <<"C:\\Users\\Moi\\Documents\\M2\\OCT\\ffmpeg-20141020-git-b5583fc-win64-static\\bin\\test-merge.mkv";

    QProcess myProcess(m_mainWindow);
    myProcess.start(program, arguments);
    myProcess.waitForFinished();
    QString string(myProcess.readAllStandardOutput());
    Model::File f("path",string);

    /***************************************/
    /*****Thibaud Test *****/


    /*
    this->addFile("E:\\M2\\Projet\\Test mkvtoolnix\\movie1.mkv");
    qDebug() << this->m_currentProject->fileList()->size();
    this->m_currentProject->fileList()->at(0)->getDatas()->at(0)->setNewStream(this->m_currentProject->fileList()->at(0)->getDatas()->at(0)->getOldStream());
    QStringList *list = this->m_currentProject->fileList()->at(0)->getCommandLine();
    foreach (QString st, *(list)) {
          qDebug() <<"TEST : " + st;
    }
*/
   /*
    QString ffmpegProgram = getSetting("ffmpeg").toString();
    QProcess myProcessFFMPEG(m_mainWindow);
    myProcessFFMPEG.start(ffmpegProgram, *list);
    myProcessFFMPEG.waitForFinished();
    QString retour(myProcessFFMPEG.readAllStandardOutput());
    qDebug()<<retour;
*/

    
    Model::Serializable::initMetaTypes();
    Model::Attachment toto1("TOTO1");
    Model::Attachment toto2("TOTO2");
    Model::Attachment toto3("TOTO3");
    Model::Audio *audio1 = new Model::Audio("3");
    audio1->setParameter("codec_name",Model::Audio::getStaticParameter("codec_name"));
    qDebug() << audio1->getUID();

    QFile file("H:\\TEST\\SerialTEst.OCTSAVE");
    file.open(QIODevice::ReadWrite);
    QDataStream out(&file);
    out << toto1;
    out << toto2;
    out << toto3;
    out << audio1;
    file.close();

    Model::Attachment readedAttachment1;
    Model::Attachment readedAttachment2;
    Model::Attachment readedAttachment3;
    Model::Audio audio2;

    file.open(QIODevice::ReadWrite);
    QDataStream in(&file);
    in >> readedAttachment1;
    in >> readedAttachment2;
    in >> readedAttachment3;
    in >> audio2;
    qDebug() << readedAttachment1.filepath();
    qDebug() << readedAttachment2.filepath();
    qDebug() << readedAttachment3.filepath();
    qDebug() << audio2.getUID();
    foreach (QString st, *(audio2.getCommand())) {
          qDebug() <<"Lecture audio : " + st;
    }

    /***********************/
}

void Controller::OCTDispatcher::addFile(QString filePath) {
    QString program = getSetting("ffprobe").toString();
    QStringList arguments;
        arguments
             <<"-v"<<"quiet"
             << "-print_format"<<"xml"
             <<"-show_streams" <<filePath;

    QProcess myProcess(m_mainWindow);
    myProcess.start(program, arguments);
    myProcess.waitForFinished();
    QString infos(myProcess.readAllStandardOutput());

    Model::File *file = new Model::File(filePath,infos);
    this->m_currentProject->addFileToList(file);
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
    initSetting("mkvToolnix","E:\M2\Projet\Dependances\mkvtoolnix\mkvinfo.exe");
}

void Controller::OCTDispatcher::addSetting(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

QVariant Controller::OCTDispatcher::getSetting(QString key)
{
    return m_settings->value(key);
}


