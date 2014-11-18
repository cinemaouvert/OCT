#include <exception>
using namespace std;

#ifndef __Controller__StreamLoader_h__
#define __Controller__StreamLoader_h__

#include <QString>
#include <QList>


// #include "Controller/OCTDispatcher.h"
#include "Model/Data.h"

namespace Controller
{
	class OCTDispatcher;
	class StreamLoader;
}
namespace Model
{
	class Data;
}

namespace Controller
{
	class StreamLoader
	{
		public: Controller::OCTDispatcher* m_streamLoader;

        public: QList<QString> getDistinctStreams(QString ffmpegStream);

        public: Model::Data* parseStreams(QString streamToParse);
	};
}

#endif
