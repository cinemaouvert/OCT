#include <exception>
#include <vector>
using namespace std;

#include "Model/Project.h"
#include "Model/Attachment.h"
#include "Model/Information.h"
#include "Model/Serializable.h"

Model::Project::Project() {
}

void Model::Project::getFiles() {
	throw "Not yet implemented";
}

void Model::Project::load() {
	throw "Not yet implemented";
}

void Model::Project::save() {
	throw "Not yet implemented";
}

QString Model::Project::getXML() {
	throw "Not yet implemented";
}

void Model::Project::setXML(QString filepath) {
	throw "Not yet implemented";
}

QList<Model::Information*> Model::Project::getInformations() {
	throw "Not yet implemented";
}

bool Model::Project::getCreateMagnet() {
	return this->m_createMagnet;
}

void Model::Project::setCreateMagnet(bool hasToCreateMagnet) {
	throw "Not yet implemented";
}

