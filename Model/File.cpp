#include <QDomDocument>
#include <exception>
using namespace std;

#include "Model/File.h"
#include "Model/Data.h"




Model::File::File() {}

Model::File::File(QString filePath, QString info) {
    m_filePath = filePath;
    m_name = filePath;

    QDomDocument doc;
    doc.setContent(info);
    if(!doc.isNull()){
        QDomElement root = doc.documentElement();
        if(!root.isNull()){
            QDomNodeList streams = root.elementsByTagName("stream");
            for (int i=0;i<streams.count();i++){
                //-----------------------STREAM------------------------//
                QDomNode stream = streams.item(i);
                QDomNamedNodeMap tab = stream.attributes();

                //-----------------------TYPE------------------------//
                QDomNode nodeCodecType = tab.namedItem("codec_type");
                QString type = nodeCodecType.nodeValue();
                if(type == "video"){
                  Video *v =  genereVideo(stream);
                  foreach (QString s, *(v->getCommand())) {
                        qDebug() <<"TEST : " + s;
                  }

                }
                if(type == "audio"){
                    qDebug() << "audio";

                }
                if(type == "subtitle"){
                    qDebug() << "sous-titre";
                }
                if(type == "attachment"){
                    qDebug() << "attachment";
                }

            }
        }
    }
}

Model::File::File(const File& f) {
    m_name = f.m_name;
    m_filePath = f.m_filePath;
}

Model::File& Model::File::operator=(const File& f) {
    if ( this != &f ) {
        m_name = f.m_name;
        m_filePath = f.m_filePath;
    }
    return *this;
}

Model::File::~File() {}

QList<Model::Data*> Model::File::getDatas() {
	throw "Not yet implemented";
}

QString Model::File::getName() {
	return this->m_name;
}

Model::Video* Model::File::genereVideo(QDomNode stream)
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
    Video *v = new Video(UID);
    Parameter *pCodecName = Video::getStaticParameter("codec_name");
    pCodecName->setValue(codecName);
    v->setParameter("codec_name",pCodecName);

    if(language != ""){
        Parameter *pLanguage = Video::getStaticParameter("language");
        pLanguage->setValue(language);
        v->setParameter("language",pLanguage);
    }

    Parameter *pDefault = Video::getStaticParameter("default");
    pDefault->setValue(isDefault);
    v->setParameter("default",pDefault);

    Parameter *pResolution = Video::getStaticParameter("resolution");
    pResolution->setValue(resolution);
    v->setParameter("resolution",pResolution);

    Parameter *pFrameRate = Video::getStaticParameter("r_frame_rate");
    pFrameRate->setValue(frameRate);
    v->setParameter("r_frame_rate",pFrameRate);

    return v;
}

Model::Audio *Model::File::genereAudio(QDomNode stream)
{
    qDebug() << "Audio";
    QDomNamedNodeMap tab = stream.attributes();
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


    /* language
    codec
    freq
    cannaux
    resolution
    */
}

ostream& Model::File::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::File::operator << (istream& o){
    throw "Not yet implemented";
}
