#include "Utils.h"
#include <QDebug>


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
