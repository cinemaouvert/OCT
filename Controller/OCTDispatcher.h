#include <exception>
#include <vector>
using namespace std;

#ifndef __Controller__OCTDispatcher_h__
#define __Controller__OCTDispatcher_h__

#include <QString>
#include <QList>
#include <QSettings>

// #include "Controller/StreamLoader.h"
// #include "Controller/Updater.h"
// #include "Controller/Merger.h"
// #include "Controller/Exporter.h"
// #include "Controller/TreatmentThread.h"
// #include "Controller/Transcoder.h"
#include "Model/Project.h"
#include "View/MainWindow.h"
// #include "View/MainWindow.h"

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
}
namespace View
{
	class MainWindow;
}

namespace Controller
{
	class OCTDispatcher
	{
        private:
            Model::Project              *m_currentProject;
            View::MainWindow            *m_mainWindow;
            QSettings                   *m_settings;
            Controller::StreamLoader    *m_streamLoader;
            Controller::Updater         *m_updater;
            Controller::Merger          *m_merger;
            Controller::Exporter        *m_exporter;
            QList<Model::Project*>      *m_projects;
            Controller::TreatmentThread *m_treatmentThread;
            Controller::Transcoder      *m_transcoder;

        public:
            OCTDispatcher();
            void addFile(QString filePath);
            void save();
            void load();
            void startTreatment();
            void pauseTreatment();
            void restartTreatment();
            void stopTreatment();
            void addToQueue();
            void checkForUpdate();
            void addSetting(const QString &key, const QVariant &value);
            QVariant getSetting(QString key);
            void initSetting(const QString &key, const QVariant &value);
            void initSettings();
	};
}

#endif
