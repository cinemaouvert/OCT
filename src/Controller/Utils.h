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
#include <qstring.h>

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief The Utils class gather utilitary methods.
 */
class Utils
{
public:
    /**
     * @brief This method converts a given fraction into an appropriate number.
     * @param var The input fraction to process.
     * @return The converted result.
     */
    static QString convertFract(QString var);

    /**
     * @brief This method converts a given value from bps to Kbps.
     * @param var The input value in bps to process.
     * @return The converted result in Kbps.
     */
    static QString bpsToKbps(QString var);

    /**
     * @brief This method compute the sha1 code from a given file.
     * @param pathFile The path of the file to process.
     * @return The sha1 value of the given file.
     */
    static QString sha1File(QString pathFile);

    /**
     * @brief This method compute the md5 code from a given file.
     * @param pathFile The path of the file to process.
     * @return The md5 value of the given file.
     */
    static QString md5File(QString pathFile);

private:
    /**
     * @brief This method convert a given file into a QByteArray.
     * @param pathFile The path of the file to process.
     * @return The converted result as a QByteArray.
     */
    static QByteArray readAllFile(QString pathFile);
};

#endif // UTILS_H
