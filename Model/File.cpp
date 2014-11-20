#include <QDomDocument>
#include <exception>
using namespace std;

#include "Model/File.h"
#include "Model/Data.h"




Model::File::File() {}

Model::File::File(QString filePath, QString info) : m_datas(NULL) {
    m_filePath = filePath;
    m_name = filePath;
    m_datas = new QList<Data*>();

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

                Stream *s;
                switch (Model::Stream::getEnumValue(type)){
                    case Model::Stream::VIDEO:
                            s = new Video(stream);
                            break;
                    case Model::Stream::AUDIO:
                            break;
                    case Model::Stream::SUBTITLE:
                            break;
                    case Model::Stream::ATTACHMENT:
                            break;
                }

                Data* theData;
                theData= new Data();

                theData->setOldStream(s);
                this->m_datas->push_back(theData);
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
        m_datas = f.m_datas;
    }
    return *this;
}

Model::File::~File() {
    if(this->m_datas != NULL)
        delete this->m_datas;
}

QList<Model::Data*>* Model::File::getDatas() {
    return m_datas;
}

QStringList *Model::File::getCommandLine()
{
    QStringList *stringList;
    stringList = new QStringList();
    *stringList << "-i" << this->m_filePath;
    foreach (Data *data, *getDatas()) {
        if(data->hasToBeTranscoded()){
            (*stringList) << *(data->generateCommandLine());
        }
    }
    *stringList << "E:\\M2\\Projet\\Test mkvtoolnix\\test3.mkv";
    return stringList;
}

QString Model::File::getName() {
	return this->m_name;
}

ostream& Model::File::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::File::operator << (istream& o){
    throw "Not yet implemented";
}
