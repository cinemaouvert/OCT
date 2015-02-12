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

#ifndef __Controller__StreamLoader_h__
#define __Controller__StreamLoader_h__

#include <QString>
#include <QList>


// #include "src/Controller/OCTDispatcher.h"
#include "src/Model/StreamWrapper.h"

namespace Controller
{
	class OCTDispatcher;
	class StreamLoader;
}
namespace Model
{
	class StreamWrapper;
}

namespace Controller
{
    /**
     * @brief StreamLoader controller.
     *
     * This classe parse streams.
     */
	class StreamLoader
	{
        public:
            /**
             * @brief The associated stream loader controller.
             */
            Controller::OCTDispatcher* m_streamLoader;

            /**
             * @brief This method retrieves distinct streams from ffmpeg.
             * @param ffmpegStream The ffmpeg stream that is to be parsed.
             * @return A QList of QString containing the distinct streams.
             */
            QList<QString> getDistinctStreams(QString ffmpegStream);

            /**
             * @brief This method parses streams.
             * @param streamToParse The stream that is to be parsed.
             * @return The StreamWrapper model equivalent once the stream is parsed.
             */
            Model::StreamWrapper* parseStreams(QString streamToParse);
	};
}

#endif
