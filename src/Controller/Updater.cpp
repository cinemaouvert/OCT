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

#include "src/Controller/Updater.h"
#include "src/Controller/OCTDispatcher.h"

// ========================================================================== //
// == Constructor and destructor ============================================ //
// ========================================================================== //
Controller::Updater::Updater(QObject *parent) :
    QObject(parent) {
    this->link = configOCT::URL + configOCT::NAME + "/" + configOCT::LINK_UPDATE;
}

Controller::Updater::~Updater() {}

// ========================================================================== //
// == Class methods ========================================================= //
// ========================================================================== //
void Controller::Updater::checkVersion(){
    QNetworkAccessManager manager(this);

    QUrl url_version (this->link + "version.txt");
    QNetworkRequest request(url_version);
    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();
    if (reply->error() == QNetworkReply::NoError){
       QString versionNew = reply->readAll();
       if (versionNew != configOCT::VERSION){
           if (QMessageBox::Yes == QMessageBox::question(NULL,
                                                         tr("Update OCT"),
                                                         tr("A new version of OCT is available, do you want download it ?\nSave your modification before update."
                                                            ),
                                                         QMessageBox::Yes|QMessageBox::No))
               this->getInstaller();
       }
    }else{
        QMessageBox::warning(NULL, tr("Update OCT"), tr("Update unreachable, maybe website is down or check your connection"));
    };
    reply->deleteLater();
}

void Controller::Updater::getInstaller(){
    /*QNetworkAccessManager manager(this);

    QFile * file = new QFile ( QString(configOCT::NAME_INSTALLER), this );
    file->open(QIODevice::WriteOnly);

    QUrl url_version (this->link);
    QNetworkRequest request(url_version);
    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    loop.exec();
    if (reply->error() == QNetworkReply::NoError){
        file->write(reply->readAll());
    }

    file->close();
    reply->deleteLater();
    */
    QDesktopServices::openUrl(QUrl(this->link));
}
