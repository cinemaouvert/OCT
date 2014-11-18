#ifndef __Model__Information_h__
#define __Model__Information_h__

#include <QString>
#include "Model/Serializable.h"


namespace Model
{
	class Information;
    class Serializable;
}

namespace Model
{
    class Information : public Model::Serializable
	{
		private: QString m_name;
		private: QString m_value;

        public:
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
