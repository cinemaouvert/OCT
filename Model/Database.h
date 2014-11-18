#include <exception>
using namespace std;

#include <QString>
#ifndef __Model__Database_h__
#define __Model__Database_h__

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

		public: Database();

		public: int sendRequest(QString request);
	};
}

#endif
