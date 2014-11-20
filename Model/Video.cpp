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

QString Model::Video::getCommand()
{
    return NULL;
}

Model::Parameter *Model::Video::getStaticParameter(QString key)
{

    Parameter *param = new Parameter(*(Video::m_staticParameters.value(key)));
    return param;
}

void Model::Video::initStaticParameters()
{
    Parameter *codecNameParam = new Parameter("-vcodec %1","This is the codec of the video stream","");
    m_staticParameters.insert("codec_name",codecNameParam);

    Parameter *language = new Parameter("-metadata:s:v:%2 language=%1","This is the language of the stream","");
    m_staticParameters.insert("language",language);

    Parameter *isDefault = new Parameter("-metadata:s:v:%2 default-flag=%1","This indicates if the stream is tagged as the default one","1");
    m_staticParameters.insert("default",isDefault);

    Parameter *resolution = new Parameter("-vf scale=%1","This is the resolution of the video stream (AAAxBBB)","");
    resolution->SetNoSpaceForNext();
    m_staticParameters.insert("resolution",resolution);

    Parameter *forceAspect = new Parameter("force_original_aspect_ratio=%1","Enable decreasing or increasing output video width or height if necessary to keep the original aspect ratio. Possible values: disable,decrease,increase","");
    m_staticParameters.insert("forceAspect",forceAspect);

    Parameter *frameRate = new Parameter("-r %1","This is the frame rate (in frame by second)","24");
    m_staticParameters.insert("r_frame_rate",frameRate);

    Parameter *averageBitRate= new Parameter("-b:v %1 -bufsize %1","This is the average bit rate","");
    m_staticParameters.insert("bitRate",averageBitRate);

    Parameter *filter= new Parameter("-filter:v %1","This is the video filter can be (yadif for deinterlace, ))","");
    m_staticParameters.insert("deinterlace",filter);

    Parameter *startPoint= new Parameter("-ss %1","Start point of the video","");
    m_staticParameters.insert("start_pts",startPoint);

    Parameter *endPoint= new Parameter("-ss %1","End point of the video","");
    m_staticParameters.insert("start_pts",endPoint);
}
