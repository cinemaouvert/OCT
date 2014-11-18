#include <exception>
using namespace std;

#include "Model/File.h"
#include "Model/Data.h"

void Model::File::FIle(QString filePath, QString info) {
	throw "Not yet implemented";
}

QList<Model::Data*> Model::File::getDatas() {
	throw "Not yet implemented";
}

QString Model::File::getName() {
	return this->m_name;
}

