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

#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QIODEVICE>
#include <QMimeDatabase>

#include <src/Model/Attachment.h>
#include <src/Model/Audio.h>
#include <src/Model/StreamWrapper.h>
#include <src/Model/Serializable.h>
#include <src/Model/Project.h>

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
    //ne pas init ici
    //m_exporter= new Exporter();
    m_treatmentThread= new TreatmentThread(m_projects,m_transcoder,m_merger,m_exporter);
    m_transcoder= new Transcoder();
    //Initialisation of the parameters lists
    Model::Video::initStaticParameters();
    Model::Audio::initStaticParameters();
    Model::Subtitle::initStaticParameters();


    /****** TRY YOUR WORK IN HERE **********/

    /*****Thibaud Test *****/


    /***********************/
    /*****Romain Test *****/
/*
    initSetting("ffmpeg","C:\\Users\\Moi\\Documents\\M2\\OCT\\ffmpeg-20141020-git-b5583fc-win64-static\\bin\\ffmpeg.exe");
    initSetting("ffprobe","C:\\Users\\Moi\\Documents\\M2\\OCT\\ffmpeg-20141020-git-b5583fc-win64-static\\bin\\ffprobe.exe");
    initSetting("mkvmerge","C:\\Users\\Moi\\Documents\\M2\\OCT\\mkvtoolnix\\mkvmerge.exe");

    qDebug() <<  *m_currentProject->getMergeCommandLine();

    m_merger->createMKVFile(m_currentProject);
*/
    /***********************/
    /*****Denis Test *****/

    /***********************/
    /*****William Test *****/


    /***********************/
}

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

void Controller::OCTDispatcher::removeFile(QString filePath)
{
    this->m_currentProject->removeFile(filePath);
    this->m_mainWindow->refresh();
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
    m_updater->checkVersion();
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

Model::Project *Controller::OCTDispatcher::getCurrentProject() const
{
    return this->m_currentProject;
}

void Controller::OCTDispatcher::addSetting(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

QVariant Controller::OCTDispatcher::getSetting(QString key)
{
    return m_settings->value(key);
}

