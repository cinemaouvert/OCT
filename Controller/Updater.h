#include <exception>
using namespace std;

#ifndef __Controller__Updater_h__
#define __Controller__Updater_h__

// #include "Controller/OCTDispatcher.h"

namespace Controller
{
	class OCTDispatcher;
	class Updater;
}

namespace Controller
{
	class Updater
	{
		public: Controller::OCTDispatcher* m_updater;

		public: void PUT_OPP_S_UPDATER();
	};
}

#endif
