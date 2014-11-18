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

		public: Audio(QString UID);

        public: Audio(Model::Audio& copy);
	};
}

#endif
