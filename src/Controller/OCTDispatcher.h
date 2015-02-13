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
    class Audio;
    class Video;
    class Subtitle;
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
             * @brief The associated main window interface.
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
             * @brief The associated list of projects.
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
              * @brief The model representation of the validation
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
            void save(QString path);

            /**
             * @brief Load a previously saved project.
             */
            void load(QString path);

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
             * @param key The associated key setting.
             * @param value The associated value to the key.
             */
            void addSetting(const QString &key, const QVariant &value);

            /**
             * @brief Get a setting by its key.
             * @param key The key.
             * @return The QVariant setting value.
             */
            QVariant getSetting(QString key);

            /**
             * @brief Initialize a given setting.
             * @param key The associated key setting.
             * @param value The associated value to the key.
             */
            void initSetting(const QString &key, const QVariant &value);

            /**
             * @brief Initialize entire set of settings.
             */
            void initSettings();

            /**
             * @brief getCurrentProject Accessor on the current project member.
             * @return The current project.
             */
            Model::Project *getCurrentProject() const;

            /**
             * @brief getProjects Accessor on the projects member.
             * @return The projects contained in the dispatcher.
             */
            QList<Model::Project*> *getProjects();

            /**
             * @brief getOCPMValidation Accessor on the OCPMValidation member.
             * @return The OCPMValidation member of the current project.
             */
            Model::OCPMValidation *getOCPMValidation();

            /**
             * @brief setCurrentProjectIndex Mutator to select the current project.
             *
             * This method allows to specify the current project within the set
             * of projects contained in the dispatcher.
             * @param index The index of the project to set as current project.
             */
            void setCurrentProjectIndex(int index);

            /**
             * @brief duplicateProject Duplicate the project designed by its index.
             *
             * Duplicate the project designed by its index within the set of project
             * contained in the dispatcher.
             * @param index The index of the project to duplicate.
             */
            void duplicateProject(int index);

            /**
             * @brief getTreatmentThread Accessor on the treatment thread member.
             * @return The treatment thread member of the dispatcher.
             */
            TreatmentThread *getTreatmentThread();

            /**
             * @brief informationMovieStruct Accessor on the movie informations.
             *
             * Accessor on the movie information structure contained in the
             * dispatcher.
             * @return The associated information as a QStringList.
             */
            QStringList *informationMovieStruct() const;

            /**
             * @brief customMessageHandler Custom message handler.
             * @param type Type of the message.
             * @param context Context of the message.
             * @param msg Message.
             */
            static void customMessageHandler(QtMsgType type, const QMessageLogContext &context,const QString& msg);

            void getInformations(QString nameMovie);
    public slots:
            /**
             * @brief treatProjectNameChanged Slot queried when the project name has changed.
             * @param newName The new project name.
             */
            void treatProjectNameChanged(QString newName);

            /**
             * @brief checkProjectValidation Check whether the project is OCPM valid or not.
             * @return Whether the project is OCPM valid or not.
             */
            bool checkProjectValidation();

            /**
             * @brief checkStreamValidation Check whether the stream is OCPM valid or not.
             * @param stream The stream that is to be checked.
             * @return Whether the stream is OCPM valid or not.
             */
            bool checkStreamValidation(Model::Stream *stream);

            /**
             * @brief checkInformationValidation Check whether the informations are OCPM valid or not.
             * @return Whether the informations are OCPM valid or not.
             */
            int checkInformationValidation();

            /**
             * @brief checkPosterValidation Check whether the poster is OCPM valid or not.
             * @return Whether the poster is OCPM valid.
             */
            bool checkPosterValidation();

            /**
             * @brief parameterChanged Slot registering any interface's parameter modification.
             * @param file The file affected by the modification.
             * @param stream The stream affected by the modification.
             * @param parameterName The parameter's name that has been changed.
             * @param value The new value associated with the parameter.
             */
            void parameterChanged(Model::File *file,Model::Stream *stream,QString parameterName, QString value);

            /**
             * @brief parameterChangedMKV Slot registering any MKV's parameter modification.
             * @param p
             * @param file The file affected by the modification.
             * @param stream The stream affected by the modification.
             * @param value The new value associated with the parameter.
             */
            void parameterChangedMKV(int p, Model::File *file,Model::Stream *stream, QString value);

    };
}

#endif
