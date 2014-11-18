#include <exception>
using namespace std;

#ifndef __Model__Attachment_h__
#define __Model__Attachment_h__

#include <QString>
#include "Model/Serializable.h"
#include "Model/Serializable.h"


namespace Model
{
    class Serializable;
	class Attachment;
}

namespace Model
{
	class Attachment: public Model::Serializable
	{

        public:
            Attachment(QString filepath);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
