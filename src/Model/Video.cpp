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
using namespace std;

#include "src/Model/Video.h"
#include "src/Model/Stream.h"
#include "src/Controller/Utils.h"

#include <QDebug>
#include <QSettings>


QMap<QString, Model::Parameter *> Model::Video::m_staticParameters;
Model::Video::Video(){
    m_default = false;
    this->m_parameters = new QMap<QString,Parameter*>();

}

Model::Video::Video(QDomNode stream, int uid)
{
    qDebug() << "video";
    QDomNamedNodeMap tab = stream.attributes();
    //-----------------------CODEC-NAME------------------------//
    QDomNode nodeCodecName = tab.namedItem("codec_name");
    QString codecName = nodeCodecName.nodeValue();
    qDebug() << codecName;
    //-----------------------LANGUAGE------------------------//
    QDomNodeList tagList = stream.toElement().elementsByTagName("tag");
    qDebug() << tagList.count();

    QString tagKey ="";
    int i = 0;
    while(tagKey != "language" && i<tagList.count()){
        tagKey = tagList.at(i).attributes().namedItem("key").nodeValue();
        i++;
    }
    QString language = "";
    if(tagKey == "language")
        language = tagList.at(i-1).attributes().namedItem("value").nodeValue();
    //-----------------------IS-DEFAULT------------------------//
    QDomNode disposition = stream.toElement().elementsByTagName("disposition").item(0);
    QString isDefault = disposition.attributes().namedItem("default").nodeValue();
    qDebug() << isDefault;
    //-----------------------RESOLUTION------------------------//
    QDomNode nodeWidth = tab.namedItem("width");
    QString width = nodeWidth.nodeValue();
    qDebug() << width;

    QDomNode nodeHeight = tab.namedItem("height");
    QString height = nodeHeight.nodeValue();
    qDebug() << height;

    QString resolution = width + "x" + height;
    qDebug() << resolution;
    //-----------------------FRAME-RATE------------------------//   //!\\  A CONVERTIR
    QDomNode nodeFrameRate = tab.namedItem("r_frame_rate");
    QString frameRate = Utils::convertFract(nodeFrameRate.nodeValue());
    qDebug() << frameRate;

    //-----------------------VIDEO-BUILD------------------------//
    this->m_uID = QString::number(uid);
    this->m_default = false;
    this->m_additionalCommand = QString();
    this->m_parameters = new QMap<QString,Parameter*>();

    Parameter *pCodecName = Video::getStaticParameter("codec_name");
    pCodecName->setValue(codecName);
    this->setParameter("codec_name",pCodecName);

    if(language != ""){
        Parameter *pLanguage = Video::getStaticParameter("language");
        pLanguage->setValue(language);
        this->setParameter("language",pLanguage);
    }

    Parameter *pDefault = Video::getStaticParameter("default");
    pDefault->setValue(isDefault);
    this->setParameter("default",pDefault);
    if(isDefault == "1")
        this->m_default = true;


    Parameter *pResolution = Video::getStaticParameter("resolution");
    pResolution->setValue(resolution);
    this->setParameter("resolution",pResolution);

    Parameter *pFrameRate = Video::getStaticParameter("r_frame_rate");
    pFrameRate->setValue(frameRate);
    this->setParameter("r_frame_rate",pFrameRate);

}

Model::Video::Video(QString uid){
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_uID = uid;
    this->m_default = false;
}

Model::Video::Video(const Model::Video & copy){
    this->m_uID = copy.m_uID;
    this->m_additionalCommand = QString(copy.m_additionalCommand);
    this->m_parameters = new QMap<QString,Parameter*>(*(copy.m_parameters));
    this->m_default = copy.m_default;
}

Model::Video &Model::Video::Video::operator=(const Model::Video &o)
{
    if(this != &o){
        this->m_uID = o.m_uID;
        this->m_default = o.m_default;
        this->m_additionalCommand = o.m_additionalCommand;
        QMap<QString,Parameter*> *param(o.m_parameters) ;
        this->m_parameters = param;
    }
    return *this;
}


Model::Video::~Video()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}



Model::Parameter *Model::Video::getStaticParameter(QString key)
{

    Parameter *param = new Parameter(*(Video::m_staticParameters.value(key)));
    return param;
}

void Model::Video::initStaticParameters()
{
    Parameter *codecNameParam = new Parameter("-vcodec","This is the codec of the video stream","%1");
    m_staticParameters.insert("codec_name",codecNameParam);

    Parameter *language = new Parameter("-metadata:s:v:%1","This is the language of the stream","language=%1");
    m_staticParameters.insert("language",language);

    Parameter *isDefault = new Parameter("-metadata:s:v:%1","This indicates if the stream is tagged as the default one","default-flag=%1");
    m_staticParameters.insert("default",isDefault);

    Parameter *resolution = new Parameter("-vf","This is the resolution of the video stream (AAAxBBB)","scale=%1");
    resolution->SetNoSpaceForNext();
    m_staticParameters.insert("resolution",resolution);

    Parameter *forceAspect = new Parameter("","Enable decreasing or increasing output video width or height if necessary to keep the original aspect ratio. Possible values: disable,decrease,increase","force_original_aspect_ratio=%1");
    m_staticParameters.insert("forceAspect",forceAspect);

    Parameter *frameRate = new Parameter("-r","This is the frame rate (in frame by second)","%1");
    m_staticParameters.insert("r_frame_rate",frameRate);

    Parameter *averageBitRate= new Parameter("-b:v %1 -bufsize %1","This is the average bit rate","");
    m_staticParameters.insert("bitRate",averageBitRate);

    Parameter *filter= new Parameter("-filter:v","This is the video filter can be (yadif for deinterlace, ))","%1");
    m_staticParameters.insert("deinterlace",filter);

    Parameter *startPoint= new Parameter("-ss","Start point of the video","%1");
    m_staticParameters.insert("start_pts",startPoint);

    Parameter *endPoint= new Parameter("-ss","End point of the video","%1");
    m_staticParameters.insert("start_pts",endPoint);

    Parameter *crop= new Parameter("-filter:v","Crop the video (w:h:x:y)","%1");
    m_staticParameters.insert("crop",crop);
}

int Model::Video::getType()
{
    return Stream::VIDEO;
}
