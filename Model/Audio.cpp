#include <exception>
using namespace std;

#include "Model/Audio.h"
#include "Model/Stream.h"

Model::Audio::Audio() {
    m_uID = "";
    this->m_parameters = NULL;
}

Model::Audio::Audio(QString uID) {
    m_uID = uID;
    this->m_parameters = NULL;
}

Model::Audio::Audio(const Audio& a) {
    m_uID = a.m_uID;
    QMap<QString,Parameter*> *param(a.m_parameters) ;
    this->m_parameters = param;
}

Model::Audio& Model::Audio::operator=(const Audio& a) {
    if ( this != &a ) {
        m_uID = a.m_uID;
        QMap<QString,Parameter*> *param(a.m_parameters) ;
        this->m_parameters = param;
    }
    return *this;
}

Model::Audio::~Audio() {
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

ostream& Model::Audio::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Audio::operator << (istream& o){
    throw "Not yet implemented";
}
