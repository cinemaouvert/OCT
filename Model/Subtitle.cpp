#include <exception>
using namespace std;

#include "Model/Subtitle.h"
#include "Model/Stream.h"

Model::Subtitle::Subtitle(QString UID) {
}

Model::Subtitle::Subtitle(Model::Subtitle& copy) {
}

ostream& Model::Subtitle::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Subtitle::operator << (istream& o){
    throw "Not yet implemented";
}
