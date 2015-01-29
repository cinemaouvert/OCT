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
#include "src/configOCT.h"

Controller::TreatmentThread::TreatmentThread(QList<Model::Project*> *projects, Controller::Transcoder *transcoder, Controller::Merger *merger, Controller::Exporter *exporter) :
    m_transcoder(transcoder),
    m_merger(merger),
    m_exporter(exporter),
    m_projects(NULL),
    m_projectsOriginal(projects)
{

}

void Controller::TreatmentThread::initTreatment(){
    if(this->m_projects != NULL)
        delete this->m_projects;

    m_projects = new QList<Model::Project*>();
    for(int i = 0; i < m_projectsOriginal->size(); i++){
        Model::Project *p = new Model::Project(*m_projectsOriginal->at(i));
        m_projects->push_back(p);
    }
}

void Controller::TreatmentThread::startTreatment() {
    //Init barre avancement
    qDebug() << "start treatment";
    QStringList listToDelete;
    int nbSteps = 0;
    for(int i = 0; i < m_projects->size(); i++){
        Model::Project *p = m_projects->at(i);
        nbSteps += p->fileList()->size();
    }
    qDebug() << "HERE";
    emit initProgress(nbSteps+1);

    for(int i = 0; i < m_projects->size(); i++){
        Model::Project *p = m_projects->at(i);
        for(int j = 0; j < p->fileList()->size(); j++){

            Model::File *f = p->fileList()->at(j);
            if(f->hasToBeTranscoded()){
                m_transcoder->transcode(f->getCommandLine());
                listToDelete.append(f->getFilePath());
            }
            emit passedStep();
        }
        QString filepath = m_merger->createMKVFile(p);
        emit passedStep();
        //m_exporter->createMagnetLink("", p->name());
        //m_exporter->sendInformationsToJSON(p);
    }
    foreach (QString filePath, listToDelete) {
        QFile file(filePath);
        if(file.exists()){
            file.remove();
        }
    }
    qDebug() << "ended treatment";
}

void Controller::TreatmentThread::pauseTreatment() {

}

void Controller::TreatmentThread::stopTreatment() {

}
