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
#include <vector>
using namespace std;

#include "src/Controller/TreatmentThread.h"
#include "src/Controller/Transcoder.h"
#include "src/Controller/Merger.h"
#include "src/Controller/Exporter.h"
#include "src/Controller/OCTDispatcher.h"
#include "src/Model/Project.h"

Controller::TreatmentThread::TreatmentThread(QList<Model::Project*> *projects, Controller::Transcoder *transcoder, Controller::Merger *merger, Controller::Exporter *exporter) :
    m_transcoder(NULL),
    m_merger(NULL),
    m_exporter(NULL),
    m_projects(NULL)
{
    m_transcoder = new Transcoder();

    m_projects = new QList<Model::Project*>();
    for(int i = 0; i < projects->size(); i++){
        Model::Project *p = new Model::Project(*projects->at(i));
        m_projects->push_back(p);
    }
}

void Controller::TreatmentThread::startTreatment() {

}

void Controller::TreatmentThread::pauseTreatment() {

}

void Controller::TreatmentThread::stopTreatment() {

}
