#include <exception>
using namespace std;

#ifndef __Model__Audio_h__
#define __Model__Audio_h__

#include <QString>
#include "Model/Stream.h"


namespace Model
{
	// class Stream;
    class Audio;
}

namespace Model
{
	class Audio: public Model::Stream
	{

        public:
            Audio(QString UID);
            Audio(Model::Audio& copy);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
