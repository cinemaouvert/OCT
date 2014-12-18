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

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QMap>
#include "Parameter.h"

namespace Model {
    class Parameter;
    class Parameters;
}

namespace Model {
    class Parameters
    {
        private:
            /**
             * @brief List of audio parameters.
             */
            static QMap<QString, Parameter *> m_audioParameters;

            /**
             * @brief List of video parameters.
             */
            static QMap<QString, Parameter *> m_videoParameters;

            /**
             * @brief List of subtitle parameters.
             */
            static QMap<QString, Parameter *> m_subtitleParameters;

        public:
            /**
             * @brief Accessor on the video parameters.
             * @param key Key associated with the searched parameter.
             * @return The parameter associated with the Key.
             */
            static Parameter *getVideoParameter(QString key);

            /**
             * @brief Accessor on the audio parameters.
             * @param key Key associated with the searched parameter.
             * @return The parameter associated with the Key.
             */
            static Parameter *getAudioParameter(QString key);

            /**
             * @brief Accessor on the subtitle parameters.
             * @param key Key associated with the searched parameter.
             * @return The parameter associated with the key.
             */
            static Parameter *getSubtitleParameter(QString key);

            /**
             * @brief Initialize the lists of parameters.
             */
            static void init();
    };
}
#endif // PARAMETERS_H
