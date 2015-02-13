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

#ifndef __Model__Data_h__
#define __Model__Data_h__

#include <QString>
#include "src/Model/Stream.h"
#include "src/Model/Serializable.h"

namespace Model
{
	class Stream;
	// class Serializable;
    class StreamWrapper;
}

namespace Model
{
    class StreamWrapper
    {
        private :
            friend QDataStream & operator >>(QDataStream  &in, StreamWrapper  &valeur);
            friend QDataStream & operator <<(QDataStream  &out, const StreamWrapper  &valeur);

            /**
             * @brief New stream.
             */
            Model::Stream* m_newStream;

            /**
             * @brief Old stream.
             */
            Model::Stream* m_oldStream;
        
        public:
            /**
             * @brief Default constructor.
             */
            StreamWrapper();

            /**
             * @brief Copy constructor.
             * @param d
             */
            StreamWrapper(StreamWrapper const& d);

            /**
             * @brief Affectation operator.
             * @param d The Data object to affect.
             * @return The current Data object modified.
             */
            StreamWrapper& operator=(StreamWrapper const& d);

            /**
             * @brief Destructor.
             */
            virtual ~StreamWrapper();

            /**
             * @brief Define if the current Data has to be transcoded.
             * @return 1 if yes, 0 if no.
             */
            bool hasToBeTranscoded() const;

            /**
             * @brief This method generate the command line associated with the data.
             * @return The command line.
             */
            QStringList* generateCommandLine();

            /**
             * @brief Accessor on the m_oldStream member.
             * @return The m_oldStream member pointer value.
             */
            Model::Stream* getRelevantStream();


            /**
             * @brief Accessor on the newStream member.
             * @return The m_newStream member pointer value.
             */
            Model::Stream *newStream() const;

            /**
             * @brief Mutator on the m_newStream member.
             * @param The pointer value to modify the m_newStream member.
             */
            void setNewStream(Model::Stream *newStream);

            /**
             * @brief Accessor on the m_oldStream member.
             * @return The m_oldStream member pointer value.
             */
            Model::Stream *oldStream() const;

            /**
             * @brief Mutator on the m_oldStream member.
             * @param The pointer value to modify the m_oldStream member.
             */
            void setOldStream(Model::Stream *oldStream);

            static void initMetaType();
    };
    QDataStream & operator <<(QDataStream  &out, const Model::StreamWrapper  &valeur);
    QDataStream & operator >>(QDataStream  &in, Model::StreamWrapper  &valeur);

}
Q_DECLARE_METATYPE(Model::StreamWrapper)


#endif
