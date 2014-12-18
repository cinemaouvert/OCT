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

#include "src/Model/StreamWrapper.h"
#include "src/Model/Stream.h"
#include "src/Model/Serializable.h"


Model::Stream *Model::StreamWrapper::newStream() const
{
    return m_newStream;
}

void Model::StreamWrapper::setNewStream(Model::Stream *newStream)
{
    m_newStream = newStream;
}

Model::Stream *Model::StreamWrapper::oldStream() const
{
    return m_oldStream;
}

void Model::StreamWrapper::setOldStream(Model::Stream *oldStream)
{
    m_oldStream = oldStream;
}
Model::StreamWrapper::StreamWrapper() : m_oldStream(NULL), m_newStream(NULL) {
}

Model::StreamWrapper::StreamWrapper(const StreamWrapper& d) {
}

Model::StreamWrapper& Model::StreamWrapper::operator=(const StreamWrapper& d) {
    if ( this != &d ) {
        m_oldStream = d.m_oldStream;
        m_newStream = d.m_newStream;
    }
    return *this;
}

Model::StreamWrapper::~StreamWrapper() {
    if(this->m_newStream != NULL)
        delete this->m_newStream;

    if(this->m_oldStream != NULL)
        delete this->m_oldStream;
}

bool Model::StreamWrapper::hasToBeTranscoded() {
    bool res = false;
    if(this->m_newStream != NULL)
        res = true;
    return res;
}

QStringList* Model::StreamWrapper::generateCommandLine() {
    if(hasToBeTranscoded())
        return this->m_newStream->getCommand();
    else
        return NULL;
}

Model::Stream* Model::StreamWrapper::getOldStream() {
    return m_oldStream;
}



