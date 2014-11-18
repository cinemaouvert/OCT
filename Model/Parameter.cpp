#include <exception>
using namespace std;

#include "Model/Parameter.h"
void Model::Parameter::setValue(QString value) {
	throw "Not yet implemented";
}

Model::Parameter::Parameter() {
}

ostream& Model::Parameter::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Parameter::operator << (istream& o){
    throw "Not yet implemented";
}
