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

#include <QDomDocument>
#include <QTemporaryDir>
#include <exception>
using namespace std;

#include "src/Model/File.h"
#include "src/Model/StreamWrapper.h"

#include "Subtitle.h"





QList<Model::StreamWrapper *> *Model::File::getDatas() const
{
    return m_datas;
}

Model::File::File() : m_datas(NULL) {
    m_datas = new QList<StreamWrapper*>();
}

Model::File::File(QString filePath, QString info) : m_datas(NULL) {
    this->m_filePath = filePath;
    QStringList path= filePath.split("/");
    QString finalOutput;
    for(int i = 0 ; i < path.size() ; i++){
        if(i== path.size()-1){
            finalOutput += "transcoded_";
            finalOutput += path.at(i);
        }else{
            finalOutput += path.at(i) + "/";
        }
    }

    this->m_outFilePath = finalOutput;

    QStringList name = filePath.split("/");

    this->m_name = name.at(name.length()-1);
    this->m_datas = new QList<StreamWrapper*>();

    QDomDocument doc;
    doc.setContent(info);
    if(!doc.isNull()){
        QDomElement root = doc.documentElement();
        if(!root.isNull()){
            QDomNodeList streams = root.elementsByTagName("stream");
            int cptv = 0;
            int cpta = 0;
            int cpts = 0;
            for (int i=0;i<streams.count();i++){
                qDebug() << "//-----------------------STREAM------------------------//";
                //-----------------------STREAM------------------------//
                QDomNode stream = streams.item(i);
                QDomNamedNodeMap tab = stream.attributes();

                //-----------------------TYPE------------------------//
                QDomNode nodeCodecType = tab.namedItem("codec_type");
                QString type = nodeCodecType.nodeValue();
                Stream *s;
                bool isimgmjpeg = false;
                switch (Model::Stream::getEnumValue(type)){
                    case Model::Stream::VIDEO:
                            if(tab.namedItem("avg_frame_rate").nodeValue().compare("0/0") !=0){
                                s = new Video(stream, cptv);
                                cptv++;
                            }else
                                isimgmjpeg = true;
                            break;
                    case Model::Stream::AUDIO:
                            s = new Audio(stream, cpta);
                            cpta++;
                            break;
                    case Model::Stream::SUBTITLE:
                            s = new Subtitle(stream, cpts);
                            cpts++;
                            break;
                }
                if(Model::Stream::getEnumValue(type) != Model::Stream::ATTACHMENT && !isimgmjpeg){
                    StreamWrapper* theData;
                    theData= new StreamWrapper();
                    theData->setOldStream(s);
                    this->m_datas->push_back(theData);
                }
            }
        }
    }
}

Model::File::File(const File& f) {
    m_name = f.m_name;
    m_filePath = f.m_filePath;
    m_outFilePath = f.m_outFilePath;

    m_datas = new QList<Model::StreamWrapper*>();
    for(int i = 0; i < f.m_datas->size(); i++){
        Model::StreamWrapper *p = new Model::StreamWrapper(*(f.m_datas->at(i)));
        m_datas->push_back(p);
    }
}

Model::File& Model::File::operator=(const File& f) {
    if ( this != &f ) {
        m_name = f.m_name;
        m_filePath = f.m_filePath;
        m_datas = f.m_datas;
        m_outFilePath = f.m_outFilePath;
    }
    return *this;
}

Model::File::~File() {
    if(this->m_datas != NULL)
        delete this->m_datas;
}

QList<Model::StreamWrapper*>* Model::File::getStreamWrappers() {
    return m_datas;
}

QStringList *Model::File::getCommandLine()
{
    QStringList *stringList;
    stringList = new QStringList();
    *stringList << "-i" << this->m_filePath;
    foreach (StreamWrapper *sW, *getStreamWrappers()) {
        (*stringList) << *(sW->generateCommandLine());
    }
    if(this->getStreamWrappers()->size()==1){
        Stream *stream = this->getStreamWrappers()->at(0)->getRelevantStream();
        if(stream->getType() == Model::Stream::AUDIO){
            QStringList filename = this->m_outFilePath.split(".");
            QString newFilename = "";
            if(filename.size()>1){
                for(int i =0 ; i <filename.size()-1;i++){
                    newFilename.append(filename.at(i));
                }
                QString codec = stream->getParameters()->value(Stream::CODEC_NAME)->value();
                this->m_outFilePath = newFilename.append("."+codec);
                (*stringList) << this->m_outFilePath;
                return stringList;
            }
        }
    }
    (*stringList) <<this->m_outFilePath;
    return stringList;
}

QString Model::File::getName() {
    return this->m_name;
}

QString Model::File::getOriginalFilePath(){
    return this->m_filePath;
}

void Model::File::initMetaType()
{
    qRegisterMetaTypeStreamOperators<Model::File>("Model::File");
    qMetaTypeId<Model::File>();
}

QString Model::File::getFilePath()
{
    if(hasToBeTranscoded()){
       return this->m_outFilePath;
    }
    return this->m_filePath;
}

bool Model::File::hasToBeTranscoded(){
    foreach (StreamWrapper *data, *getStreamWrappers()) {
        if(data->hasToBeTranscoded()){
            return true;
        }
    }
    return false;
}






QDataStream &Model::operator <<(QDataStream &out, const Model::File &valeur)
{
    out << valeur.m_name;
    out << valeur.m_filePath;
    out << valeur.m_outFilePath;
    out << valeur.m_datas->size();
    foreach (StreamWrapper *sW, *(valeur.m_datas)) {
        out << *sW;
    }
    return out;
}


QDataStream &Model::operator >>(QDataStream &in, Model::File &valeur)
{
    in >> valeur.m_name;
    in >> valeur.m_filePath;
    in >> valeur.m_outFilePath;
    int size;
    in >> size;

    for(int i = 0 ; i < size; i++){
        StreamWrapper *sw = new StreamWrapper;
        in >> *sw;
        valeur.m_datas->push_back(sw);
    }
    return in;
}
