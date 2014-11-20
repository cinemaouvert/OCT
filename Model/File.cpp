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
#include "Model/Data.h"




Model::File::File() {}

Model::File::File(QString filePath, QString info) {
    m_filePath = filePath;
    m_name = filePath;

    QDomDocument doc;
    doc.setContent(info);
    if(!doc.isNull()){
        QDomElement root = doc.documentElement();
        if(!root.isNull()){
            QDomNodeList streams = root.elementsByTagName("stream");
            for (int i=0;i<streams.count();i++){
                //-----------------------STREAM------------------------//
                QDomNode stream = streams.item(i);
                QDomNamedNodeMap tab = stream.attributes();

                //-----------------------TYPE------------------------//
                QDomNode nodeCodecType = tab.namedItem("codec_type");
                QString type = nodeCodecType.nodeValue();
                if(type == "video"){
                  Video *v = new Video(stream);
                  foreach (QString s, *(v->getCommand())) {
                        qDebug() <<"TEST : " + s;
                  }

                }
                if(type == "audio"){
                    qDebug() << "audio";

                }
                if(type == "subtitle"){
                    qDebug() << "sous-titre";
                }
                if(type == "attachment"){
                    qDebug() << "attachment";
                }

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
    }
    return *this;
}

Model::File::~File() {}

QList<Model::Data*> Model::File::getDatas() {
	throw "Not yet implemented";
}

QString Model::File::getName() {
	return this->m_name;
}

ostream& Model::File::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::File::operator << (istream& o){
    throw "Not yet implemented";
}
