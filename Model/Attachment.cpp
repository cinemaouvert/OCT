#include <exception>
using namespace std;

#include "Model/Attachment.h"
#include "Model/Serializable.h"

Model::Attachment::Attachment(QString filepath) {
}

ostream& Model::Attachment::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Attachment::operator << (istream& o){
    throw "Not yet implemented";
}
