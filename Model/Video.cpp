#include <exception>
using namespace std;

#include "Model/Video.h"
#include "Model/Stream.h"

#include <QDebug>

Model::Video::Video(){
    this->m_parameters = new QMap<QString,Parameter*>();



}

Model::Video::Video(QString uid){
    this->m_parameters = new QMap<QString,Parameter*>();



    this->m_uID = uid;
}

Model::Video::Video(const Model::Video & copy){
    this->m_uID = copy.m_uID;
    this->m_additionalCommand = copy.m_additionalCommand;
    this->m_parameters = new QMap<QString,Parameter*>(*(copy.m_parameters));
}

Model::Video &Model::Video::Video::operator=(const Model::Video &o)
{
    if(this != &o){
        this->m_uID = o.m_uID;
        this->m_additionalCommand = o.m_additionalCommand;
        QMap<QString,Parameter*> *param(o.m_parameters) ;
        this->m_parameters = param;
    }
    return *this;
}

ostream& Model::Video::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Video::operator << (istream& o){
    throw "Not yet implemented";
}

Model::Video::~Video()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}
