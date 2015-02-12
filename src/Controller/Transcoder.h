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

#ifndef __Controller__Transcoder_h__
#define __Controller__Transcoder_h__


#include <QString>
#include <QObject>
#include <QSettings>

// #include "src/Controller/OCTDispatcher.h"

namespace Controller
{
	class OCTDispatcher;
	class Transcoder;
}

namespace Controller
{
    /**
     * @brief Trancoder controller.
     *
     * This class retrieve transcoder informations and commands to transcode
     * a given file considering given settings.
     */
    class Transcoder
	{
        public:

            /**
             * @brief Default constructor.
             */
            Transcoder();

            ~Transcoder();

            /**
             * @brief This method retrieves informations from a given file.
             *
             * This method uses ffprobe to retrieve information from
             * a given media file.
             *
             * @param filePath to the file.
             * @return The retrieved informations within a QString.
             */
            QString getInfo(QString filePath);

            /**
             * @brief This method transcode from a given command.
             * @param list The list of parameter to transcode.
             * @return The transcoded result.
             */
            QString transcode(QStringList *list);

        private:
            /**
             * @brief The associated settings.
             */
            QSettings                   *m_settings;
	};
}

#endif
