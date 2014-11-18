#include <exception>
using namespace std;

#include "Model/Database.h"

Model::Database::Database() {
}

Model::Database::Database(const Database& db) {
    m_userKey = db.m_userKey;
    m_depot = db.m_depot;
}

Model::Database& Model::Database::operator=(const Database& db) {
    if ( this != &db ) {
        m_userKey = db.m_userKey;
        m_depot = db.m_depot;
    }
    return *this;
}

Model::Database::~Database() {}

int Model::Database::sendRequest(QString request) {
	throw "Not yet implemented";
}

ostream& Model::Database::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Database::operator << (istream& o){
    throw "Not yet implemented";
}
