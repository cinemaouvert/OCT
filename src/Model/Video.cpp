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
    QDomNamedNodeMap tab = stream.attributes();
    //-----------------------CODEC-NAME------------------------//
    QDomNode nodeCodecName = tab.namedItem(Model::Stream::CODEC_NAME);
    QString codecName = nodeCodecName.nodeValue();
    //-----------------------LANGUAGE------------------------//
    QDomNodeList tagList = stream.toElement().elementsByTagName("tag");

    QString tagKey ="";
    int i = 0;
    while(tagKey != Model::Stream::LANGUAGE && i<tagList.count()){
        tagKey = tagList.at(i).attributes().namedItem("key").nodeValue();
        i++;
    }
    QString language = "";
    if(tagKey == Model::Stream::LANGUAGE)
        language = tagList.at(i-1).attributes().namedItem("value").nodeValue();
    //-----------------------IS-DEFAULT------------------------//
    QDomNode disposition = stream.toElement().elementsByTagName("disposition").item(0);
    QString isDefault = disposition.attributes().namedItem(Model::Stream::DEFAULT).nodeValue();
    //-----------------------RESOLUTION------------------------//
    QDomNode nodeWidth = tab.namedItem("width");
    QString width = nodeWidth.nodeValue();

    QDomNode nodeHeight = tab.namedItem("height");
    QString height = nodeHeight.nodeValue();

    QString resolution = width + "x" + height;
    //-----------------------FRAME-RATE------------------------//   //!\\  A CONVERTIR
    QDomNode nodeFrameRate = tab.namedItem(Model::Stream::VIDEO_FRAME_RATE);
    QString frameRate = Utils::convertFract(nodeFrameRate.nodeValue());

    //-----------------------BPS------------------------//   //!\\  A CONVERTIR
    QDomNodeList nodeListTag = stream.toElement().elementsByTagName("tag");
    QString bps;
    if(! nodeListTag.isEmpty()){
        int i = 0;
        bool bpsFinded = false;
        while(!bpsFinded && i< nodeListTag.size()){
            QDomNode node = nodeListTag.item(i);
                if(node.attributes().namedItem("key").nodeValue() == "BPS"){
                    bps = node.attributes().namedItem("value").nodeValue();
                    bpsFinded = true;
                }
            i++;
        }
    }
    //-----------------------TITLE------------------------//
    QString titre ="";
    if(! nodeListTag.isEmpty()){
        int i = 0;
        bool titreFinded = false;
        while(!titreFinded && i< nodeListTag.size()){
            QDomNode node = nodeListTag.item(i);
                if(node.attributes().namedItem("key").nodeValue() == "title"){
                    titre = node.attributes().namedItem("value").nodeValue();
                    titreFinded = true;
                }
            i++;
        }
    }
    //-----------------------VIDEO-BUILD------------------------//
    this->m_uID = QString::number(uid);
    this->m_name = titre;
    this->m_default = false;
    this->m_additionalCommand = QString();
    this->m_parameters = new QMap<QString,Parameter*>();

    Parameter *pCodecName = Video::getStaticParameter(Model::Stream::CODEC_NAME);
    pCodecName->setValue(codecName);
    this->setParameter(Model::Stream::CODEC_NAME,pCodecName);

    if(language != ""){
        Parameter *pLanguage = Video::getStaticParameter(Model::Stream::LANGUAGE);
        pLanguage->setValue(language);
        this->setParameter(Model::Stream::LANGUAGE,pLanguage);
    }

    Parameter *pDefault = Video::getStaticParameter(Model::Stream::DEFAULT);
    pDefault->setValue(isDefault);
    this->setParameter(Model::Stream::DEFAULT,pDefault);
    if(isDefault == "1")
        this->m_default = true;


    Parameter *pResolution = Video::getStaticParameter(Model::Stream::RESOLUTION);
    pResolution->setValue(resolution);
    this->setParameter(Model::Stream::RESOLUTION,pResolution);

    Parameter *pFrameRate = Video::getStaticParameter(Model::Stream::VIDEO_FRAME_RATE);
    pFrameRate->setValue(frameRate);
    this->setParameter(Model::Stream::VIDEO_FRAME_RATE,pFrameRate);

    if(!bps.isNull()){
        Parameter *pBps = Video::getStaticParameter(Model::Stream::VIDEO_AVG_BIT_RATE);
        pBps->setValue(bps);
        this->setParameter(Model::Stream::VIDEO_AVG_BIT_RATE,pBps);

    }

}

Model::Video::Video(QString uid){
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_uID = uid;
    this->m_default = false;
}

