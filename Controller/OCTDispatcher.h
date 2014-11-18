#include <exception>
#include <vector>
using namespace std;

#ifndef __Controller__OCTDispatcher_h__
#define __Controller__OCTDispatcher_h__

#include <QString>
#include <QList>

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
            Model::Project *m_currentProject;
            View::MainWindow *m_mainWindow;

		public: Controller::StreamLoader* m_streamLoader;
		public: Controller::Updater* m_updater;
		public: Controller::Merger* m_merger;
		public: Controller::Exporter* m_exporter;
		public: View::MainWindow* m_unnamed_MainWindow_;
        public: QList<Model::Project*> m_projects;
		public: Controller::TreatmentThread* m_unnamed_TreatmentThread_;
		public: Controller::Transcoder* m_transcoder;

		public: OCTDispatcher();

        public: void addFile(QString filePath);

		public: void save();

		public: void load();

		public: void startTreatment();

		public: void pauseTreatment();

		public: void restartTreatment();

		public: void stopTreatment();

		public: void addToQueue();

		public: void checkForUpdate();
	};
}

#endif
