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

QStringList *Model::Stream::getCommand()
{
    QStringList *myStringList = new QStringList();

    for(int i = 0; i < this->m_parameters->size()-1;i++){
       Parameter *param = this->m_parameters->values().at(i);
       QString value = param->value();
       while(param->noSpaceForNext()){
           if(i < this->m_parameters->size()-1 )
            i++;
            param = this->m_parameters->values().at(i);
            value+=param->value();
       }
       *myStringList << param->command().arg(this->getUID()) << value ;
    }
    return myStringList;
}

Model::Stream::~Stream()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

