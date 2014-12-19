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

#include "src/Controller/Transcoder.h"
#include "src/Controller/OCTDispatcher.h"

#include <QProcess>


Controller::Transcoder::Transcoder() : m_settings(NULL) {
    m_settings = new QSettings("CinemaOuvert", "OpenCinemaTranscoder");
}

Controller::Transcoder::~Transcoder()
{
    delete(m_settings);
}

QString Controller::Transcoder::getInfo(QString filePath) {
    QString program = m_settings->value("ffprobe").toString();
    QStringList arguments;
        arguments
             <<"-v"<<"quiet"
             << "-print_format"<<"xml"
             <<"-show_streams" <<filePath;

    QProcess myProcess;
    myProcess.start(program, arguments);
    myProcess.waitForFinished();
    QString retour(myProcess.readAllStandardOutput());
    return retour;
}

QString Controller::Transcoder::transcode(QStringList *list) {
    QString ffmpegProgram = m_settings->value("ffmpeg").toString();
    QProcess myProcessFFMPEG;
    myProcessFFMPEG.start(ffmpegProgram, *list);
    myProcessFFMPEG.waitForFinished();
    QString retour(myProcessFFMPEG.readAll());
    return retour;
}

void Controller::Transcoder::process()
{
    qDebug() << "Super Thread";
    emit finished();

}

