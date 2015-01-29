#include <qstring.h>

#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
    static QString convertFract(QString var);
    static QString bpsToKbps(QString var);
    static QString sha1File(QString pathFile);
    static QString md5File(QString pathFile);
private:
    static QByteArray readAllFile(QString pathFile);
};

#endif // UTILS_H
