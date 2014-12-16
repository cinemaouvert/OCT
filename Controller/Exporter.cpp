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

#include "Controller/Exporter.h"
#include "Controller/OCTDispatcher.h"
#include "Model/Database.h"
#include "Model/Project.h"
#include "Model/Information.h"
#include <QDebug>

Controller::Exporter::Exporter(QString userKey, QString depot) : m_Database(NULL) {
    this->m_Database = new Model::Database("1", "http://localhost/CODB-Depot-master/");
}

QString Controller::Exporter::createMagnetLink(QString filepath) {
    throw "Not yet implemented";
}

bool Controller::Exporter::sendInformationsToJSON(Model::Project* project)
{
    bool send = false;
    if(project != NULL){
        QList<Model::Information*> *informations = project->informations();
        if(informations != NULL){
            QByteArray  json = "{\"key_user\":\"" + m_Database->userKey().toUtf8()+ "\",\"quick\":\"false\"";
            for (int i = 0; i < informations->size(); i++) {
                Model::Information* info = informations->at(i);
                json += "\"" + info->name() + "\":\"" + info->value() +"\",";
            }
            json.remove(json.size()-1, 1); // Supprime la dernière virgule
            json += "}";
            int res = this->m_Database->sendRequest(json);
            if(res == 200){
                send = true;
            }
        }
    }
    return send;
}



