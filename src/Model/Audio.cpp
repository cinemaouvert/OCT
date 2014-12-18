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
    m_default = false;
    this->m_parameters = new QMap<QString,Parameter*>();
}

Model::Audio::Audio(QDomNode stream)
{
    qDebug() << "Audio";
    QDomNamedNodeMap tab = stream.attributes();
    //-----------------------UID------------------------//
    QDomNode uidNode = tab.namedItem("index");
    QString UID = uidNode.nodeValue();
    qDebug() << UID;
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
    //-----------------------SAMPLE-RATE------------------------//
    QDomNode nodeSampleRate = tab.namedItem("sample_rate");
    QString SampleRate = nodeSampleRate.nodeValue();
    qDebug() << SampleRate;
    //-----------------------CHANNELS------------------------//
    QDomNode nodeChannels = tab.namedItem("channels");
    QString channels = nodeChannels.nodeValue();
    qDebug() << channels;
    //-----------------------RESOLUTION------------------------//
    QDomNode nodeBitRate = tab.namedItem("bit_rate");
    QString bitRate = Utils::bpsToKbps(nodeBitRate.nodeValue());
    qDebug() << bitRate;
    //-----------------------IS-DEFAULT------------------------//
    QDomNode disposition = stream.toElement().elementsByTagName("disposition").item(0);
    QString isDefault = disposition.attributes().namedItem("default").nodeValue();
    qDebug() << isDefault;

    //-----------------------AUDIO-BUILD------------------------//
    this->m_uID = UID;
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_default = false;

    if(isDefault == "1")
        this->m_default = true;

    Parameter *pCodecName = Audio::getStaticParameter("codec_name");
    pCodecName->setValue(codecName);
    this->setParameter("codec_name",pCodecName);

    if(language != ""){
        Parameter *pLanguage = Audio::getStaticParameter("language");
        pLanguage->setValue(language);
        this->setParameter("language",pLanguage);
    }

    Parameter *pSampleRate = Audio::getStaticParameter("sample_rate");
    pSampleRate->setValue(SampleRate);
    this->setParameter("sample_rate",pSampleRate);

    Parameter *pChannels = Audio::getStaticParameter("channels");
    pChannels->setValue(channels);
    this->setParameter("channels",pChannels);

    Parameter *pBitRate = Audio::getStaticParameter("resolution");
    pBitRate->setValue(bitRate);
    this->setParameter("resolution",pBitRate);
}

Model::Audio::Audio(QString uID) {
    m_uID = uID;
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_default = false;
}

Model::Audio::Audio(const Audio& a) {
    m_uID = a.m_uID;
    QMap<QString,Parameter*> *param(a.m_parameters) ;
    this->m_parameters = param;
    this->m_default = a.m_default;
}

Model::Audio& Model::Audio::operator=(const Audio& a) {
    if ( this != &a ) {
        m_uID = a.m_uID;
        QMap<QString,Parameter*> *param(a.m_parameters) ;
        this->m_parameters = param;
        this->m_default = a.m_default;
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
    m_staticParameters.insert("codec_name",codecNameParam);

    Parameter *language = new Parameter("-metadata:s:a:%1","This is the language of the audio stream","language=%1");
    m_staticParameters.insert("language",language);

    Parameter *delay = new Parameter("-itsoffset","This is the delay of the audio stream","%1");
    m_staticParameters.insert("delay",delay);

    Parameter *sampleRate = new Parameter("-ar","This is the sample rate of the audio stream","%1");
    m_staticParameters.insert("sample_rate",sampleRate);

    Parameter *channels = new Parameter("-ac","This is the channels of the audio stream","%1");
    m_staticParameters.insert("channels",channels);

    Parameter *resolution = new Parameter("-ab","This is the resolution of the audio stream","%1");
    m_staticParameters.insert("resolution",resolution);
}

void Model::Audio::initMetaType()
{
    qRegisterMetaTypeStreamOperators<Model::Audio>("Model::Audio");
    qMetaTypeId<Model::Audio>();
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
