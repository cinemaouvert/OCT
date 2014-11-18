#include <exception>
using namespace std;

#ifndef __Model__Subtitle_h__
#define __Model__Subtitle_h__

#include <QString>

#include "Model/Stream.h"

namespace Model
{
	// class Stream;
	class Subtitle;
}

namespace Model
{
	class Subtitle: public Model::Stream
	{

		public: Subtitle(QString UID);

        public: Subtitle(Model::Subtitle& copy);
	};
}

#endif
