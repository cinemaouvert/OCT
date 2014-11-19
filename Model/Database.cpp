#include <exception>
using namespace std;

#include "Model/Database.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QSslConfiguration>
#include "configOCT.h"

Model::Database::Database(QString userKey, QString depot) {
    this->m_userKey = userKey;
    this->m_depot = depot;
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

int Model::Database::sendRequest(QByteArray jsonString) {
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    QUrl url(this->m_depot);
    QNetworkRequest request(url);

    request.setRawHeader("User-Agent", configOCT::NAME.toStdString().c_str());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    qDebug() << jsonString;
    qDebug() << postDataSize;

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();

    QEventLoop loop;
    QNetworkReply* reply = networkManager->post(request, jsonString);
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    reply->deleteLater();

    return statusCodeV.toInt();
}

ostream& Model::Database::operator >> (ostream& o){
    throw "Not yet implemented";
}

istream& Model::Database::operator << (istream& o){
    throw "Not yet implemented";
}
