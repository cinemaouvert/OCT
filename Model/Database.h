#include <exception>
using namespace std;

#ifndef __Model__Database_h__
#define __Model__Database_h__
#include <QString>

namespace Model
{
	class Database;
}

namespace Model
{
	class Database
	{
		private: QString m_userKey;
        private: QString m_depot;

        public:
            Database(QString userKey, QString depot);
            Database(Database const& db);
            Database& operator=(Database const& db);
            virtual ~Database();

            int sendRequest(QByteArray jsonString);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);

	};
}

#endif
