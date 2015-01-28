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

#include "EncodePane.h"
#include "ui_encodepane.h"
#include "src/Controller/TreatmentThread.h"

#include <QFileDialog>
#include <QMouseEvent>

// ========================================================================== //
// == CONSTRUCTORS AND DESTRUCTORS ========================================== //
// ========================================================================== //
EncodePane::EncodePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EncodePane)
{
    ui->setupUi(this);
    m_modelProjectList = new QStringListModel(this);
    ui->listViewProjects->setModel(m_modelProjectList);
    ui->listViewProjects->setAlternatingRowColors(true);
    ui->listViewProjects->setEncodePane(this);
    m_currentSteps = 0;
}

EncodePane::~EncodePane()
{
    if(ui) delete ui;
    if(m_modelProjectList) delete m_modelProjectList;
}

// ========================================================================== //
// == ACCESSORS AND MUTATORS ================================================ //
// ========================================================================== //
void EncodePane::setDispatcher(Controller::OCTDispatcher *dispatcher)
{
    this->m_dispatcher = dispatcher;
    refreshProjectPane();
    connectInterface();
}

// ========================================================================== //
// == CLASS METHODS ========================================================= //
// ========================================================================== //
void EncodePane::refresh()
{

}

void EncodePane::refreshProjectPane()
{
    QStringList list;
    foreach (Model::Project *project, *(m_dispatcher->getProjects())) {
        list << project->name();
    }
    m_modelProjectList->setStringList(list);
}

void EncodePane::passedProgressStep()
{
    m_currentSteps ++;
    ui->progressBar_Encoding->setValue((int)((float)((float)m_currentSteps/(float)m_progressMax)*100));
}

void EncodePane::changeCurrentProject(int index)
{
    m_dispatcher->setCurrentProjectIndex(index);
}

void EncodePane::duplicateProject(int index)
{
    m_dispatcher->duplicateProject(index);
    refreshProjectPane();
}

// ========================================================================== //
// == EVENT METHODS ========================================================= //
// ========================================================================== //
void EncodePane::connectInterface()
{
    connect(m_dispatcher->getTreatmentThread(),SIGNAL(initProgress(int)),this,SLOT(initProgressBar(int)));
    connect(m_dispatcher->getTreatmentThread(),SIGNAL(passedStep()),this,SLOT(passedProgressStep()));
}

void EncodePane::on_newProjectButton_clicked()
{
    m_dispatcher->addToQueue();
    refreshProjectPane();
}

void EncodePane::initProgressBar(int progressMax)
{
    m_progressMax = progressMax;
    ui->progressBar_Encoding->setValue(0);
}

void EncodePane::on_pushButton_Encode_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this,tr("Choisir le chemin"));
       this->m_dispatcher->getCurrentProject()->setName(filePath.append("/").append(this->m_dispatcher->getCurrentProject()->name()));


    m_dispatcher->startTreatment();
    ui->pushButton_Cancel->setEnabled(true);
    ui->pushButton_Pause->setEnabled(true);
}

void EncodePane::on_pushButton_Cancel_clicked()
{
    m_dispatcher->stopTreatment();
    ui->pushButton_Cancel->setEnabled(false);
    ui->pushButton_Pause->setEnabled(false);
}

void EncodePane::on_pushButton_Pause_clicked()
{
    m_dispatcher->pauseTreatment();
}
