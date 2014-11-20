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

#ifndef __Model__Video_h__
#define __Model__Video_h__

#include <QString>
#include <qdom.h>

#include "Model/Stream.h"

namespace Model
{
	// class Stream;
	class Video;
}

namespace Model
{
    /**
     * @brief The Video model class.
     */
	class Video: public Model::Stream
	{
        private:
            /**
             * @brief Additional command.
             */
            QString m_additionalCommand;

            /**
             * @brief List of associated static parameter.
             */
            static QMap<QString, Parameter *> m_staticParameters;

        public:
            /**
             * @brief Default constructor.
             */
            Video();

            /**
             * @brief Constructor.
             * @param stream Associated stream.
             */
            Video(QDomNode stream);

            /**
             * @brief Constructor.
             * @param uid Associated uid.
             */
            Video(QString uid);

            /**
             * @brief Copy constructor.
             * @param copy The Video object to be copied.
             */
            Video(const Video& copy);

            /**
             * @brief Destructor.
             */
            virtual ~Video();

            /**
             * @brief Affectation operator.
             * @param o The video object to be affected.
             * @return The current Video object modified.
             */
            Video& operator=(const Video& o);

            /**
             * @brief operator >>
             * @param o
             * @return
             */
            virtual ostream& operator >> (ostream& o);

            /**
             * @brief operator <<
             * @param o
             * @return
             */
            virtual istream& operator << (istream& o);

            /**
             * @brief Accessor on the static parameter list.
             * @param key Key to search for the corresponding entry.
             * @return The corresponding entry.
             */
            static Parameter *getStaticParameter(QString key);

            /**
             * @brief Initialize the static parameter list member.
             */
            static void initStaticParameters();
	};
}

#endif
