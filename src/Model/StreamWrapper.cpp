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

#include <QDebug>

#include "src/Model/StreamWrapper.h"
#include "src/Model/Stream.h"
#include "src/Model/Serializable.h"
#include "src/Model/Video.h"
#include "src/Model/Audio.h"
#include "src/Model/Subtitle.h"

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

void Model::StreamWrapper::initMetaType()
{
    qRegisterMetaTypeStreamOperators<Model::StreamWrapper>("Model::StreamWrapper");
    qMetaTypeId<Model::StreamWrapper>();
}

Model::StreamWrapper::StreamWrapper() : m_oldStream(NULL), m_newStream(NULL) {
}

//A tester
Model::StreamWrapper::StreamWrapper(const StreamWrapper& d) {
    if(d.m_oldStream){
        switch (d.m_oldStream->getType()){
            case Model::Stream::VIDEO:
                m_oldStream = new Model::Video(*((Model::Video*)d.m_oldStream));
                break;
            case Model::Stream::AUDIO:
                m_oldStream = new Model::Audio(*((Model::Audio*)d.m_oldStream));
                break;
            case Model::Stream::SUBTITLE:
                m_oldStream = new Model::Subtitle(*((Model::Subtitle*)d.m_oldStream));
                break;
        }
    }else{
        m_oldStream = NULL;
    }
    if(d.m_newStream){

        switch (d.m_newStream->getType()){
            case Model::Stream::VIDEO:
                m_newStream = new Model::Video(*((Model::Video*)d.m_newStream));
                break;
            case Model::Stream::AUDIO:
                m_newStream = new Model::Audio(*((Model::Audio*)d.m_newStream));
                break;
            case Model::Stream::SUBTITLE:
                m_newStream = new Model::Subtitle(*((Model::Subtitle*)d.m_newStream));
                break;
        }
    }else{
        m_newStream = NULL;
    }
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

bool Model::StreamWrapper::hasToBeTranscoded() const{
    bool res = false;
    if(this->m_newStream != NULL)
        res = true;
    return res;
}

QStringList* Model::StreamWrapper::generateCommandLine() {
    if(hasToBeTranscoded())
        return this->m_newStream->getCommand();
    else
        return this->m_oldStream->getCommand();
}

Model::Stream *Model::StreamWrapper::getRelevantStream()
{

    if(hasToBeTranscoded())
        return this->m_newStream;
    else
        return this->m_oldStream;

}

QDataStream &Model::operator <<(QDataStream &out, const Model::StreamWrapper &valeur)
{
    out << valeur.m_oldStream->getType();
    qDebug() << "WRITE Stream Type : "<< valeur.m_oldStream->getType();

    switch (valeur.m_oldStream->getType()) {
        case Stream::AUDIO:
            out << *((Audio*)(valeur.m_oldStream));
            if(valeur.hasToBeTranscoded()){
                //out << "hasNext";
                //out << *(Audio*)(valeur.m_newStream);
            }else{
                //out << "noNext";
            }
            qDebug()<< "WRITE AUDIO";
            break;

        case Stream::VIDEO:
            out << *((Video*)(valeur.m_oldStream));
            if(valeur.hasToBeTranscoded()){
                //out << "hasNext";
                //out << *(Video*)(valeur.m_newStream);
            }else{
                //out << "noNext";
            }
            qDebug()<< "WRITE Video";

            break;

        case Stream::SUBTITLE:
            out << *((Subtitle*)(valeur.m_oldStream));
            if(valeur.hasToBeTranscoded()){
                //out << "hasNext";
                //out << *(Subtitle*)(valeur.m_newStream);
            }else{
                //out << "noNext";
            }
            qDebug()<< "WRITE Subtitle";

            break;
    }
    return out;
}


QDataStream &Model::operator >>(QDataStream &in, Model::StreamWrapper &valeur)
{
    int streamType;
    in >>streamType;
    Audio *a;
    Video *v;
    Subtitle *s;
    QString hasNext;
    qDebug() << "READ Stream Type : "<< streamType;
    switch (streamType) {
        case Stream::AUDIO:
            qDebug()<< "READ Audio";

            a = new Audio;
            in >> *a;
            valeur.setOldStream(a);
            /*in >> hasNext;
            if(hasNext == "hasNext"){
                a = new Audio;
                in >> *a;
                valeur.setNewStream(a);
            }*/
            break;
        case Stream::VIDEO:
            qDebug()<< "READ Video";

            v = new Video;
            in >> *v;
            valeur.setOldStream(v);
            /*in >> hasNext;
            if(hasNext == "hasNext"){
                v = new Video;
                in >> *v;
                valeur.setNewStream(v);
            }*/

            break;
        case Stream::SUBTITLE:
            qDebug()<< "READ SUBTITLE";

            s = new Subtitle;
            in >> *s;
            valeur.setOldStream(s);
            /*in >> hasNext;
            if(hasNext == "hasNext"){
                s = new Subtitle;
                in >> *s;
                valeur.setNewStream(s);
            }*/
            break;
    }

    return in;
}





