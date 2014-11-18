#include <exception>
using namespace std;

#include "Model/Attachment.h"
#include "Model/Serializable.h"

Model::Attachment::Attachment() {
    m_filepath = "";
}

Model::Attachment::Attachment(QString filepath) {
    m_filepath = filepath;
}

Model::Attachment::Attachment(const Attachment& a) {
    m_filepath = a.m_filepath;
}

Model::Attachment& Model::Attachment::operator=(const Attachment& a) {
    if ( this != &a ) {
        m_filepath = a.m_filepath;
    }
    return *this;
}

Model::Attachment::~Attachment() {
    m_filepath = "";
}

ostream& Model::Attachment::operator >> (ostream& o) {
    throw "Not yet implemented";
}

istream& Model::Attachment::operator << (istream& o) {
    throw "Not yet implemented";
}
