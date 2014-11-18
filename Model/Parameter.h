#include <exception>
#include <QString>
using namespace std;

#ifndef __Model__Parameter_h__
#define __Model__Parameter_h__

namespace Model
{
	class Parameter;
}

namespace Model
{
	class Parameter
	{
		private: QString m_command;
		private: QString m_type;
		private: QString m_description;
		private: QString m_value;

		public: void setValue(QString value);

		public: Parameter();
	};
}

#endif
