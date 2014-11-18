#include <exception>
using namespace std;

#include "Model/File.h"
#include "Model/Data.h"

Model::File::File(QString filePath, QString info) {
	throw "Not yet implemented";
}

QList<Model::Data*> Model::File::getDatas() {
	throw "Not yet implemented";
}

QString Model::File::getName() {
	return this->m_name;
}

ostream& Model::File::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::File::operator << (istream& o){
    throw "Not yet implemented";
}
