#include <exception>
using namespace std;

#include <QString>
#include <QList>
#ifndef __Model__File_h__
#define __Model__File_h__

#include "Model/Data.h"

namespace Model
{
	class Data;
	class File;
}

namespace Model
{
	class File
	{
		private: QString m_name;
		private: QString m_filePath;
		public: Model::Data* m___n;

		public: void FIle(QString filePath, QString info);

        public: QList<Model::Data*> getDatas();

		public: QString getName();
	};
}

#endif
