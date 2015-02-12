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

#include <QCoreApplication>
#include <exception>
#include <vector>
using namespace std;

#include "src/Model/Project.h"
#include "src/Model/Attachment.h"
#include "Subtitle.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>
#include <QCoreApplication>



Model::Project::Project() : m_attachments (NULL),m_informations(NULL), m_fileList(NULL)
{
    this->m_attachments = new QList<Model::Attachment*>();
    this->m_informations =  new QMap<QString, QString>;
    this->m_fileList = new QList<Model::File*>();
    this->m_name = "";
}

Model::Project::~Project()
{
    if(this->m_attachments)     delete this->m_attachments;
    if(this->m_fileList)        delete this->m_fileList;
    if(this->m_informations)    delete this->m_informations;
}

Model::Project &Model::Project::operator=(const Model::Project &project)
{
    if (this != &project) {
        m_name = project.m_name;
        m_xmlFilePath = project.m_xmlFilePath;
        m_createMagnet = project.m_createMagnet;
        //m_attachments = new QList<Model::Attachment*>(*project.m_attachments);
        //m_attachments = new QList<Model::Attachment*>();
        //m_attachments = project.m_attachments;
        //m_informations = new QList<Model::Information*>(*project.m_informations);
        //m_informations = new QList<Model::Information*>();
        //m_informations = project.m_informations;
        //m_fileList = new QList<Model::File*>(*project.m_fileList);
        //m_fileList = new QList<Model::File*>();
        //m_fileList = project.m_fileList;


        m_fileList = new QList<Model::File*>();
        for(int i = 0; i < project.m_fileList->size(); i++){
            Model::File *p = new Model::File(*project.m_fileList->at(i));
            m_fileList->push_back(p);
        }

        m_attachments = new QList<Model::Attachment*>();
        for(int i = 0; i < project.m_attachments->size(); i++){
            Model::Attachment *p = new Model::Attachment(*project.m_attachments->at(i));
            m_attachments->push_back(p);
        }

        m_informations = new QMap<QString, QString>;
        QMap<QString, QString>::const_iterator i = project.m_informations->constBegin();
         while (i != project.m_informations->constEnd()) {
             m_informations->insert(i.key(), i.value());
             ++i;
         }
    }
    return *this;
}

Model::Project::Project(const Model::Project &project)
{
    m_name = project.m_name;
    m_xmlFilePath = project.m_xmlFilePath;
    m_createMagnet = project.m_createMagnet;

    m_fileList = new QList<Model::File*>();
    for(int i = 0; i < project.m_fileList->size(); i++){
        Model::File *p = new Model::File(*project.m_fileList->at(i));
        m_fileList->push_back(p);
    }

    m_attachments = new QList<Model::Attachment*>();
    for(int i = 0; i < project.m_attachments->size(); i++){
        Model::Attachment *p = new Model::Attachment(*project.m_attachments->at(i));
        m_attachments->push_back(p);
    }

    m_informations = new QMap<QString, QString>;
    QMap<QString, QString>::const_iterator i = project.m_informations->constBegin();
     while (i != project.m_informations->constEnd()) {
         m_informations->insert(i.key(), i.value());
         ++i;
     }
}

void Model::Project::load() {
	throw "Not yet implemented";
}

void Model::Project::save() {
	throw "Not yet implemented";
}


void Model::Project::addFileToList(Model::File *file)
{
    if(m_fileList == NULL)
        this->m_fileList = new QList<Model::File*>();

    this->m_fileList->push_back(file);
}

void Model::Project::addInformations(QString key, QString value)
{
    if(m_informations == NULL)
        this->m_informations = new QMap<QString, QString>;

    this->m_informations->insert(key, value);
}

void Model::Project::removeInformations(QString key)
{
    if(this->m_informations->contains(key))
        this->m_informations->remove(key);
}

void Model::Project::addAttachment(Model::Attachment *attachment)
{
    if(m_attachments == NULL)
        this->m_attachments = new QList<Model::Attachment*>();

    this->m_attachments->push_back(attachment);
}

void Model::Project::removeFile(QString filePath)
{
    int i = 0;
    while(i < this->m_fileList->size() && this->m_fileList->at(i)->getFilePath().compare(filePath) !=0 )
        i++;
    if (i < this->m_fileList->size()){
        File *f = m_fileList->at(i);
        this->m_fileList->removeAt(i);
        delete(f);
    }
    else{
        i = 0;
        while(i < this->m_attachments->size() && this->m_attachments->at(i)->filepath().compare(filePath) !=0 )
            i++;

        if (i < this->m_attachments->size()){
            Attachment *a = m_attachments->at(i);
            this->m_attachments->removeAt(i);
            delete(a);
        }
    }
}

