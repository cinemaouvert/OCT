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

#include "src/Model/Information.h"


QString Model::Information::value() const
{
    return m_value;
}

void Model::Information::setValue(const QString &value)
{
    m_value = value;
}

QString Model::Information::name() const
{
    return m_name;
}

void Model::Information::setName(const QString &name)
{
    m_name = name;
}
Model::Information::Information() {}

Model::Information::Information(QString name, QString value) {
    m_name = name;
    m_value = value;
}

Model::Information::Information(const Information &i) {
    m_name = i.m_name;
    m_value = i.m_value;
}

Model::Information& Model::Information::operator=(const Model::Information& i) {
    if ( this != &i ) {
        m_name = i.m_name;
        m_value = i.m_value;
    }
    return *this;
}

Model::Information::~Information() {}

