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

#ifndef __Controller__TreatmentThread_h__
#define __Controller__TreatmentThread_h__

#include <QList>
#include <QThread>

#include "src/Controller/Transcoder.h"
#include "src/Controller/Merger.h"
// #include "src/Controller/Exporter.h"
// #include "src/Controller/OCTDispatcher.h"
#include "src/Model/Project.h"

namespace Controller
{
	class Transcoder;
	class Merger;
	class Exporter;
	class OCTDispatcher;
	class TreatmentThread;
}
namespace Model
{
	class Project;
}

namespace Controller
{
    class TreatmentThread : public QObject
	{
        Q_OBJECT
        public:
            /**
             * @brief The associated transcoder controller.
             */
            Controller::Transcoder      *m_transcoder;

            /**
             * @brief The associated merger controller.
             */
            Controller::Merger          *m_merger;

            /**
             * @brief The associated exporter controller.
             */
            Controller::Exporter        *m_exporter;

            /**
             * @brief The associated projects.
             */
            QList<Model::Project*>      *m_projects;

            /**
             * @brief Constructor.
             * @param projects List of projects.
             * @param transcoder Selected transcoder controller.
             * @param merger Selected merger controller.
             * @param exporter Selected exporter controller.
             */
            TreatmentThread(QList<Model::Project*> *projects, Controller::Transcoder *transcoder, Controller::Merger *merger, Controller::Exporter *exporter);

            signals:
                void finished();


            public slots:

            /**
             * @brief This method start the treatement queue.
             */
            void startTreatment();

            /**
             * @brief This method pause the treatment queue.
             */
            void pauseTreatment();

            /**
             * @brief This method stop the treatment queue.
             */
            void stopTreatment();
	};
}

#endif
