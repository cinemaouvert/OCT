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
#include "src/Model/Information.h"
#include "Subtitle.h"
#include <QXmlStreamWriter>
#include <QFile>

Model::Project::Project() : m_attachments (NULL),m_informations(NULL), m_fileList(NULL)
{
    this->m_attachments = new QList<Model::Attachment*>();
    this->m_informations = new QList<Model::Information*>();
    this->m_fileList = new QList<Model::File*>();
    this->m_name = "Projet.mkv";
}

Model::Project::~Project()
{
    if(this->m_attachments != NULL)
        delete this->m_attachments;
    if(this->m_fileList != NULL)
        delete this->m_fileList;
    if(this->m_informations != NULL)
        delete this->m_informations;
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

        m_informations = new QList<Model::Information*>();
        for(int i = 0; i < project.m_informations->size(); i++){
            Model::Information *p = new Model::Information(*project.m_informations->at(i));
            m_informations->push_back(p);
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

    m_informations = new QList<Model::Information*>();
    for(int i = 0; i < project.m_informations->size(); i++){
        Model::Information *p = new Model::Information(*project.m_informations->at(i));
        m_informations->push_back(p);
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

void Model::Project::addInformations(Model::Information *information)
{
    if(m_informations == NULL)
        this->m_informations = new QList<Model::Information*>();

    this->m_informations->push_back(information);
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

QList<Model::Information *> *Model::Project::informations() const
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

void Model::Project::generateInformationToXML()
{
    if(m_informations != NULL){
        QFile file("infos.xml"); // TODO : changer emplacement du fichier
        if (!file.open(QIODevice::WriteOnly)){
            return;
        }
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument("1.0");
        writer.writeStartElement("Informations");

        for (int i = 0; i < m_informations->size(); i++) {
            Information *info = m_informations->at(i);
            writer.writeTextElement(info->name(), info->value());
        }

        writer.writeEndElement();
        writer.writeEndDocument();

        file.close();
    }
}

QStringList *Model::Project::getMergeCommandLine()
{
    QStringList *arguments = new QStringList();
   // *arguments << "mkvmerge.exe";
    *arguments << "-o" << m_name;
  //  *arguments <<"--title"<<"TITRE";

    foreach (Model::File *f, *(fileList())){
        foreach(Model::StreamWrapper *sw, *(f->getStreamWrappers())){
            if(sw->oldStream()->isDefault())
                *arguments << "--default-track" << sw->oldStream()->getUID(); //////////////////getNew
        }
        *arguments <<f->getFilePath();
    }

    foreach (Model::Attachment *a, *(attachments())){
        *arguments << "--attach-file" << a->filepath();
    }

    //*arguments <<"--attach-file"<< m_xmlFilePath;

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
