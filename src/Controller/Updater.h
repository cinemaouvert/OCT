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

#ifndef __Controller__Updater_h__
#define __Controller__Updater_h__

// #include "src/Controller/OCTDispatcher.h"

#include <QObject>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QEventLoop>
#include <QMessageBox>
#include <QProcess>
#include <QDesktopServices>

#include "src/configOCT.h"

namespace Controller
{
	class OCTDispatcher;
	class Updater;
}

namespace Controller
{
    /**
    * @brief Base class to update the OCT application
    */
    class Updater : public QObject
    {
        public:
            /**
             * @brief Constructor
             * @param parent
             */
            Updater(QObject *parent = 0);

            /**
             * @brief Destructor.
             */
            virtual ~Updater();

            /**
            * @brief Compare version software with installer on cinemaouvert.fr
            *
            */
            void checkVersion();

        private:
            /**
            * @brief Download installer
            */
            void getInstaller();

            /**
             * @brief Link to the installer.
             */
            QString link;
    };

}

#endif
