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
#include <QProcess>

#include "src/Controller/Exporter.h"
#include "src/Controller/OCTDispatcher.h"
#include "src/Model/Database.h"
#include "src/Model/Project.h"
#include "src/configOCT.h"

// ========================================================================== //
// == Constructor =========================================================== //
// ========================================================================== //
Controller::Exporter::Exporter(QString userKey, QString depot) : m_Database(NULL) {
    this->m_Database = new Model::Database(userKey, depot);
}

// ========================================================================== //
// == Destructor ============================================================ //
// ========================================================================== //
Controller::Exporter::~Exporter() {
    if(this->m_Database != NULL)
        delete this->m_Database;;
}

// ========================================================================== //
// == Class methods ========================================================= //
// ========================================================================== //
QString Controller::Exporter::createMagnetLink(QString filepath, QString nomTorrent) {
    QStringList arguments;
        arguments << "-jar" << "OCT.jar" <<createTorrentFile(filepath, nomTorrent);

    QProcess myProcess;
    myProcess.start("java", arguments);
    myProcess.waitForFinished();
    QString retour(myProcess.readAllStandardOutput());
    return retour;
}

QString Controller::Exporter::createTorrentFile(QString filepath, QString nomTorrent) {
    nomTorrent.append(".torrent");
    QStringList arguments;
        arguments << "-v" << "-p" << "-a" << configOCT::ADDRESSTRACKER << "-o" << nomTorrent << filepath;

    QString program = "mktorrent";
    #if defined(Q_OS_WIN)
        program = "mktorrent.exe";
    #endif

    QProcess myProcess;
    myProcess.start(program, arguments);
    myProcess.waitForFinished();
   // QString retour(myProcess.readAllStandardOutput());
    return nomTorrent;
}

bool Controller::Exporter::sendInformationsToJSON(Model::Project* project, QString url_magnet) {
    bool send = false;
    if(project != NULL){
        if(project->informations() != NULL){
            QByteArray  json = "{\"key_user\":\"" + m_Database->userKey().toUtf8()+ "\",\"quick\":\"off\"";
            QMap<QString, QString>::const_iterator i = project->informations()->constBegin();
            while (i != project->informations()->constEnd()) {
                json += "\"" + i.key() + "\":\"" + i.value() +"\",";
                ++i;
            }
            json += "\"url_magnet:\"\""+ url_magnet +"\"";

            //json.remove(json.size()-1, 1); // Supprime la dernière virgule
            json += "}";
            int res = this->m_Database->sendRequest(json);
            if(res == 200){
            send = true;
            }
        }
    }
    return send;
}

QStringList* Controller::Exporter::getInformations(){
    if(Model::Database::getMovieStruct() != NULL){
        QStringList *qsl = new QStringList(*(Model::Database::getMovieStruct()));
        //qsl->removeOne("affiche");
        qsl->removeOne("id");
        return qsl;
    }else{
        return NULL;
    }
}

QMap<QString, QString>* Controller::Exporter::getMovieInfoByTitle(QString title){
    return this->m_Database->getMovieByTitle(title);
}


