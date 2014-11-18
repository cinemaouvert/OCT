#include <exception>
using namespace std;

#include "Model/Video.h"
#include "Model/Stream.h"

Model::Video::Video(QString UID) {
}

Model::Video::Video(Model::Video& copy) {
}

ostream& Model::Video::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Video::operator << (istream& o){
    throw "Not yet implemented";
}
