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
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QMap>

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

QStringList* Model::Database::getMovieStruct() {
    QUrl url(configOCT::DEPOTCOC + "?movie=&structure");
    QNetworkRequest request(url);

    request.setRawHeader("User-Agent", configOCT::NAME.toStdString().c_str());
    request.setRawHeader("Content-Type", "application/json");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();

    QEventLoop loop;
    QNetworkReply* reply = networkManager->get(request);
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QVariant statusCodeV = -1;
    QStringList *movieStructList = NULL;

    QFile file(qApp->applicationDirPath() + QDir::separator() +"struct.json");

    if (reply->error() == QNetworkReply::NoError){
        statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        QByteArray movieStruct = reply->readAll();
        if(statusCodeV == 200){
            if (file.open(QIODevice::WriteOnly)){
                QTextStream out(&file);
                out << movieStruct;
                file.close();
            }
        }

        movieStructList = createStruct(movieStruct);
    }else{
        if (file.open(QIODevice::ReadOnly)){
            movieStructList = createStruct(file.readAll());
            file.close();
        }
    }
    reply->deleteLater();

    return movieStructList;
}

QMap<QString, QString>* Model::Database::getMovieByTitle(QString title) {
    QUrl url(this->m_depot + "?resolver="+ this->m_depot +"&movie&title="+title+"&key_user="+ this->m_userKey);
    QNetworkRequest request(url);

    request.setRawHeader("User-Agent", configOCT::NAME.toStdString().c_str());
    request.setRawHeader("Content-Type", "application/json");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();

    QEventLoop loop;
    QNetworkReply* reply = networkManager->get(request);
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QVariant statusCodeV = -1;
    QMap<QString, QString> *movieData = NULL;

    if (reply->error() == QNetworkReply::NoError){
        statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        QByteArray movieStruct = reply->readAll();

        movieData = createMovie(movieStruct);
    }
    reply->deleteLater();

    return movieData;
}

QMap<QString, QString>* Model::Database::createMovie(QByteArray movieStruct){
    QMap<QString, QString> *movieData = new  QMap<QString, QString>;
    QJsonDocument qjd;
    qjd = QJsonDocument::fromJson(movieStruct);
    QJsonObject qjo = qjd.object();

    QStringList keys = qjo.keys();
    for(int i = 0; i < qjo.size(); i++){
        QString key = keys.at(i);
        movieData->insert(key, qjo.value(key).toString());
    }

    return movieData;
}

QStringList* Model::Database::createStruct(QByteArray movieStruct){
    QStringList *movieStructList = NULL;
    QJsonDocument qjd;
    qjd = QJsonDocument::fromJson(movieStruct);
    QJsonObject qjo = qjd.object();
    movieStructList = new QStringList(qjo.keys());
    return movieStructList;
}
