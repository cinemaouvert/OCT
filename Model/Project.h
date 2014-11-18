#include <exception>
using namespace std;

#ifndef __Model__Project_h__
#define __Model__Project_h__

#include <QString>
#include <QList>

// #include "Model/Attachment.h"
#include "Model/Information.h"
#include "Model/Serializable.h"

namespace Model
{
	class Attachment;
	class Information;
	// class Serializable;
	class Project;
    class File;
}

namespace Model
{
	class Project: public Model::Serializable
	{
        private:
            QString m_name;
            QString m_xmlFilePath;
            bool m_createMagnet;
            QList<Model::Attachment*> *m_attachments;
            QList<Model::Information*> *m_informations;
            QList<Model::File*> *m_fileList;
        public:
            Project();
            virtual ~Project();
            Project & operator=(const Project &project);
            Project(Project const &project);
            void getFiles();
            void load();
            void save();
            QString getXML();
            void setXML(QString filepath);
            QList<Model::Information*> getInformations();
            bool getCreateMagnet();
            void setCreateMagnet(bool hasToCreateMagnet);
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);
	};
}

#endif
