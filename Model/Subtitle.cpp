#include <exception>
using namespace std;

#include "Model/Subtitle.h"
#include "Model/Stream.h"

Model::Subtitle::Subtitle(){
    this->m_parameters = NULL;
}

Model::Subtitle::Subtitle(QString uid) {
    this->m_parameters = NULL;
    this->m_uID = uid;
}

Model::Subtitle::Subtitle(Model::Subtitle& copy) {
    this->m_uID = copy.m_uID;
    QMap<QString,Parameter*> *param(copy.m_parameters) ;
    this->m_parameters = param;
}

Model::Subtitle &Model::Subtitle::operator=(const Model::Subtitle &o)
{
    if(this != &o){
        this->m_uID = o.m_uID;
        QMap<QString,Parameter*> *param(o.m_parameters) ;
        this->m_parameters = param;
    }
    return *this;
}

ostream& Model::Subtitle::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Subtitle::operator << (istream& o){
    throw "Not yet implemented";
}

Model::Subtitle::~Subtitle()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}
