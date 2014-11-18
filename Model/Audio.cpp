#include <exception>
using namespace std;

#include "Model/Audio.h"
#include "Model/Stream.h"

Model::Audio::Audio(QString UID) {
}

Model::Audio::Audio(Model::Audio& copy) {
}

ostream& Model::Audio::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Audio::operator << (istream& o){
    throw "Not yet implemented";
}
