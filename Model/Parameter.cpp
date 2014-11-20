#include <exception>
using namespace std;

#include "Model/Parameter.h"


QString Model::Parameter::description() const
{
    return this->m_description;
}

QString Model::Parameter::value() const
{
    return m_value;
}

void Model::Parameter::setValue(const QString &value)
{
    this->m_value = this->m_value.arg(value);
}

QString Model::Parameter::command() const
{
    return m_command;
}

QString Model::Parameter::commandAndValue() const
{
    return m_command +" " +m_value;
}

void Model::Parameter::SetNoSpaceForNext(bool val)
{
    this->m_noSpaceForNext = val;
}

bool Model::Parameter::noSpaceForNext()
{
    return m_noSpaceForNext;
}


Model::Parameter::Parameter() {
    this->m_noSpaceForNext = false;

}

Model::Parameter::Parameter(QString cmd, QString desc, QString val)
{
    this->m_command = cmd;
    this->m_description = desc;
    this->m_value = val;
    this->m_noSpaceForNext = false;

}

Model::Parameter::Parameter(Model::Parameter &copy)
{
    this->m_command = copy.m_command;
    this->m_description = copy.m_description;
    this->m_value = copy.m_value;
    this->m_noSpaceForNext = copy.m_noSpaceForNext;

}

Model::Parameter &Model::Parameter::operator=(const Model::Parameter &o)
{
    if(this != &o){
        this->m_command = o.m_command;
        this->m_description = o.m_description;
        this->m_value = o.m_value;
        this->m_noSpaceForNext = o.m_noSpaceForNext;
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
