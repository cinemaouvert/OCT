#include <exception>
using namespace std;

#include "Model/Database.h"
#include "Controller/Exporter.h"

Model::Database::Database() {
}

int Model::Database::sendRequest(QString request) {
	throw "Not yet implemented";
}

ostream& Model::Database::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Database::operator << (istream& o){
    throw "Not yet implemented";
}
