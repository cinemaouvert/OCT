#include <exception>
using namespace std;

#include "Model/Audio.h"
#include "Model/Stream.h"

Model::Audio::Audio() {
    m_uID = "";
}

Model::Audio::Audio(QString uID) {
    m_uID = uID;
}

Model::Audio::Audio(const Audio& a) {
    m_uID = a.m_uID;
}

Model::Audio& Model::Audio::operator=(const Audio& a) {
    if ( this != &a ) {
        m_uID = a.m_uID;
    }
    return *this;
}

Model::Audio::~Audio() {}

ostream& Model::Audio::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Audio::operator << (istream& o){
    throw "Not yet implemented";
}
