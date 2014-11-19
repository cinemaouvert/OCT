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
        private:
            QString m_command;
            QString m_description;
            QString m_value;
            bool m_noSpaceForNext;

        public:
            Parameter();
            Parameter(QString cmd,QString desc,QString val);
            Parameter(Parameter& copy);
            Parameter& operator=(const Parameter& o);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
            virtual ~Parameter();

            void setValue(const QString &value);

            QString description() const;
            QString value() const;
            QString command() const;
            QString commandAndValue() const;

            void SetNoSpaceForNext(bool val = true);

    };
}

#endif
