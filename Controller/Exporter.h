#include <exception>

using namespace std;

#ifndef __Controller__Exporter_h__
#define __Controller__Exporter_h__


#include <QString>

// #include "Controller/OCTDispatcher.h"
// #include "Model/Database.h"

namespace Controller
{
	class OCTDispatcher;
	class Exporter;
}
namespace Model
{
	class Database;
}

namespace Controller
{
	class Exporter
	{
		public: Controller::OCTDispatcher* m_exporter;
		public: Model::Database* m_unnamed_Database_;

		public: Exporter();

		public: QString createMagnetLink(QString filepath);

		public: bool sendXML(QString filepathXML, QString filepathMagnet);
	};
}

#endif
