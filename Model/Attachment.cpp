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
#include "Model/Attachment.h"



Model::Attachment::Attachment() {
    m_filepath = "";
}

Model::Attachment::Attachment(QString filepath) {
    m_filepath = filepath;
}

Model::Attachment::Attachment(const Attachment& a) {
    m_filepath = a.m_filepath;
}

Model::Attachment& Model::Attachment::operator=(const Attachment& a) {
    if ( this != &a ) {
        m_filepath = a.m_filepath;
    }
    return *this;
}

Model::Attachment::~Attachment() {
    m_filepath = "";
}

void Model::Attachment::initMetaType()
{
    qRegisterMetaTypeStreamOperators<Model::Attachment>("Model::Attachment");
    qMetaTypeId<Model::Attachment>();
}


QString Model::Attachment::filepath() const
{
    return this->m_filepath;
}

QDataStream &Model::operator >>(QDataStream &in, Model::Attachment &valeur)
{
    in >> valeur.m_filepath;
    return in;
}
QDataStream &Model::operator <<(QDataStream &out, const Model::Attachment& valeur)
{
    out << valeur.m_filepath;
    return out;
}



