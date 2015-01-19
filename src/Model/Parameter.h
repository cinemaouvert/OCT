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
#include <QString>
using namespace std;

#ifndef __Model__Parameter_h__
#define __Model__Parameter_h__
#include "src/Model/Serializable.h"

namespace Model
{
	class Parameter;
}

namespace Model
{
    class Parameter
	{
        private:
            /**
             * @brief Command of the current parameter.
             */
            QString m_command;

            /**
             * @brief Description of the current parameter.
             */
            QString m_description;

            /**
             * @brief Value of the current parameter.
             */
            QString m_value;

            /**
             * @brief Original Value of the current parameter.
             */
            QString m_originalValue;

            /**
             * @brief Member defined whether the parameter need to be spaced from next one.
             */
            bool m_noSpaceForNext;

            friend QDataStream & operator <<(QDataStream  &out, const Parameter  &valeur);
            friend QDataStream & operator >>(QDataStream  &in, Parameter  &valeur);


        public:
            /**
             * @brief Default constructor.
             */
            Parameter();

            /**
             * @brief Constructor.
             * @param cmd The command name.
             * @param desc The description of the current parameter.
             * @param val The value associated with the current parameter.
             */
            Parameter(QString cmd,QString desc,QString val);

            /**
             * @brief Constructor.
             * @param
             */
            Parameter(const Parameter& copy);

            /**
             * @brief Affectation operator.
             * @param o The Parameter object to affect.
             * @return The current Parameter object modified.
             */
            Parameter& operator=(const Parameter& o);

            /**
             * @brief Destructor.
             */
            virtual ~Parameter();

            /**
             * @brief Mutator for value member.
             * @param value The value to replace the current value member.
             */
            void setValue(const QString &value);

            /**
             * @brief Accessor on description member of the current parameter.
             * @return The value of description member.
             */
            QString description() const;

            /**
             * @brief Accessor on value member of the current parameter.
             * @return The value of value member.
             */
            QString value() const;

            /**
             * @brief Accessor on command member of the current parameter.
             * @return The value of the command member.
             */
            QString command() const;

            /**
             * @brief Accessor on command and value member of the current parameter.
             * @return The value of the command parameter with associated value.
             */
            QString commandAndValue() const;

            /**
             * @brief Method to set if the current parameter is to have no space with next parameter in the command line.
             * @param val 1 if yes, 0 if no.
             */
            void SetNoSpaceForNext(bool val = true);

            /**
             * @brief Accessor to the space member value.
             * @return The space member value.
             */
            bool noSpaceForNext();

            static void initMetaType();

    };
    QDataStream & operator <<(QDataStream  &out, const Model::Parameter  &valeur);
    QDataStream & operator >>(QDataStream  &in, Model::Parameter &valeur);
}
Q_DECLARE_METATYPE(Model::Parameter)



#endif
