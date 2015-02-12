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

// ========================================================================== //
// == Constructor =========================================================== //
// ========================================================================== //
Controller::TreatmentThread::TreatmentThread(QList<Model::Project*> *projects, Controller::Transcoder *transcoder, Controller::Merger *merger, Controller::Exporter *exporter) :
    m_transcoder(transcoder),
    m_merger(merger),
    m_exporter(exporter),
    m_projects(NULL),
    m_projectsOriginal(projects)
{
}

// ========================================================================== //
// == Class method ========================================================== //
// ========================================================================== //
void Controller::TreatmentThread::initTreatment(){
    if(this->m_projects != NULL)
        delete this->m_projects;

    m_projects = new QList<Model::Project*>();
    for(int i = 0; i < m_projectsOriginal->size(); i++){
        Model::Project *p = new Model::Project(*m_projectsOriginal->at(i));
        m_projects->push_back(p);
    }

    m_stop = false;
    m_pause = false;
    m_indexTreatment_i = 0;
    m_indexTreatment_j = 0;
    m_listToDelete.clear();
}

// ========================================================================== //
// == Public slot methods =================================================== //
// ========================================================================== //
void Controller::TreatmentThread::startTreatment() {
    int start_i = m_indexTreatment_i;
    int start_j = m_indexTreatment_j;


    qDebug() << "start treatment";
    int nbSteps = 0;
    for(int i = 0; i < m_projects->size(); i++){
        Model::Project *p = m_projects->at(i);
        nbSteps += p->fileList()->size();
    }

    if(start_i == 0 && start_j == 0){
        emit initProgress(nbSteps+1);
    }

    for(int i = start_i; i < m_projects->size() && !m_stop && !m_pause; i++){
        Model::Project *p = m_projects->at(i);
        for(int j = start_j; j < p->fileList()->size() && !m_stop && !m_pause; j++){

            Model::File *f = p->fileList()->at(j);
            int k = 0;
            //while(k < 100000){ qDebug() << k <<"j : " + QString::number(m_indexTreatment_j); k++;}
            if(f->hasToBeTranscoded()){
                m_transcoder->transcode(f->getCommandLine());
                m_listToDelete.append(f->getFilePath());
            }
            m_indexTreatment_j = j;
            emit passedStep();
        }

        if(m_indexTreatment_j == p->fileList()->size()-1){
            m_indexTreatment_j = 0;
            QString filepath = m_merger->createMKVFile(p);
            emit passedStep();
            //m_exporter = new Controller::Exporter(p->userKey(), p->depot());
            //m_exporter->createMagnetLink(p->name(), p->name());
            //m_exporter->sendInformationsToJSON(p, p->name());
            m_indexTreatment_i = i + 1; // Projet fini donc on passe au suivant si il y a pause
        }else{
           m_indexTreatment_i = i; //On reste au projet courant
        }

    }

    if(!m_pause){
        foreach (QString filePath, m_listToDelete) {
            QFile file(filePath);
            if(file.exists()){
                file.remove();
            }
        }
    }
    qDebug() << "ended treatment";
}

void Controller::TreatmentThread::pauseTreatment() {
    m_pause = true;
}

void Controller::TreatmentThread::stopTreatment() {
    m_stop = true;
    m_pause = false;
}

void Controller::TreatmentThread::restartTreatment(){
    this->m_pause = false;
    this->startTreatment();
}
