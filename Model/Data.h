#include <exception>
using namespace std;

#ifndef __Model__Data_h__
#define __Model__Data_h__

#include <QString>
#include "Model/Stream.h"
#include "Model/Serializable.h"

namespace Model
{
	class Stream;
	// class Serializable;
	class Data;
}

namespace Model
{
	class Data: public Model::Serializable
	{
		public: Model::Stream* m__;

		public: Data(QString QString);

		public: bool hasToBeTranscoded();

		public: QString generateCommandLine();

        public: Model::Stream* getOldStream();
	};
}

#endif
