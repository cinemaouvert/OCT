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

#include "src/Model/Stream.h"
#include "src/Model/StreamWrapper.h"
#include "src/Model/Serializable.h"

#include "Audio.h"
#include "Subtitle.h"
#include "Video.h"

#include <QDebug>

const QString Model::Stream::CODEC_NAME = "codec_name";
const QString Model::Stream::LANGUAGE = "language";
const QString Model::Stream::DEFAULT ="default";
const QString Model::Stream::RESOLUTION ="resolution";
const QString Model::Stream::VIDEO_FORCE_ASPECT ="forceAspect";
const QString Model::Stream::VIDEO_FRAME_RATE ="r_frame_rate";
const QString Model::Stream::VIDEO_AVG_BIT_RATE ="bitRate";
const QString Model::Stream::VIDEO_DEINTERLACE ="deinterlace";
const QString Model::Stream::VIDEO_START_TIME ="start_pts";
const QString Model::Stream::VIDEO_STOP_POINT ="stop_pts";
const QString Model::Stream::VIDEO_CROP ="crop";
const QString Model::Stream::AUDIO_DELAY ="delay";
const QString Model::Stream::AUDIO_SAMPLE_RATE ="sample_rate";
const QString Model::Stream::AUDIO_CHANNELS = "channels";
const QString Model::Stream::SUBTITLE_CHAR_ENCODE ="charEncode";

void Model::Stream::setParameter(QString name, Parameter *value) {
    this->m_parameters->insert(name,value);
}

QString Model::Stream::getUID() {
    return this->m_uID;
}

QMap<QString, Model::Parameter *> *Model::Stream::getParameters() const
{
    return this->m_parameters;
}


QStringList *Model::Stream::getCommand()
{
    QStringList *myStringList = new QStringList();

    for(int i = 0; i < this->m_parameters->size();i++){
       Parameter *param = this->m_parameters->values().at(i);
       QString value = param->value();
       while(param->noSpaceForNext() && i < m_parameters->size()-1){
           if(i < this->m_parameters->size()-1 ){
                i++;
                param = this->m_parameters->values().at(i);
                value+=param->value();
           }
       }
       QString command = param->command();
       if(command.contains("%")){
            command = command.arg(this->getUID());
       }
       if(command != "" && value != "")
         *myStringList << command << value ;
       else if(command == "" && value != "")
         *myStringList << value ;
       else if(value == "" && command != "")
         *myStringList << command ;

    }
    return myStringList;
}


bool Model::Stream::isDefault() const
{
    return m_default;
}

void Model::Stream::setDefault(bool d)
{
    m_default = d;
}

QString Model::Stream::name() const
{
    return m_name;
}

void Model::Stream::setName(const QString &name)
{
    m_name = name;
}

bool Model::Stream::operator==(const Model::Stream &s)
{
    if(s.getType() == getType()){
        bool retVal = true;
        retVal = retVal && (s.name() == name());
        foreach (QString key, getParameters()->keys()) {
            if(s.getParameters()->contains(key)){
                if(getParameters()->value(key)->value() != s.getParameters()->value(key)->value()){
                    return false;
                }
            }else{
                return false;
            }
        }
        return retVal;
    }
    return false;

}
Model::Stream::~Stream()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

int Model::Stream::getEnumValue(QString type)
{
    if(type == "video"){
       return 0;
    }else if(type == "audio"){
       return 1;
    }else if(type == "subtitle"){
       return 2;
    }else{
       return 3;
    }
}

