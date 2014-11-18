#include <exception>
#include <vector>
using namespace std;

#include "Controller/OCTDispatcher.h"
#include "Controller/StreamLoader.h"
#include "Controller/Updater.h"
#include "Controller/Merger.h"
#include "Controller/Exporter.h"
#include "Controller/TreatmentThread.h"
#include "Controller/Transcoder.h"
#include "Model/Project.h"
#include "View/MainWindow.h"

Controller::OCTDispatcher::OCTDispatcher() : m_currentProject(NULL), m_mainWindow(NULL) {
    m_currentProject = new Model::Project();
    m_mainWindow = new View::MainWindow(0,this);
    m_mainWindow->show();
}

void Controller::OCTDispatcher::addFile(QString filePath) {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::save() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::load() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::startTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::pauseTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::restartTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::stopTreatment() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::addToQueue() {
	throw "Not yet implemented";
}

void Controller::OCTDispatcher::checkForUpdate() {
	throw "Not yet implemented";
}

