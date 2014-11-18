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
        private :
            QString m_string;

            Model::Stream* m_newStream;
            Model::Stream* m_oldStream;
        public:
            Data();
            Data(QString string);
            Data(Data const& d);
            Data& operator=(Data const& d);
            virtual ~Data();

            bool hasToBeTranscoded();
            QString generateCommandLine();
            Model::Stream* getOldStream();

            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
