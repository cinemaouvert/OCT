#include <exception>
#include <vector>
using namespace std;

#include "Model/Project.h"
#include "Model/Attachment.h"
#include "Model/Information.h"

Model::Project::Project() : m_attachments (NULL),m_informations(NULL), m_fileList(NULL){
}

Model::Project::~Project()
{
    if(this->m_attachments != NULL)
        delete this->m_attachments;
    if(this->m_fileList != NULL)
        delete this->m_fileList;
    if(this->m_informations != NULL)
        delete this->m_informations;
}

Model::Project &Model::Project::operator=(const Model::Project &project)
{
    if (this != &project) {
        m_name = project.m_name;
        m_xmlFilePath = project.m_xmlFilePath;
        m_createMagnet = project.m_createMagnet;
        m_attachments = new QList<Model::Attachment*>();
        m_attachments = project.m_attachments;
        m_informations = new QList<Model::Information*>();
        m_informations = project.m_informations;
        m_fileList = new QList<Model::File*>();
        m_fileList = project.m_fileList;
    }
    return *this;
}

Model::Project::Project(const Model::Project &project)
{
    m_name = project.m_name;
    m_xmlFilePath = project.m_xmlFilePath;
    m_createMagnet = project.m_createMagnet;
    m_attachments = new QList<Model::Attachment*>(*project.m_attachments);
    //m_attachments = project.m_attachments;
    m_informations = new QList<Model::Information*>(*project.m_informations);
    //m_informations = project.m_informations;
    m_fileList = new QList<Model::File*>(*project.m_fileList);
    //m_fileList = project.m_fileList;
}

void Model::Project::getFiles() {
	throw "Not yet implemented";
}

void Model::Project::load() {
	throw "Not yet implemented";
}

void Model::Project::save() {
	throw "Not yet implemented";
}

QString Model::Project::getXML() {
	throw "Not yet implemented";
}

void Model::Project::setXML(QString filepath) {
	throw "Not yet implemented";
}

QList<Model::Information*> Model::Project::getInformations() {
	throw "Not yet implemented";
}

bool Model::Project::getCreateMagnet() {
	return this->m_createMagnet;
}

void Model::Project::setCreateMagnet(bool hasToCreateMagnet) {
	throw "Not yet implemented";
}

ostream& Model::Project::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Project::operator << (istream& o){
    throw "Not yet implemented";
}

