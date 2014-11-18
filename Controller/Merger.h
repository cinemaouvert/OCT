#include <exception>

using namespace std;

#ifndef __Controller__Merger_h__
#define __Controller__Merger_h__

// #include "Controller/OCTDispatcher.h"
#include "Model/Project.h"

namespace Controller
{
	class OCTDispatcher;
	class Merger;
}
namespace Model
{
	class Project;
}

namespace Controller
{
	class Merger
	{
		public: Controller::OCTDispatcher* m_merger;

		public: Merger();

        public: void createXML(Model::Project *project);

		public: void createMKVFile();
	};
}

#endif
