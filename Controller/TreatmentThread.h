#include <exception>
using namespace std;

#ifndef __Controller__TreatmentThread_h__
#define __Controller__TreatmentThread_h__

#include <QList>

#include "Controller/Transcoder.h"
#include "Controller/Merger.h"
// #include "Controller/Exporter.h"
// #include "Controller/OCTDispatcher.h"
#include "Model/Project.h"

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
	class TreatmentThread
	{
        public: Controller::Transcoder      *m_transcoder;
        public: Controller::Merger          *m_merger;
        public: Controller::Exporter        *m_exporter;
        public: QList<Model::Project*>      *m_projects;

    public: TreatmentThread(QList<Model::Project*> *projects, Controller::Transcoder *transcoder, Controller::Merger *merger, Controller::Exporter *exporter);

		public: void startTreatment();

		public: void pauseTreatment();

		public: void stopTreatment();
	};
}

#endif
