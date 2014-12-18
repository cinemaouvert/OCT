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

#include "src/Model/Database.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>

#include "src/configOCT.h"


QString Model::Database::depot() const
{
    return m_depot;
}

QString Model::Database::userKey() const
{
    return m_userKey;
}

Model::Database::Database(QString userKey, QString depot) {
    this->m_userKey = userKey;
    this->m_depot = depot;
}

Model::Database::Database(const Database& db) {
    m_userKey = db.m_userKey;
    m_depot = db.m_depot;
}

Model::Database& Model::Database::operator=(const Database& db) {
    if ( this != &db ) {
        m_userKey = db.m_userKey;
        m_depot = db.m_depot;
    }
    return *this;
}

Model::Database::~Database() {}

int Model::Database::sendRequest(QByteArray jsonString) {
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    //Changer le premier dépot par config_oct::DEPOTCOC
    QUrl url(this->m_depot + "?resolver="+ this->m_depot +"&movie");
    QNetworkRequest request(url);

    request.setRawHeader("User-Agent", configOCT::NAME.toStdString().c_str());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();

    QEventLoop loop;
    QNetworkReply* reply = networkManager->post(request, jsonString);
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QVariant statusCodeV = -1;
    if (reply->error() == QNetworkReply::NoError){
        statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    }

    reply->deleteLater();

    return statusCodeV.toInt();
}

