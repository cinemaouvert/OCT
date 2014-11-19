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

#ifndef __Model__Attachment_h__
#define __Model__Attachment_h__

#include <QString>
#include "Model/Serializable.h"
#include "Model/Serializable.h"


namespace Model
{
    class Serializable;
	class Attachment;
}

namespace Model
{
	class Attachment: public Model::Serializable
    {
        /**
         * @brief The associated file path.
         */
        QString m_filepath;

        public:
            /**
             * @brief Default contructor.
             */
            Attachment();

            /**
             * @brief Constructor.
             * @param filepath The file path to the attachement file.
             */
            Attachment(QString filepath);

            /**
             * @brief Copy constructor.
             * @param a A given Attachement object to copy.
             */
            Attachment(const Attachment& a);

            /**
             * @brief Affectation operator.
             * @param a A given Attachement object to affect.
             * @return The current Attachement object modified.
             */
            Attachment& operator=(const Attachment& a);

            /**
             * @brief Destructor.
             */
            virtual ~Attachment();

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
	};
}

#endif
