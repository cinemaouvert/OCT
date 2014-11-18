#include <exception>
#include <QString>
using namespace std;

#ifndef __Model__Parameter_h__
#define __Model__Parameter_h__
#include "Model/Serializable.h"

namespace Model
{
	class Parameter;
}

namespace Model
{
    class Parameter : public Model::Serializable
	{
		private: QString m_command;
		private: QString m_type;
		private: QString m_description;
		private: QString m_value;

        public:
            Parameter();
            Parameter(QString cmd,QString type,QString desc,QString val);
            Parameter(Parameter& copy);
            Parameter& operator=(const Parameter& o);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
            virtual ~Parameter();
            QString description() const;
            void setDescription(const QString &description);
            QString value() const;
            void setValue(const QString &value);
            QString type() const;
            void setType(const QString &type);
            QString command() const;
            void setCommand(const QString &command);
    };
}

#endif
