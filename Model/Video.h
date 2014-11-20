#include <exception>
using namespace std;

#ifndef __Model__Video_h__
#define __Model__Video_h__

#include <QString>
#include <qdom.h>

#include "Model/Stream.h"

namespace Model
{
	// class Stream;
	class Video;
}

namespace Model
{
	class Video: public Model::Stream
	{
        private:
            QString m_additionalCommand;
            static QMap<QString, Parameter *> m_staticParameters;


        public:
            Video();
            Video(QDomNode stream);
            Video(QString uid);
            Video(const Video& copy);
            Video& operator=(const Video& o);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
            virtual ~Video();

            static Parameter *getStaticParameter(QString key);
            static void initStaticParameters();

	};
}

#endif
