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

#ifndef __Model__Stream_h__
#define __Model__Stream_h__

#include <QString>
#include <QMap>
#include <qstringlist.h>

// #include "src/Model/Data.h"
#include "src/Model/Parameter.h"
#include "src/Model/Serializable.h"

namespace Model
{
	// class Serializable;
	class Stream;
    class Parameter;


}

namespace Model
{
    class Stream
	{
        protected:
            /**
             * @brief m_uID
             */
            QString m_uID;

            /**
             * @brief m_name
             */
            QString m_name;

            /**
             * @brief m_default
             */
            bool m_default;

            /**
             * @brief List of parameter associated with the stream.
             */
            QMap<QString,Parameter*> *m_parameters;

        public:
            /**
             * @brief Destructor.
             */
            virtual ~Stream();

            /**
             * @brief Mutator for the parameter list.
             * @param name The name of the parameter.
             * @param value The value associated with the parameter.
             */
            virtual void setParameter(QString name, Parameter *value);

            /**
             * @brief Accessor for the uID member.
             * @return The uID member value.
             */
            virtual QString getUID();

            /**
             * @brief Accessor for the parameters member.
             * @return The parameters member value.
             */
            virtual QMap<QString,Parameter*> *getParameters();

            /**
             * @brief Accessor for the command list.
             * @return The command list member value.
             */
            virtual QStringList *getCommand();


            enum fileType{
                VIDEO = 0,
                AUDIO = 1,
                SUBTITLE = 2,
                ATTACHMENT = 3
            };
            static int getEnumValue(QString type);
            virtual bool isDefault() const;
            virtual void setDefault(bool d);

            virtual int getType()=0;
            QString name() const;
            void setName(const QString &name);
			
			static const QString CODEC_NAME;
			static const QString LANGUAGE;
			static const QString DEFAULT;
			static const QString RESOLUTION;
			static const QString VIDEO_FORCE_ASPECT;
			static const QString VIDEO_FRAME_RATE;
			static const QString VIDEO_AVG_BIT_RATE;
			static const QString VIDEO_DEINTERLACE;
			static const QString VIDEO_START_TIME;
			static const QString VIDEO_STOP_POINT;
			static const QString VIDEO_CROP;
			static const QString AUDIO_DELAY;
			static const QString AUDIO_SAMPLE_RATE;
			static const QString AUDIO_CHANNELS;
			static const QString SUBTITLE_CHAR_ENCODE;

    };



}

#endif
