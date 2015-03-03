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
#include <QDebug>

// ========================================================================== //
// == Constructors and destructor =========================================== //
// ========================================================================== //


Model::Project::Project() : m_attachments (NULL),m_informations(NULL), m_fileList(NULL) {
    this->m_attachments = new QList<Model::Attachment*>();
    this->m_informations =  new QMap<QString, QString>;
    this->m_fileList = new QList<Model::File*>();
    this->m_name = "";
    this->m_sendInfo = false;
}

Model::Project::~Project() {
    if(this->m_attachments)     delete this->m_attachments;
    if(this->m_fileList)        delete this->m_fileList;
    if(this->m_informations)    delete this->m_informations;
}

// ========================================================================== //
// == Copy constructor ====================================================== //
// ========================================================================== //
Model::Project::Project(const Model::Project &project) {
    m_name = project.m_name;
    m_xmlFilePath = project.m_xmlFilePath;
    m_createMagnet = project.m_createMagnet;
    m_sendInfo = project.m_sendInfo;

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

// ========================================================================== //
// == Affectation operator ================================================== //
// ========================================================================== //
Model::Project &Model::Project::operator=(const Model::Project &project) {
    if (this != &project) {
        m_name = project.m_name;
        m_xmlFilePath = project.m_xmlFilePath;
        m_createMagnet = project.m_createMagnet;
        m_affiche = project.m_affiche;
        m_capture = project.m_capture;
        m_depot = project.m_depot;
        m_userKey = project.m_userKey;
        m_sendInfo = project.m_sendInfo;
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
        for(int i = 0; i < project.m_fileList->size(); i++) {
            Model::File *p = new Model::File(*project.m_fileList->at(i));
            m_fileList->push_back(p);
        }

        m_attachments = new QList<Model::Attachment*>();
        for(int i = 0; i < project.m_attachments->size(); i++) {
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

// ========================================================================== //
// == Accessor and mutator methods ========================================== //
// ========================================================================== //
QString Model::Project::name() const {
    return m_name;
}

void Model::Project::setName(const QString &name) {
    m_name = name;
}

QList<Model::File *> *Model::Project::fileList() const {
    return m_fileList;
}

QMap<QString, QString> *Model::Project::informations() const {
    return m_informations;
}

bool Model::Project::createMagnet() const {
    return m_createMagnet;
}

void Model::Project::setCreateMagnet(bool createMagnet) {
    m_createMagnet = createMagnet;
}

QList<Model::Attachment *> *Model::Project::attachments() const {
    return m_attachments;
}

QString Model::Project::xmlFilePath() const {
    return m_xmlFilePath;
}

void Model::Project::setXmlFilePath(const QString &xmlFilePath) {
    m_xmlFilePath = xmlFilePath;
}

QString Model::Project::getTorrentSoftwarePath() const {
    return m_torrentSoftwarePath;
}

void Model::Project::setTorrentSoftwarePath(const QString &torrentSoftwarePath) {
    m_torrentSoftwarePath = torrentSoftwarePath;
}

// ========================================================================== //
// == Class methods ========================================================= //
// ========================================================================== //
void Model::Project::load() {
	throw "Not yet implemented";
}

void Model::Project::save() {
	throw "Not yet implemented";
}

void Model::Project::addFileToList(Model::File *file) {
    if(m_fileList == NULL)
        this->m_fileList = new QList<Model::File*>();

    this->m_fileList->push_back(file);
}

void Model::Project::addInformations(QString key, QString value) {
    if(m_informations == NULL)
        this->m_informations = new QMap<QString, QString>;

    this->m_informations->insert(key, value);
}

void Model::Project::removeInformations(QString key) {
    if(this->m_informations->contains(key))
        this->m_informations->remove(key);
}

void Model::Project::addAttachment(Model::Attachment *attachment) {
    if(m_attachments == NULL)
        this->m_attachments = new QList<Model::Attachment*>();

    this->m_attachments->push_back(attachment);
}

void Model::Project::removeFile(QString filePath) {
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

QString Model::Project::generateInformationToXML() {
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

QStringList *Model::Project::getMergeCommandLine() {
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
    QFile::copy(this->m_affiche,"affiche.png");
    QFile::copy(this->m_capture,"capture.png");

    foreach (Model::Attachment *a, *(attachments())){
        if(a->filepath().compare(this->m_affiche) == 0){
            *arguments << "--attach-file" << "affiche.png";
        }else if(a->filepath().compare(this->m_capture) == 0){
            *arguments << "--attach-file" << "capture.png";
       }else
            *arguments << "--attach-file" << a->filepath();
    }

    *arguments <<"--attach-file"<< this->generateInformationToXML();

    qDebug() << "Merge command : " << *arguments;
    return arguments;
}

int Model::Project::nbVideo() const {
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

int Model::Project::nbAudio() const {
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

int Model::Project::nbSub() const {
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

QString Model::Project::depot() const {
    return m_depot;
}

void Model::Project::setDepot(const QString &depot) {
    m_depot = depot;
}

QString Model::Project::userKey() const {
    return m_userKey;
}

void Model::Project::setUserKey(const QString &userKey) {
    m_userKey = userKey;
}

void Model::Project::initMetaType() {
    qRegisterMetaTypeStreamOperators<Model::Project>("Model::Project");
    qMetaTypeId<Model::Project>();
}

QDataStream &Model::operator <<(QDataStream &out, const Model::Project &valeur) {
    out << valeur.m_depot;
    out << valeur.m_createMagnet;
    out << valeur.m_name;
    out << valeur.m_torrentSoftwarePath;
    out << valeur.m_userKey;
    out << valeur.m_xmlFilePath;

    out << valeur.m_attachments->size();
    foreach (Attachment *a, *(valeur.m_attachments)) {
        out << *a;
    }

    out << valeur.m_fileList->size();
    foreach (File *f, *(valeur.m_fileList)) {
        out << *f;
    }

    out << valeur.m_informations->size();
    foreach (QString key, valeur.m_informations->keys()) {
        out << key;
        out << valeur.m_informations->value(key);
    }
    return out;
}

QDataStream &Model::operator >>(QDataStream &in, Model::Project &valeur) {
    in >> valeur.m_depot;
    in >> valeur.m_createMagnet;
    in >> valeur.m_name;
    in >> valeur.m_torrentSoftwarePath;
    in >> valeur.m_userKey;
    in >> valeur.m_xmlFilePath;

    int sizeAttachments;
    in >> sizeAttachments;

    for(int i=0 ; i<sizeAttachments ; i++){
        Attachment *a = new Attachment;
        in >> *a;
        valeur.m_attachments->push_back(a);
    }

    int sizeFiles;
    in >> sizeFiles;
    for(int i=0 ; i<sizeFiles ; i++){
        File *f = new File;
        in >> *f;
        valeur.m_fileList->push_back(f);
    }

    int sizeInformation;
    in >> sizeInformation;

    for(int i = 0; i < sizeInformation ; i++){
        QString key;
        QString value;
        in >> key;
        in >> value;
        valeur.m_informations->insert(key, value);
    }
    return in;
}

QString Model::Project::capture() const {
    return m_capture;
}

void Model::Project::setCapture(const QString &capture) {
    m_capture = capture;
}

QString Model::Project::affiche() const {
    return m_affiche;
}

void Model::Project::setAffiche(const QString &affiche) {
    m_affiche = affiche;
}

bool Model::Project::sendInfo() const
{
    return m_sendInfo;
}

void Model::Project::setSendInfo(bool sendInfo)
{
    m_sendInfo = sendInfo;
}


