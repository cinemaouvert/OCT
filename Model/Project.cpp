#include <exception>
#include <vector>
using namespace std;

#include "Model/Project.h"
#include "Model/Attachment.h"
#include "Model/Information.h"

Model::Project::Project() : m_attachments (NULL),m_informations(NULL), m_fileList(NULL)
{
    this->m_attachments = new QList<Model::Attachment*>();
    this->m_informations = new QList<Model::Information*>();
    this->m_fileList = new QList<Model::File*>();
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
        //m_attachments = new QList<Model::Attachment*>(*project.m_attachments);
        m_attachments = new QList<Model::Attachment*>();
        m_attachments = project.m_attachments;
        //m_informations = new QList<Model::Information*>(*project.m_informations);
        m_informations = new QList<Model::Information*>();
        m_informations = project.m_informations;
        //m_fileList = new QList<Model::File*>(*project.m_fileList);
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
    //m_attachments = new QList<Model::Attachment*>(*project.m_attachments);
    m_attachments = project.m_attachments;
    //m_informations = new QList<Model::Information*>(*project.m_informations);
    m_informations = project.m_informations;
    //m_fileList = new QList<Model::File*>(*project.m_fileList);
    m_fileList = project.m_fileList;
}

void Model::Project::load() {
	throw "Not yet implemented";
}

void Model::Project::save() {
	throw "Not yet implemented";
}

ostream& Model::Project::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Project::operator << (istream& o){
    throw "Not yet implemented";
}

void Model::Project::addFileToList(Model::File *file)
{
    if(m_fileList == NULL)
        this->m_fileList = new QList<Model::File*>();

    this->m_fileList->push_back(file);
}

void Model::Project::addInformations(Model::Information *information)
{
    if(m_informations == NULL)
        this->m_informations = new QList<Model::Information*>();

    this->m_informations->push_back(information);
}

void Model::Project::addAttachment(Model::Attachment *attachment)
{
    if(m_attachments == NULL)
        this->m_attachments = new QList<Model::Attachment*>();

    this->m_attachments->push_back(attachment);
}

QString Model::Project::name() const
{
    return m_name;
}

void Model::Project::setName(const QString &name)
{
    m_name = name;
}

QList<Model::File *> *Model::Project::fileList() const
{
    return m_fileList;
}

QList<Model::Information *> *Model::Project::informations() const
{
    return m_informations;
}

bool Model::Project::createMagnet() const
{
    return m_createMagnet;
}

void Model::Project::setCreateMagnet(bool createMagnet)
{
    m_createMagnet = createMagnet;
}

QList<Model::Attachment *> *Model::Project::attachments() const
{
    return m_attachments;
}

QString Model::Project::xmlFilePath() const
{
    return m_xmlFilePath;
}

void Model::Project::setXmlFilePath(const QString &xmlFilePath)
{
    m_xmlFilePath = xmlFilePath;
}