Model::Video::Video(const Model::Video & copy){
    this->m_uID = copy.m_uID;
    this->m_additionalCommand = QString(copy.m_additionalCommand);
    this->m_default = copy.m_default;

    m_parameters = new QMap<QString,Parameter*>;
    QMap<QString,Parameter*>::const_iterator i = copy.m_parameters->constBegin();
     while (i != copy.m_parameters->constEnd()) {
         m_parameters->insert(i.key(), new Model::Parameter(*(i.value())));
         ++i;
     }
}

Model::Video &Model::Video::Video::operator=(const Model::Video &o)
{
    if(this != &o){
        this->m_uID = o.m_uID;
        this->m_default = o.m_default;
        this->m_additionalCommand = o.m_additionalCommand;
        m_parameters = new QMap<QString,Parameter*>;
        QMap<QString,Parameter*>::const_iterator i = o.m_parameters->constBegin();
         while (i != o.m_parameters->constEnd()) {
             m_parameters->insert(i.key(), new Model::Parameter(*(i.value())));
             ++i;
         }
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
    m_staticParameters.insert(Model::Stream::CODEC_NAME,codecNameParam);

    Parameter *language = new Parameter("-metadata:s:v:%1","This is the language of the stream","language=%1");
    m_staticParameters.insert(Model::Stream::LANGUAGE,language);

    Parameter *isDefault = new Parameter("-metadata:s:v:%1","This indicates if the stream is tagged as the default one","default-flag=%1");
    m_staticParameters.insert(Model::Stream::DEFAULT,isDefault);

    Parameter *resolution = new Parameter("-vf","This is the resolution of the video stream (AAAxBBB)","scale=%1");
    m_staticParameters.insert(Model::Stream::RESOLUTION,resolution);

    Parameter *forceAspect = new Parameter("","Enable decreasing or increasing output video width or height if necessary to keep the original aspect ratio. Possible values: disable,decrease,increase","force_original_aspect_ratio=%1");
    m_staticParameters.insert(Model::Stream::VIDEO_FORCE_ASPECT,forceAspect);

    Parameter *scale = new Parameter("-aspect","","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_SCALE,scale);

    Parameter *frameRate = new Parameter("-r","This is the frame rate (in frame by second)","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_FRAME_RATE,frameRate);

    Parameter *averageBitRate= new Parameter("","This is the average bit rate","-b:v %1 -bufsize %1");
    m_staticParameters.insert(Model::Stream::VIDEO_AVG_BIT_RATE,averageBitRate);

    Parameter *filter= new Parameter("-filter:v","This is the video filter can be (yadif for deinterlace, ))","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_DEINTERLACE,filter);

    Parameter *startPoint= new Parameter("-ss","Start point of the video","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_START_TIME,startPoint);

    Parameter *endPoint= new Parameter("-ss","End point of the video","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_STOP_POINT,endPoint);

    Parameter *crop= new Parameter("-filter:v","Crop the video (w:h:x:y)","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_CROP,crop);

    Parameter *preset= new Parameter("-preset","Encoding speed and compression radio for h264","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_H264_PRESET,preset);

    Parameter *h264_quality= new Parameter("-crf","CRF Value for H264 (0->51) 0 is lossless","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_H264_QUALITY,h264_quality);

    Parameter *h264_profile= new Parameter("-profile:v","Advanced features for h264","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_H264_BASELINE,h264_profile);

    Parameter *h264_level= new Parameter("-level","Advanced features for h264","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_H264_LEVEL,h264_level);

    Parameter *h264_tune= new Parameter("-tune","Advanced features for h264","%1");
    m_staticParameters.insert(Model::Stream::VIDEO_H264_TUNE,h264_tune);

    Parameter *extraCmd= new Parameter("","Extra command from the user","%1");
    m_staticParameters.insert(Model::Stream::EXTRA_CMD,extraCmd);


}

void Model::Video::initMetaType()
{
    qRegisterMetaTypeStreamOperators<Model::Video>("Model::Video");
    qMetaTypeId<Model::Video>();
}

int Model::Video::getType() const
{
    return Stream::VIDEO;
}


QDataStream &Model::operator <<(QDataStream &out, const Model::Video &valeur)
{
    out << valeur.m_uID;
    out << valeur.m_default;
    out << valeur.m_delay;
    out << valeur.m_name;
    out << valeur.m_additionalCommand;

    out << valeur.m_parameters->size();
    foreach (QString key, valeur.m_parameters->keys()) {
        out << key;
        out << *(valeur.m_parameters->value(key));
    }
    return out;
}


QDataStream &Model::operator >>(QDataStream &in, Model::Video &valeur)
{
    in >> valeur.m_uID;
    in >> valeur.m_default;
    in >> valeur.m_delay;
    in >> valeur.m_name;
    in >> valeur.m_additionalCommand;

    int parametersSize;
    in >> parametersSize;
    for(int i = 0; i < parametersSize ; i++){
        QString key;
        Parameter *param = new Parameter();
        in >> key;
        in >> *param;
        valeur.m_parameters->insert(key, param);
    }
    return in;
}
