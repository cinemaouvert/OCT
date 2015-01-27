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
#include <vector>
using namespace std;

#ifndef __Controller__OCTDispatcher_h__
#define __Controller__OCTDispatcher_h__

#include <QString>
#include <QList>
#include <QSettings>
#include <QObject>

// #include "src/Controller/StreamLoader.h"
// #include "src/Controller/Updater.h"
// #include "src/Controller/Merger.h"
// #include "src/Controller/Exporter.h"
// #include "src/Controller/TreatmentThread.h"
// #include "src/Controller/Transcoder.h"
#include "src/Model/Project.h"
#include "src/Model/Stream.h"
#include "src/Model/OCPMValidation.h"
#include "src/View/MainWindow.h"
// #include "src/View/MainWindow.h"

namespace Controller
{
	class StreamLoader;
	class Updater;
	class Merger;
	class Exporter;
	class TreatmentThread;
	class Transcoder;
	class OCTDispatcher;
}
namespace Model
{
	class Project;
    class OCPMValidation;
    class Stream;
}
namespace View
{
	class MainWindow;
}

namespace Controller
{
    /**
     * @brief Main controller which dispatches treatment between controllers.
     */
    class OCTDispatcher : public QObject
	{

        Q_OBJECT

        private:
            /**
             * @brief Thread to start treatment
             */
            QThread                     *m_startTreatmentThread;

            /**
             * @brief The associated current project.
             */
            Model::Project              *m_currentProject;

            /**
             * @brief The associated interface.
             */
            View::MainWindow            *m_mainWindow;

            /**
             * @brief The associated settings.
             */
            QSettings                   *m_settings;

            /**
             * @brief The associated stream loader.
             */
            Controller::StreamLoader    *m_streamLoader;

            /**
             * @brief The associated updater.
             */
            Controller::Updater         *m_updater;

            /**
             * @brief The associated merger.
             */
            Controller::Merger          *m_merger;

            /**
             * @brief The associated exporter.
             */
            Controller::Exporter        *m_exporter;

            /**
             * @brief The associated list of project.
             */
            QList<Model::Project*>      *m_projects;

            /**
             * @brief The associated treatment thread controller.
             */
            Controller::TreatmentThread *m_treatmentThread;

            /**
             * @brief The associated transcoder.
             */
            Controller::Transcoder      *m_transcoder;

            /**
             * @brief The movie struct.
             */
            QStringList *m_informationMovieStruct;

            /**
              * @brief the model representation of the validation
              */
            Model::OCPMValidation *m_OCPMvalidation;


        public:
            /**
             * @brief Default constructor.
             */
            OCTDispatcher();

            /**
              * @brief The destructor
              * */
            ~OCTDispatcher();

            /**
             * @brief Add a file to the current project.
             * @param filePath
             */
            void addFile(QString filePath);

            /**
             * @brief remove a file to the current project.
             * @param filePath
             */
            void removeFile(QString filePath);

            /**
             * @brief Save the current project.
             */
            void save();

            /**
             * @brief Load a previously saved project.
             */
            void load();

            /**
             * @brief Start the transcoding process.
             */
            void startTreatment();

            /**
             * @brief Pause the transcoding process.
             */
            void pauseTreatment();

            /**
             * @brief Restart the transcoding process.
             */
            void restartTreatment();

            /**
             * @brief Stop the transcoding process.
             */
            void stopTreatment();

            /**
             * @brief Add a project to the traitement queue.
             */
            void addToQueue();

            /**
             * @brief Check for software updates.
             */
            void checkForUpdate();

            /**
             * @brief Add a setting to the current set of settings.
             * @param key
             * @param value
             */
            void addSetting(const QString &key, const QVariant &value);

            /**
             * @brief Get a setting by its key.
             * @param key
             * @return The QVariant setting value.
             */
            QVariant getSetting(QString key);

            /**
             * @brief Initialize a given setting.
             * @param key
             * @param value
             */
            void initSetting(const QString &key, const QVariant &value);

            /**
             * @brief Initialize entire set of settings.
             */
            void initSettings();


            Model::Project *getCurrentProject() const;

            QList<Model::Project*> *getProjects();

            Model::OCPMValidation *getOCPMValidation();

            void setCurrentProjectIndex(int index);

            void duplicateProject(int index);

            TreatmentThread *getTreatmentThread();


            QStringList *informationMovieStruct() const;

    public slots:
            void treatProjectNameChanged(QString newName);
            bool checkProjectValidation();
            bool checkStreamValidation(Model::Stream *stream);
            bool checkInformationValidation();

    };
}

#endif
