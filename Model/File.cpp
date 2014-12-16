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
#include <exception>
using namespace std;

#include "Model/File.h"
#include "Model/StreamWrapper.h"

#include "Subtitle.h"




Model::File::File() {}

Model::File::File(QString filePath, QString info) : m_datas(NULL) {
    m_filePath = filePath;
    m_name = filePath;
    m_datas = new QList<StreamWrapper*>();

    QDomDocument doc;
    doc.setContent(info);
    if(!doc.isNull()){
        QDomElement root = doc.documentElement();
        if(!root.isNull()){
            QDomNodeList streams = root.elementsByTagName("stream");
            for (int i=0;i<streams.count();i++){
                qDebug() << "//-----------------------STREAM------------------------//";
                //-----------------------STREAM------------------------//
                QDomNode stream = streams.item(i);
                QDomNamedNodeMap tab = stream.attributes();

                //-----------------------TYPE------------------------//
                QDomNode nodeCodecType = tab.namedItem("codec_type");
                QString type = nodeCodecType.nodeValue();
                Stream *s;
                switch (Model::Stream::getEnumValue(type)){
                    case Model::Stream::VIDEO:
                            s = new Video(stream);
                            break;
                    case Model::Stream::AUDIO:
                            s = new Audio(stream);
                            break;
                    case Model::Stream::SUBTITLE:
                            s = new Subtitle(stream);
                            break;
                    case Model::Stream::ATTACHMENT:
                            break;
                }

                StreamWrapper* theData;
                theData= new StreamWrapper();

                theData->setOldStream(s);
                this->m_datas->push_back(theData);
            }
        }
    }
}

Model::File::File(const File& f) {
    m_name = f.m_name;
    m_filePath = f.m_filePath;
}

Model::File& Model::File::operator=(const File& f) {
    if ( this != &f ) {
        m_name = f.m_name;
        m_filePath = f.m_filePath;
        m_datas = f.m_datas;
    }
    return *this;
}

Model::File::~File() {
    if(this->m_datas != NULL)
        delete this->m_datas;
}

QList<Model::StreamWrapper*>* Model::File::getDatas() {
    return m_datas;
}

QStringList *Model::File::getCommandLine()
{
    QStringList *stringList;
    stringList = new QStringList();
    *stringList << "-i" << this->m_filePath;
    foreach (StreamWrapper *data, *getDatas()) {
        if(data->hasToBeTranscoded()){
            (*stringList) << *(data->generateCommandLine());
        }
    }
    *stringList << "E:\\M2\\Projet\\Test mkvtoolnix\\test3.mkv";
    return stringList;
}

QString Model::File::getName() {
    return this->m_name;
}




