
#include "Model/Information.h"

Model::Information::Information() {}

Model::Information::Information(QString name, QString value) {
    m_name = name;
    m_value = value;
}

Model::Information::Information(const Information &i) {
    m_name = i.m_name;
    m_value = i.m_value;
}

Model::Information& Model::Information::operator=(const Model::Information& i) {
    if ( this != &i ) {
        m_name = i.m_name;
        m_value = i.m_value;
    }
    return *this;
}

Model::Information::~Information() {}

ostream& Model::Information::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Information::operator << (istream& o){
    throw "Not yet implemented";
}
