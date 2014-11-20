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
        private:
            static QMap<QString, Parameter *> m_staticParameters;


        public:
            Subtitle();
            Subtitle(QString uid);
            Subtitle(Subtitle& copy);
            Subtitle& operator=(const Subtitle& o);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
            virtual ~Subtitle();

            static Parameter *getStaticParameter(QString key);
            static void initStaticParameters();

	};
}

#endif