QString Model::Project::name() const
{
    return m_name;
}

void Model::Project::setName(const QString &name)
{
    m_name = name;
}

QList<Model::File *> *Model::Project::fileList() const
{
    return m_fileList;
}

QMap<QString, QString> *Model::Project::informations() const
{
    return m_informations;
}

bool Model::Project::createMagnet() const
{
    return m_createMagnet;
}

void Model::Project::setCreateMagnet(bool createMagnet)
{
    m_createMagnet = createMagnet;
}

QList<Model::Attachment *> *Model::Project::attachments() const
{
    return m_attachments;
}

QString Model::Project::xmlFilePath() const
{
    return m_xmlFilePath;
}

void Model::Project::setXmlFilePath(const QString &xmlFilePath)
{
    m_xmlFilePath = xmlFilePath;
}

QString Model::Project::getTorrentSoftwarePath() const {
    return m_torrentSoftwarePath;
}

void Model::Project::setTorrentSoftwarePath(const QString &torrentSoftwarePath) {
    m_torrentSoftwarePath = torrentSoftwarePath;
}

QString Model::Project::generateInformationToXML()
{
    if(m_informations != NULL){
        this->m_xmlFilePath = qApp->applicationDirPath() + QDir::separator() + "infos.xml";
        QFile file(this->m_xmlFilePath);
        if (!file.open(QIODevice::WriteOnly)){
            return "";
        }
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument("1.0");
        writer.writeStartElement("Informations");

        QMap<QString, QString>::const_iterator i = m_informations->constBegin();
         while (i != m_informations->constEnd()) {
             writer.writeTextElement(i.key(), i.value());
             ++i;
         }

        writer.writeEndElement();
        writer.writeEndDocument();

        file.close();
        return this->m_xmlFilePath;
    }
    return "";

}

QStringList *Model::Project::getMergeCommandLine()
{
    QStringList *arguments = new QStringList();
    *arguments << "-o" << m_name;

    foreach (Model::File *f, *(fileList())){
        foreach(Model::StreamWrapper *sw, *(f->getStreamWrappers())){
            if(sw->getRelevantStream()->isDefault())
                *arguments << "--default-track" << sw->getRelevantStream()->getUID();

            if(sw->oldStream()->name() !=""){
                *arguments << "--track-name" << sw->oldStream()->name();
            }
            if(sw->oldStream()->delay() !=""){
                QString a =sw->oldStream()->getUID();
                QString b = ":";
                QString c = sw->oldStream()->delay();
                QString sync = a+b+c;
                *arguments << "--sync" << sync;
            }
        }
        *arguments <<f->getFilePath();
    }

    foreach (Model::Attachment *a, *(attachments())){
        *arguments << "--attach-file" << a->filepath();
    }

    *arguments <<"--attach-file"<< this->generateInformationToXML();

    qDebug() << *arguments;
    return arguments;
}

int Model::Project::nbVideo() const
{
    int cpt = 0;
    foreach(Model::File *f , *(this->m_fileList)){
        foreach( Model::StreamWrapper *sw, *(f->getDatas())){
            Model::Video* v = dynamic_cast<Model::Video*>(sw->oldStream());
            if(v !=0)
                cpt++;
        }
    }
    return cpt;
}

int Model::Project::nbAudio() const
{
    int cpt = 0;
    foreach(Model::File *f , *(this->m_fileList)){
        foreach( Model::StreamWrapper *sw, *(f->getDatas())){
            Model::Audio* a = dynamic_cast<Model::Audio*>(sw->oldStream());
            if(a !=0)
                cpt++;
        }
    }
    return cpt;
}

int Model::Project::nbSub() const
{
    int cpt = 0;
    foreach(Model::File *f , *(this->m_fileList)){
        foreach( Model::StreamWrapper *sw, *(f->getDatas())){
            Model::Subtitle* s = dynamic_cast<Model::Subtitle*>(sw->oldStream());
            if(s !=0)
                cpt++;
        }
    }
    return cpt;
}

QString Model::Project::depot() const
{
    return m_depot;
}

void Model::Project::setDepot(const QString &depot)
{
    m_depot = depot;
}

QString Model::Project::userKey() const
{
    return m_userKey;
}

void Model::Project::setUserKey(const QString &userKey)
{
    m_userKey = userKey;
}
