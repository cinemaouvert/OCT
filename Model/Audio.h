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
#include <qdom.h>
using namespace std;

#ifndef __Model__Audio_h__
#define __Model__Audio_h__

#include <QString>
#include "Model/Stream.h"


namespace Model
{
	// class Stream;
    class Audio;
}

namespace Model
{
	class Audio: public Model::Stream
    {

        private:
            static QMap<QString, Parameter *> m_staticParameters;

            friend QDataStream & operator <<(QDataStream  &out, const Audio  &valeur);
            friend QDataStream & operator <<(QDataStream  &out, const Audio  *valeur);
            friend QDataStream & operator >>(QDataStream  &in, Audio  &valeur);

        public:
            /**
             * @brief Default constructor.
             */
            Audio();

            /**
             * @brief Constructor.
             * @param stream Associated stream.
             */
            Audio(QDomNode stream);

            /**
             * @brief Constructor.
             * @param UID
             */
            Audio(QString UID);

            /**
             * @brief Copy constructor.
             * @param a The Audio object to copy.
             */
            Audio(const Audio& a);

            /**
             * @brief The affectation operator.
             * @param a The Audio object to affect.
             * @return The current Audio object modified.
             */
            Audio& operator=(const Audio& a);

            /**
             * @brief Destructor.
             */
            virtual ~Audio();


            static Parameter *getStaticParameter(QString key);
            static void initStaticParameters();

            static void initMetaType();

	};
    QDataStream & operator <<(QDataStream  &out, const Model::Audio  &valeur);
    QDataStream & operator <<(QDataStream  &out, const Model::Audio  *valeur);
    QDataStream & operator >>(QDataStream  &in, Model::Audio  &valeur);
}
Q_DECLARE_METATYPE(Model::Audio)


#endif
