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

#include "src/Controller/Merger.h"
#include "src/Controller/OCTDispatcher.h"
#include "src/Model/Project.h"
#include <QProcess>
#include <QApplication>
#include <QDir>

// ========================================================================== //
// == Constructor =========================================================== //
// ========================================================================== //
Controller::Merger::Merger() : m_settings(NULL) {
     m_settings = new QSettings("CinemaOuvert", "OpenCinemaTranscoder");
}

// ========================================================================== //
// == Destructor ============================================================ //
// ========================================================================== //
Controller::Merger::~Merger() {
    delete(m_settings);
}

// ========================================================================== //
// == Class methods ========================================================= //
// ========================================================================== //
void Controller::Merger::createXML(Model::Project *project) {
	throw "Not yet implemented";
}

QString Controller::Merger::createMKVFile(Model::Project *project) {
    QString program = m_settings->value("mkvmerge").toString();
    QStringList arguments;
    arguments << *project->getMergeCommandLine();

    QProcess myProcess;
    myProcess.start(program, arguments);
    myProcess.waitForFinished(-1);
    qDebug() << myProcess.readAllStandardError();
    qDebug() << myProcess.readAllStandardOutput();

    QFile file(project->xmlFilePath());
    QString path = qApp->applicationDirPath() + QDir::separator() + "infos" + QDir::separator();
    if(file.exists())
        file.remove();
    QFile affiche(path+"affiche.png");
    if(affiche.exists())
        affiche.remove();
    QFile capture(path+"capture.png");
    if(capture.exists())
        capture.remove();
    return "filepath";
}

