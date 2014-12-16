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

#ifndef __Controller__Merger_h__
#define __Controller__Merger_h__

// #include "Controller/OCTDispatcher.h"
#include "Model/Project.h"
#include "Model/Attachment.h"

namespace Controller
{
	class OCTDispatcher;
	class Merger;
}
namespace Model
{
	class Project;
    class Attachment;
}

namespace Controller
{
	class Merger
    {


        public:
        QStringList addAttachment(const QString &name);
        QStringList setTitle(const QString &name);
        QStringList setOutputFile(const QString &name);
        QStringList setDefaultTrack(const QString &name);
            /**
             * @brief The associated merger.
             */
            Controller::OCTDispatcher* m_merger;

            /**
             * @brief Default constructor.
             */
            Merger();

            /**
             * @brief This method creates an XML file from project information.
             * @param project
             */
            void createXML(Model::Project *project);

            /**
             * @brief This method creates an MKV file from the current project.
             * @param project
             */
            void createMKVFile(Model::Project *project);





	};
}

#endif
