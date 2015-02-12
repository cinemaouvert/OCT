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

#ifndef __Controller__Exporter_h__
#define __Controller__Exporter_h__


#include <QString>

// #include "src/Controller/OCTDispatcher.h"
// #include "src/Model/Database.h"

namespace Controller
{
	class OCTDispatcher;
	class Exporter;
}
namespace Model
{
	class Database;
    class Project;
}

namespace Controller
{
    /**
     * @brief The Exporter class
     *
     * This class is in charge to connect to the remote database and create
     * associated torrent file and magnet link.
     */
	class Exporter
    {
        private:
            /**
             * @brief This method creates a torrent file to create a magnet link.
             * @param filepath The filepath to the torrent file.
             * @param nomTorrent The torrent file name.
             * @return The final filepath to the torrent file created.
             */
            QString createTorrentFile(QString filepath, QString nomTorrent);

        public:
            /**
             * @brief The associated database.
             */
            Model::Database* m_Database;

            /**
             * @brief Constructor to connect database
             */
            Exporter(QString userKey, QString depot);

            /**
             * @brief Destructor.
             */
            ~Exporter();

            /**
             * @brief This method creates a magnet link to bind a local file in the database.
             * @param filepath
             * @return
             */
            QString createMagnetLink(QString filepath, QString nomTorrent);

            /**
             * @brief This method sends information in json to the database.
             * @param Project The associated project.
             * @param url_magnet The associated magnet link url.
             * @return 1 if ok, 0 else.
             */
            bool sendInformationsToJSON(Model::Project* project, QString url_magnet);

            /**
             * @brief Retrieve informations under a QStringList.
             * @return The QStringList containing the associated informations.
             */
            static QStringList* getInformations();
    };
}

#endif
