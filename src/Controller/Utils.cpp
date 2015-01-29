#include "Utils.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QDialog>
#include <QFile>

QString Utils::convertFract(QString var)
{
    QString nomi = "";
    QString denomi = "";

    int i = 0;
    while (var.at(i) != '/' && var.size()>i){
        nomi += var.at(i);
        i++;
    }
    if(var.at(i) == '/'){
        i++;
        while(var.size()>i){
            denomi += var.at(i);
            i++;
        }
        if(denomi.toInt()==0)
            return nomi;
        else{
            qDebug() << "ici! ";
            int fract =  nomi.toInt() / denomi.toInt();
            return QString::number(fract);
        }
    }
    else return nomi;

}

QString Utils::bpsToKbps(QString var)
{
    return QString::number(var.toInt()/1000);
}

QString Utils::md5File(QString pathFile){
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(readAllFile(pathFile));
    QByteArray hah = md5.result();
    return hah.toHex();
}
QString Utils::sha1File(QString pathFile){
    QCryptographicHash sha1(QCryptographicHash::Sha1);
    sha1.addData(readAllFile(pathFile));
    QByteArray hah = sha1.result();
    return hah.toHex();
}

QByteArray Utils::readAllFile(QString pathFile){
    QFile file(pathFile);
    file.open(QIODevice::ReadOnly);
    return file.readAll();
}
