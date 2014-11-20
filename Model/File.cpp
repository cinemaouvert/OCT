#include <QDomDocument>
#include <exception>
using namespace std;

#include "Model/File.h"
#include "Model/Data.h"
#include "Model/parameters.h"

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
                qDebug() << "------------stream-------------------";
                //new stream // get attribute
                //Stream *theStream;
                QDomNode stream = streams.item(i);
                QDomNamedNodeMap tab = stream.attributes();

                QDomNode nodeCodecType = tab.namedItem("codec_type");
                QString type = nodeCodecType.nodeValue();
                qDebug() << type;


                qDebug() << "------------attributes-------------------";
                for(int j=0;j<tab.count();j++)
                {
                    QDomNode n = tab.item(j);
                    qDebug() << n.nodeName() << " : " <<  n.nodeValue();
                   /* Parameter *tmpParam = Parameters.getVideoParameter(n.nodeName());
                    if(param != NULL){
                        Parameter *param = new Parameter(tmpParam);
                        param->setValue(n.nodeValue());
                        theStream->setParameter(n.nodeName(),param);
                    }*/


                }
                qDebug() << "------------Dispositoion-------------------";
                QDomElement e = stream.toElement();
                QDomNodeList disposition = e.elementsByTagName("disposition");
                for (int j=0;j<disposition.count();j++){
                    QDomNode n = tab.item(j);
                    qDebug() << n.nodeName() << " : " <<  n.nodeValue();
                }
                qDebug() << "------------TAG-------------------";
                QDomNodeList tag = e.elementsByTagName("tag");
                for (int j=0;j<tag.count();j++){
                    QDomNode n = tab.item(j);
                    qDebug() << n.nodeName() << " : " <<  n.nodeValue();

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

ostream& Model::File::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::File::operator << (istream& o){
    throw "Not yet implemented";
}
