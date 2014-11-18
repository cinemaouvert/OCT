#include <exception>
using namespace std;

#include "Model/Stream.h"
#include "Model/Data.h"
#include "Model/Serializable.h"

void Model::Stream::setParameter(QString name, QString value) {
	throw "Not yet implemented";
}

QString Model::Stream::getUID() {
	return this->m_uID;
}

