#include <exception>
using namespace std;

#ifndef __Model__File_h__
#define __Model__File_h__

#include <QString>
#include <QList>

#include "Model/Serializable.h"
#include "Model/Data.h"
#include "qdebug.h"
namespace Model
{
	class Data;
	class File;
    class Serializable;
}

namespace Model
{
    class File : public Model::Serializable
	{
        private:
            QString m_name;
            QString m_filePath;
            Model::Data* m___n;
        public:
            File();
            File(QString filePath, QString info);
            File(File const& f);
            File& operator=(File const& f);
            virtual ~File();

            QList<Model::Data*> getDatas();
            QString getName();
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);

	};
}

#endif
