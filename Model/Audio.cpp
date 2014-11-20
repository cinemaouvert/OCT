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

#include "Model/Audio.h"
#include "Model/Stream.h"

QMap<QString, Model::Parameter *> Model::Audio::m_staticParameters;
Model::Audio::Audio() {
    m_uID = "";
    this->m_parameters = NULL;
}

Model::Audio::Audio(QString uID) {
    m_uID = uID;
    this->m_parameters = NULL;
}

Model::Audio::Audio(const Audio& a) {
    m_uID = a.m_uID;
    QMap<QString,Parameter*> *param(a.m_parameters) ;
    this->m_parameters = param;
}

Model::Audio& Model::Audio::operator=(const Audio& a) {
    if ( this != &a ) {
        m_uID = a.m_uID;
        QMap<QString,Parameter*> *param(a.m_parameters) ;
        this->m_parameters = param;
    }
    return *this;
}

Model::Audio::~Audio() {
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

ostream& Model::Audio::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Audio::operator << (istream& o){
    throw "Not yet implemented";
}

Model::Parameter *Model::Audio::getStaticParameter(QString key)
{
    Parameter *param = new Parameter(*(Audio::m_staticParameters.value(key)));
    return param;
}

void Model::Audio::initStaticParameters()
{

}

