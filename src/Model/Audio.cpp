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

#include "src/Model/Audio.h"
#include "src/Model/Stream.h"
#include "src/Controller/Utils.h"

#include <QDebug>
#include <QSettings>

QMap<QString, Model::Parameter *> Model::Audio::m_staticParameters;
Model::Audio::Audio() {
    m_uID = "";
    m_delay = "";
    m_name = "";
    m_default = false;
    this->m_parameters = new QMap<QString,Parameter*>();
}

Model::Audio::Audio(QDomNode stream, int uid)
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
    //-----------------------SAMPLE-RATE------------------------//
    QDomNode nodeSampleRate = tab.namedItem(Model::Stream::AUDIO_SAMPLE_RATE);
    QString SampleRate = nodeSampleRate.nodeValue();
    //-----------------------CHANNELS------------------------//
    QDomNode nodeChannels = tab.namedItem(Model::Stream::AUDIO_CHANNELS);
    QString channels = nodeChannels.nodeValue();
    //-----------------------RESOLUTION------------------------//
    QDomNode nodeBitRate = tab.namedItem("bit_rate");
    QString bitRate = Utils::bpsToKbps(nodeBitRate.nodeValue());
    //-----------------------IS-DEFAULT------------------------//
    QDomNode disposition = stream.toElement().elementsByTagName("disposition").item(0);
    QString isDefault = disposition.attributes().namedItem(Model::Stream::DEFAULT).nodeValue();
    //-----------------------TITLE------------------------//
    QString titre ="";
    QDomNodeList nodeListTag = stream.toElement().elementsByTagName("tag");
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
    //-----------------------AUDIO-BUILD------------------------//
    this->m_uID = QString::number(uid);
    this->m_name = titre;
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_default = false;

    if(isDefault == "1")
        this->m_default = true;

    Parameter *pCodecName = Audio::getStaticParameter(Model::Stream::CODEC_NAME);
    pCodecName->setValue(codecName);
    this->setParameter(Model::Stream::CODEC_NAME,pCodecName);

    if(language != ""){
        Parameter *pLanguage = Audio::getStaticParameter(Model::Stream::LANGUAGE);
        pLanguage->setValue(language);
        this->setParameter(Model::Stream::LANGUAGE,pLanguage);
    }

    Parameter *pSampleRate = Audio::getStaticParameter(Model::Stream::AUDIO_SAMPLE_RATE);
    pSampleRate->setValue(SampleRate);
    this->setParameter(Model::Stream::AUDIO_SAMPLE_RATE,pSampleRate);

    Parameter *pChannels = Audio::getStaticParameter(Model::Stream::AUDIO_CHANNELS);
    pChannels->setValue(channels);
    this->setParameter(Model::Stream::AUDIO_CHANNELS,pChannels);

    Parameter *pBitRate = Audio::getStaticParameter(Model::Stream::RESOLUTION);
    pBitRate->setValue(bitRate);
    this->setParameter(Model::Stream::RESOLUTION,pBitRate);
}

Model::Audio::Audio(QString uID) {
    m_uID = uID;
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_default = false;
    m_delay = "";
    m_name = "";
}

Model::Audio::Audio(const Audio& a) {
    m_uID = a.m_uID;
    QMap<QString,Parameter*> *param(a.m_parameters) ;
    this->m_parameters = param;
    this->m_default = a.m_default;
    m_delay = a.m_delay;
    m_name = a.m_name;
}

Model::Audio& Model::Audio::operator=(const Audio& a) {
    if ( this != &a ) {
        m_uID = a.m_uID;
        QMap<QString,Parameter*> *param(a.m_parameters) ;
        this->m_parameters = param;
        this->m_default = a.m_default;
        m_delay = a.m_delay;
        m_name = a.m_name;
    }
    return *this;
}

Model::Audio::~Audio() {
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

Model::Parameter *Model::Audio::getStaticParameter(QString key)
{
    Parameter *param = new Parameter(*(Audio::m_staticParameters.value(key)));
    return param;
}

void Model::Audio::initStaticParameters()
{
    Parameter *codecNameParam = new Parameter("-acodec","This is the codec of the audio stream","%1");
    m_staticParameters.insert(Model::Stream::CODEC_NAME,codecNameParam);

    Parameter *language = new Parameter("-metadata:s:a:%1","This is the language of the audio stream","language=%1");
    m_staticParameters.insert(Model::Stream::LANGUAGE,language);

    Parameter *delay = new Parameter("-itsoffset","This is the delay of the audio stream","%1");
    m_staticParameters.insert(Model::Stream::AUDIO_DELAY,delay);

    Parameter *sampleRate = new Parameter("-ar","This is the sample rate of the audio stream","%1");
    m_staticParameters.insert(Model::Stream::AUDIO_SAMPLE_RATE,sampleRate);

    Parameter *channels = new Parameter("-ac","This is the channels of the audio stream","%1");
    m_staticParameters.insert(Model::Stream::AUDIO_CHANNELS,channels);

    Parameter *resolution = new Parameter("-b:a","This is the resolution of the audio stream","%1k");
    m_staticParameters.insert(Model::Stream::RESOLUTION,resolution);
}

void Model::Audio::initMetaType()
{
    qRegisterMetaTypeStreamOperators<Model::Audio>("Model::Audio");
    qMetaTypeId<Model::Audio>();
}

int Model::Audio::getType() const
{
    return Stream::AUDIO;
}

QDataStream &Model::operator >>(QDataStream &in, Model::Audio &valeur)
{
    in >> valeur.m_uID;
    in >> valeur.m_default;

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
QDataStream &Model::operator <<(QDataStream &out, const Model::Audio& valeur)
{
    out << valeur.m_uID;
    out << valeur.m_default;

    out << valeur.m_parameters->size();
    foreach (QString key, valeur.m_parameters->keys()) {
        out << key;
        out << *(valeur.m_parameters->value(key));
    }
    return out;
}
QDataStream &Model::operator <<(QDataStream &out, const Model::Audio* valeur)
{
    out << *valeur;
    return out;
}
