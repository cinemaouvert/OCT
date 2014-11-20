#include <exception>
using namespace std;

#ifndef __Model__File_h__
#define __Model__File_h__

#include <QString>
#include <QList>
#include <qdom.h>

#include "Model/Serializable.h"
#include "Model/Data.h"
#include "Audio.h"
#include "Video.h"
#include "qdebug.h"
namespace Model
{
	class Data;
	class File;
    class Serializable;
    class Parameters;
}

namespace Model
{
    class File : public Model::Serializable
	{
        private:
            QString m_name;
            QString m_filePath;
            QList<Model::Data*> *m_datas;
            Video* genereVideo(QDomNode stream);
        public:
            File();
            File(QString filePath, QString info);
            File(File const& f);
            File& operator=(File const& f);
            virtual ~File();

            QList<Model::Data*>* getDatas();
            QString getName();
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);

	};
}

#endif
