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

#include "src/Model/Subtitle.h"
#include "src/Model/Stream.h"
#include <QDebug>

QMap<QString, Model::Parameter *> Model::Subtitle::m_staticParameters;
Model::Subtitle::Subtitle(){
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_default = false;
}

Model::Subtitle::Subtitle(QDomNode stream, int uid)
{
    qDebug() << "Subtitle";
    QDomNamedNodeMap tab = stream.attributes();
    //-----------------------CODEC-NAME------------------------//
    QDomNode nodeCodecName = tab.namedItem("codec_name");
    QString codecName = nodeCodecName.nodeValue();
    if (codecName == "subrip")
        codecName = "srt";
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
    //-----------------------ENCODE------------------------//

    //-----------------------SUBTITLE-BUILD------------------------//
    this->m_uID = QString::number(uid);
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_default = false;
    if(isDefault == "1")
        this->m_default = true;

    Parameter *pCodecName = Subtitle::getStaticParameter("codec_name");
    pCodecName->setValue(codecName);
    this->setParameter("codec_name",pCodecName);

    if(language != ""){
        Parameter *pLanguage = Subtitle::getStaticParameter("language");
        pLanguage->setValue(language);
        this->setParameter("language",pLanguage);
    }
}

Model::Subtitle::Subtitle(QString uid) {
    this->m_parameters = new QMap<QString,Parameter*>();
    this->m_uID = uid;
    this->m_default = false;
}

Model::Subtitle::Subtitle(Model::Subtitle& copy) {
    this->m_uID = copy.m_uID;
    QMap<QString,Parameter*> *param(copy.m_parameters) ;
    this->m_parameters = param;
    this->m_default = copy.m_default;
}

Model::Subtitle &Model::Subtitle::operator=(const Model::Subtitle &o)
{
    if(this != &o){
        this->m_uID = o.m_uID;
        QMap<QString,Parameter*> *param(o.m_parameters) ;
        this->m_parameters = param;
        this->m_default = o.m_default;
    }
    return *this;
}

Model::Subtitle::~Subtitle()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

Model::Parameter *Model::Subtitle::getStaticParameter(QString key)
{
    Parameter *param = new Parameter(*(Subtitle::m_staticParameters.value(key)));
    return param;
}

void Model::Subtitle::initStaticParameters()
{
    Parameter *codecNameParam = new Parameter("-scodec","This is the codec of the subtitle stream","%1");
    m_staticParameters.insert("codec_name",codecNameParam);

    Parameter *language = new Parameter("-metadata:s:s:%1","This is the language of the subtitle stream","language=%1");
    m_staticParameters.insert("language",language);

    Parameter *charEncode = new Parameter("-sub_charenc","This is the encode of the subtitle stream, must be before the subtitle file","%1");
    m_staticParameters.insert("charEncode",charEncode);

}

int Model::Subtitle::getType()
{
    return Stream::SUBTITLE;
}



