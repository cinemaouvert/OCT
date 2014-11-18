#include <exception>
using namespace std;

#include "Model/Data.h"
#include "Model/Stream.h"
#include "Model/Serializable.h"

Model::Data::Data(QString QString) {
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

