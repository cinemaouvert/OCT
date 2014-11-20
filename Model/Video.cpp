#include <exception>
using namespace std;

#include "Model/Video.h"
#include "Model/Stream.h"

#include <QDebug>
#include <QSettings>


QMap<QString, Model::Parameter *> Model::Video::m_staticParameters;
Model::Video::Video(){
    this->m_parameters = new QMap<QString,Parameter*>();



}

Model::Video::Video(QDomNode stream)
{
    qDebug() << "video";
    QDomNamedNodeMap tab = stream.attributes();
    //-----------------------UID------------------------//
    QDomNode uidNode = tab.namedItem("index");
    QString UID = uidNode.nodeValue();
    qDebug() << UID;
    //-----------------------CODEC-NAME------------------------//
    QDomNode nodeCodecName = tab.namedItem("codec_name");
    QString codecName = nodeCodecName.nodeValue();
    qDebug() << codecName;
    //-----------------------LANGUAGE------------------------//
    QDomNodeList tagList = stream.toElement().elementsByTagName("tag");
    qDebug() << tagList.count();

    QString tagKey ="";
    int i = 0;
    while(tagKey != "language" && i<tagList.count()){
        tagKey = tagList.at(i).attributes().namedItem("key").nodeValue();
        i++;
    }
    QString language = "";
    if(tagKey == "language")
        language = tagList.at(i-1).attributes().namedItem("value").nodeValue();
    //-----------------------IS-DEFAULT------------------------//
    QDomNode disposition = stream.toElement().elementsByTagName("disposition").item(0);
    QString isDefault = disposition.attributes().namedItem("default").nodeValue();
    qDebug() << isDefault;
    //-----------------------RESOLUTION------------------------//
    QDomNode nodeWidth = tab.namedItem("width");
    QString width = nodeWidth.nodeValue();
    qDebug() << width;

    QDomNode nodeHeight = tab.namedItem("height");
    QString height = nodeHeight.nodeValue();
    qDebug() << height;

    QString resolution = width + "x" + height;
    qDebug() << resolution;
    //-----------------------FRAME-RATE------------------------//   //!\\  A CONVERTIR
    QDomNode nodeFrameRate = tab.namedItem("r_frame_rate");
    QString frameRate = nodeFrameRate.nodeValue();
    qDebug() << frameRate;

    //-----------------------VIDEO-BUILD------------------------//
    this->m_uID = UID;
    this->m_parameters = new QMap<QString,Parameter*>();

    Parameter *pCodecName = Video::getStaticParameter("codec_name");
    pCodecName->setValue(codecName);
    this->setParameter("codec_name",pCodecName);

    if(language != ""){
        Parameter *pLanguage = Video::getStaticParameter("language");
        pLanguage->setValue(language);
        this->setParameter("language",pLanguage);
    }

    Parameter *pDefault = Video::getStaticParameter("default");
    pDefault->setValue(isDefault);
    this->setParameter("default",pDefault);

    Parameter *pResolution = Video::getStaticParameter("resolution");
    pResolution->setValue(resolution);
    this->setParameter("resolution",pResolution);

    Parameter *pFrameRate = Video::getStaticParameter("r_frame_rate");
    pFrameRate->setValue(frameRate);
    this->setParameter("r_frame_rate",pFrameRate);

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

    Parameter *param = new Parameter(*(Video::m_staticParameters.value(key)));
    return param;
}

void Model::Video::initStaticParameters()
{
    Parameter *codecNameParam = new Parameter("-vcodec","This is the codec of the video stream","%1");
    m_staticParameters.insert("codec_name",codecNameParam);

    Parameter *language = new Parameter("-metadata:s:v:%1","This is the language of the stream","language=%1");
    m_staticParameters.insert("language",language);

    Parameter *isDefault = new Parameter("-metadata:s:v:%1","This indicates if the stream is tagged as the default one","default-flag=%1");
    m_staticParameters.insert("default",isDefault);

    Parameter *resolution = new Parameter("-vf","This is the resolution of the video stream (AAAxBBB)","scale=%1");
    resolution->SetNoSpaceForNext();
    m_staticParameters.insert("resolution",resolution);

    Parameter *forceAspect = new Parameter("","Enable decreasing or increasing output video width or height if necessary to keep the original aspect ratio. Possible values: disable,decrease,increase","force_original_aspect_ratio=%1");
    m_staticParameters.insert("forceAspect",forceAspect);

    Parameter *frameRate = new Parameter("-r","This is the frame rate (in frame by second)","%1");
    m_staticParameters.insert("r_frame_rate",frameRate);

    Parameter *averageBitRate= new Parameter("-b:v %1 -bufsize %1","This is the average bit rate","");
    m_staticParameters.insert("bitRate",averageBitRate);

    Parameter *filter= new Parameter("-filter:v","This is the video filter can be (yadif for deinterlace, ))","%1");
    m_staticParameters.insert("deinterlace",filter);

    Parameter *startPoint= new Parameter("-ss","Start point of the video","%1");
    m_staticParameters.insert("start_pts",startPoint);

    Parameter *endPoint= new Parameter("-ss","End point of the video","%1");
    m_staticParameters.insert("start_pts",endPoint);

    Parameter *crop= new Parameter("-filter:v","Crop the video (w:h:x:y)","%1");
    m_staticParameters.insert("crop",crop);
}
