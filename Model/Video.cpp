#include <exception>
using namespace std;

#include "Model/Video.h"
#include "Model/Stream.h"

#include <QDebug>


QMap<QString, Model::Parameter *> Model::Video::m_staticParameters;
Model::Video::Video(){
    this->m_parameters = new QMap<QString,Parameter*>();



}

Model::Video::Video(QString uid){
    this->m_parameters = new QMap<QString,Parameter*>();



    this->m_uID = uid;
}

Model::Video::Video(const Model::Video & copy){
    this->m_uID = copy.m_uID;
    this->m_additionalCommand = copy.m_additionalCommand;
    this->m_parameters = new QMap<QString,Parameter*>(*(copy.m_parameters));
}

Model::Video &Model::Video::Video::operator=(const Model::Video &o)
{
    if(this != &o){
        this->m_uID = o.m_uID;
        this->m_additionalCommand = o.m_additionalCommand;
        QMap<QString,Parameter*> *param(o.m_parameters) ;
        this->m_parameters = param;
    }
    return *this;
}

ostream& Model::Video::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Video::operator << (istream& o){
    throw "Not yet implemented";
}

Model::Video::~Video()
{
    if (this->m_parameters != NULL)
        delete(this->m_parameters);
}

Model::Parameter *Model::Video::getStaticParameter(QString key)
{
    return Video::m_staticParameters.value(key);
}

void Model::Video::initStaticParameters()
{
    Parameter *v_codecNameParam = new Parameter("-vcodec %1","This is the codec of the video stream","");
    m_staticParameters.insert("codec_name",v_codecNameParam);

    Parameter *v_language = new Parameter("-metadata:s:v:%2 language=%1","This is the language of the stream","");
    m_staticParameters.insert("language",v_language);

    Parameter *v_isDefault = new Parameter("-metadata:s:v:%2 default-flag=%1","This indicates if the stream is tagged as the default one","1");
    m_staticParameters.insert("default",v_isDefault);

    Parameter *v_resolution = new Parameter("-vf scale=%1","This is the resolution of the video stream (AAAxBBB)","");
    v_resolution->SetNoSpaceForNext();
    m_staticParameters.insert("resolution",v_resolution);

    Parameter *v_forceAspect = new Parameter("force_original_aspect_ratio=%1","Enable decreasing or increasing output video width or height if necessary to keep the original aspect ratio. Possible values: disable,decrease,increase","");
    m_staticParameters.insert("forceAspect",v_forceAspect);

    Parameter *v_frameRate = new Parameter("-r %1","This is the frame rate (in frame by second)","24");
    m_staticParameters.insert("r_frame_rate",v_frameRate);

    Parameter *v_averageBitRate= new Parameter("-b:v %1 -bufsize %1","This is the average bit rate (in frame by second)","");
    m_staticParameters.insert("sample_rate",v_averageBitRate);

    Parameter *v_filter= new Parameter("-filter:v %1","This is the video filter can be (yadif for deinterlace, ))","");
    m_staticParameters.insert("deinterlace",v_filter);
}
