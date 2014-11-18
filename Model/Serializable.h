#include <exception>
using namespace std;

#ifndef __Model__Serializable_h__
#define __Model__Serializable_h__

#include <ostream>
#include <istream>
namespace Model
{
	class Serializable;
}

namespace Model
{
    class Serializable
	{

        public:
            virtual ostream& operator >> (ostream& o) = 0;
            virtual istream& operator << (istream& o) = 0;
    };
}

#endif
