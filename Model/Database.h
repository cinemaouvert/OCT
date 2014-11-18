#include <exception>
using namespace std;

#include <QString>
#ifndef __Model__Database_h__
#define __Model__Database_h__

// #include "Controller/Exporter.h"

namespace Controller
{
	class Exporter;
}
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
		public: Controller::Exporter* m_unnamed_Exporter_;

		public: Database();

		public: int sendRequest(QString request);
	};
}

#endif
