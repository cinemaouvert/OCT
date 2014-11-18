#include <exception>
using namespace std;

#include "Model/Parameter.h"


QString Model::Parameter::description() const
{
    return this->m_description;
}

void Model::Parameter::setDescription(const QString &description)
{
    this->m_description = description;
}

QString Model::Parameter::value() const
{
    return m_value;
}

void Model::Parameter::setValue(const QString &value)
{
    this->m_value = value;
}

QString Model::Parameter::type() const
{
    return m_type;
}

void Model::Parameter::setType(const QString &type)
{
    this->m_type = type;
}

QString Model::Parameter::command() const
{
    return m_command;
}

void Model::Parameter::setCommand(const QString &command)
{
    this->m_command = command;
}
Model::Parameter::Parameter() {
}

Model::Parameter::Parameter(QString cmd, QString type, QString desc, QString val)
{
    this->m_command = cmd;
    this->m_description = desc;
    this->m_type = type;
    this->m_value = val;
}

Model::Parameter::Parameter(Model::Parameter &copy)
{
    this->m_command = copy.m_command;
    this->m_description = copy.m_description;
    this->m_type = copy.m_type;
    this->m_value = copy.m_value;
}

Model::Parameter &Model::Parameter::operator=(const Model::Parameter &o)
{
    if(this != &o){
        this->m_command = o.m_command;
        this->m_description = o.m_description;
        this->m_type = o.m_type;
        this->m_value = o.m_value;
    }
    return *this;
}


ostream& Model::Parameter::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Parameter::operator << (istream& o){
    throw "Not yet implemented";
}

Model::Parameter::~Parameter()
{

}
