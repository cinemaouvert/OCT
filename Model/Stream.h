#include <exception>
using namespace std;

#ifndef __Model__Stream_h__
#define __Model__Stream_h__

#include <QString>
#include <QMap>

// #include "Model/Data.h"
#include "Model/Parameter.h"
#include "Model/Serializable.h"

namespace Model
{
	// class Serializable;
	class Stream;
    class Parameter;
}

namespace Model
{
    class Stream: public Model::Serializable
	{
        protected:
            QString m_uID;
            QMap<QString,Parameter> m_parameters;
        public:
            virtual void setParameter(QString name, QString value) = 0;
            virtual QString getUID() = 0;
	};
}

#endif
