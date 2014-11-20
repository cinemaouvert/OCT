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
            void load();
            void save();
            virtual ostream& operator >> (ostream& o);
            virtual istream& operator << (istream& o);

            QString name() const;
            void setName(const QString &name);

            QList<Model::File *> *fileList() const;
            void addFileToList(Model::File *fileList);

            QList<Model::Information *> *informations() const;
            void addInformations(Model::Information *information);

            bool createMagnet() const;
            void setCreateMagnet(bool createMagnet);

            QList<Model::Attachment *> *attachments() const;
            void addAttachment(Model::Attachment *attachment);

            QString xmlFilePath() const;
            void setXmlFilePath(const QString &xmlFilePath);
    };
}

#endif
