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

#ifndef __Model__Database_h__
#define __Model__Database_h__
#include <QString>
#include <QMap>

namespace Model
{
	class Database;
}

namespace Model
{
    /**
     * @brief The Database model class
     */
	class Database
    {
        private:
            /**
             * @brief Member user key.
             */
            QString m_userKey;

            /**
             * @brief Member value depot associated with the key.
             */
            QString m_depot;

            /**
             * @brief create StringList from json.
             */
            static QStringList *createStruct(QByteArray movieStruct);

            /**
             * @brief create Map from json.
             */
            QMap<QString, QString> *createMovie(QByteArray movieStruct);
    public:
            /**
             * @brief Constructor.
             * @param userKey The user key to be binded.
             * @param depot The depot value to be binded with the key.
             */
            Database(QString userKey, QString depot);

            /**
             * @brief Copy constructor.
             * @param db The Database object to copy.
             */
            Database(Database const& db);

            /**
             * @brief Affectation operator
             * @param db The Database object to modify current object.
             * @return The current Database object modified.
             */
            Database& operator=(Database const& db);

            /**
             * @brief Destructor.
             */
            virtual ~Database();

            /**
             * @brief This method sends a json request.
             * @param jsonString The json request to be send.
             * @return The result of the sending.
             */
            int sendRequest(QByteArray jsonString);

            /**
             * @brief Accessor on the member depot.
             * @return The depot member.
             */
            QString depot() const;

            /**
             * @brief Accessor on the member userKey.
             * @return The userKey member.
             */
            QString userKey() const;

            /**
             * @brief This static method to get a movie struct.
             * @return StringList of keys json.
             */
            static QStringList* getMovieStruct();

            /**
             * @brief This method get movie by a title
             * @param jsonString The json request to be send.
             * @return The result of the sending.
             */
            QMap<QString, QString> *getMovieByTitle(QString title);
    };
}

#endif
