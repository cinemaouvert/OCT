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
            void setValue(QString value);
            Parameter();
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
