#include <exception>
using namespace std;


#ifndef __Model__Database_h__
#define __Model__Database_h__
#include "Model/Serializable.h"
#include <QString>
namespace Model
{
	class Database;
    class Serializable;
}

namespace Model
{
    class Database : public Model::Serializable
	{
        private:
            QString m_userKey;
            QString m_depot;

        public:
            Database();
            int sendRequest(QString request);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
