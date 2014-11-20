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

#ifndef __Model__Information_h__
#define __Model__Information_h__

#include <QString>
#include "Model/Serializable.h"


namespace Model
{
	class Information;
    class Serializable;
}

namespace Model
{
    class Information : public Model::Serializable
	{
        private:
            /**
             * @brief The member name of the information.
             */
            QString m_name;

            /**
             * @brief The member value of the information.
             */
            QString m_value;

        public:
            /**
             * @brief Default constructor.
             */
            Information();

            /**
             * @brief Contructor
             * @param name The name of the information.
             * @param value The value of the information.
             */
            Information(QString name, QString value);

            /**
             * @brief Copy constructor.
             * @param i The Information object to copy.
             */
            Information(const Information& i);

            /**
             * @brief The affectation operator.
             * @param i The Information object to affect.
             * @return The current Information object modified.
             */
            Information& operator=(const Information& i);

            /**
             * @brief Destructor.
             */
            ~Information();

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
