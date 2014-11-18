#include <exception>
#include <vector>
using namespace std;

#include "Controller/TreatmentThread.h"
#include "Controller/Transcoder.h"
#include "Controller/Merger.h"
#include "Controller/Exporter.h"
#include "Controller/OCTDispatcher.h"
#include "Model/Project.h"

Controller::TreatmentThread::TreatmentThread(QList<Model::Project*> projects, Controller::Transcoder transcoder, Controller::Merger merger) {
}

void Controller::TreatmentThread::startTreatment() {
	throw "Not yet implemented";
}

void Controller::TreatmentThread::pauseTreatment() {
	throw "Not yet implemented";
}

void Controller::TreatmentThread::stopTreatment() {
	throw "Not yet implemented";
}

