#include <exception>
using namespace std;

#include "Model/File.h"
#include "Model/Data.h"

Model::File::File() {}

Model::File::File(QString filePath, QString info) {
    m_filePath = filePath;
    // m_name = info; ?
}

Model::File::File(const File& f) {
    m_name = f.m_name;
    m_filePath = f.m_filePath;
}

Model::File& Model::File::operator=(const File& f) {
    if ( this != &f ) {
        m_name = f.m_name;
        m_filePath = f.m_filePath;
    }
    return *this;
}

Model::File::~File() {}

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
