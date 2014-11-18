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
        private:
            QString m_name;
            QString m_value;

        public:
            Information();
            Information(QString name, QString value);
            Information(const Information& i);
            Information& operator=(const Information& i);
            ~Information();

            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
