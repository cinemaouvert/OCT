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
    {//test commit
        private :
            Model::Stream* m_newStream;
            Model::Stream* m_oldStream;
        public:
            Data(QString QString);
            bool hasToBeTranscoded();
            QString generateCommandLine();
            Model::Stream* getOldStream();
	};
}

#endif
