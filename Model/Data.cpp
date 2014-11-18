#include <exception>
using namespace std;

#include "Model/Data.h"
#include "Model/Stream.h"
#include "Model/Serializable.h"

Model::Data::Data() {
    m_string = "";
}

Model::Data::Data(QString string) {
    m_string = string;
}

Model::Data::Data(const Data& d) {
    m_string = d.m_string;
}

Model::Data& Model::Data::operator=(const Data& d) {
    if ( this != &d ) {
        m_string = d.m_string;
    }
    return *this;
}

Model::Data::~Data() {
    m_string = "";
}

bool Model::Data::hasToBeTranscoded() {
	throw "Not yet implemented";
}

QString Model::Data::generateCommandLine() {
	throw "Not yet implemented";
}

Model::Stream* Model::Data::getOldStream() {
    return m_oldStream;
}

ostream& Model::Data::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Data::operator << (istream& o){
    throw "Not yet implemented";
}

