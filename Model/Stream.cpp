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

#include "Model/Stream.h"
#include "Model/Data.h"
#include "Model/Serializable.h"

void Model::Stream::setParameter(QString name, Parameter *value) {
    this->m_parameters->insert(name,value);
}

QString Model::Stream::getUID() {
    return this->m_uID;
}

QStringList *Model::Stream::getCommand()
{
    QStringList *myStringList = new QStringList();

    for(int i = 0; i < this->m_parameters->size()-1;i++){
       Parameter *param = this->m_parameters->values().at(i);
       QString value = param->value();
       while(param->noSpaceForNext()){
           if(i < this->m_parameters->size()-1 )
            i++;
            param = this->m_parameters->values().at(i);
            value+=param->value();
       }
       QString command = param->command();
       if(command.contains("%")){
            command = command.arg(this->getUID());
       }
       *myStringList << command << value ;
    }
    return myStringList;
}

Model::Stream::~Stream()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

