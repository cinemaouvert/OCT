#include <exception>
using namespace std;

#include "Model/Stream.h"
#include "Model/Data.h"
#include "Model/Serializable.h"

void Model::Stream::setParameter(QString name, Parameter *value) {
    this->m_parameters->insert(name,value);
}

QString Model::Stream::getUID() {
    return this->m_uID;
}

Model::Stream::~Stream()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

