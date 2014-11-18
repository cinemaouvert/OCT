#include <exception>

using namespace std;

#ifndef __Controller__Transcoder_h__
#define __Controller__Transcoder_h__


#include <QString>
// #include "Controller/OCTDispatcher.h"

namespace Controller
{
	class OCTDispatcher;
	class Transcoder;
}

namespace Controller
{
	class Transcoder
	{
		public: Controller::OCTDispatcher* m_transcoder;

		public: Transcoder();

		public: QString getInfo(QString filePath);

		public: QString transcode(QString command);
	};
}

#endif
