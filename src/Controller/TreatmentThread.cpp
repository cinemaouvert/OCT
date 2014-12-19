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
    m_transcoder(transcoder),
    m_merger(merger),
    m_exporter(exporter),
    m_projects(projects)
{
}

void Controller::TreatmentThread::startTreatment() {
    m_transcoderThread = new QThread();

    connect(m_transcoderThread, SIGNAL(started()), m_transcoder, SLOT(process()));
    connect(m_transcoder, SIGNAL(finished()), m_transcoderThread, SLOT(quit()));
    //connect(m_transcoder, SIGNAL(finished()), m_transcoder, SLOT(deleteLater()));

    connect(m_transcoderThread, SIGNAL(finished()), m_transcoderThread, SLOT(deleteLater()));

    m_transcoder->moveToThread(m_transcoderThread);
    m_transcoderThread->start();
}

void Controller::TreatmentThread::pauseTreatment() {
    if(m_transcoderThread->isRunning())
        m_transcoderThread->wait(ULONG_MAX);
    else
        m_transcoderThread->start();
}

void Controller::TreatmentThread::stopTreatment() {
    if(m_transcoderThread->isRunning())
        m_transcoderThread->quit();
}
