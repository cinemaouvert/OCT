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
                  Video *v = new Video(stream);
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

QList<Model::Data*>* Model::File::getDatas() {
    return m_datas;
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
