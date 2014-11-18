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
}

namespace Model
{
	class Project: public Model::Serializable
	{
		private: QString m_name;
		private: QString m_xmlFilePath;
		private: bool m_createMagnet;
        public: QList<Model::Attachment*> m_attachments;
        public: QList<Model::Information*> m_informations;

		public: Project();

		public: void getFiles();

		public: void load();

		public: void save();

		public: QString getXML();

		public: void setXML(QString filepath);

        public: QList<Model::Information*> getInformations();

		public: bool getCreateMagnet();

		public: void setCreateMagnet(bool hasToCreateMagnet);
	};
}

#endif
