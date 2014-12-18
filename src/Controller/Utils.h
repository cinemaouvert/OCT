#include <qstring.h>

#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
    static QString convertFract(QString var);
    static QString bpsToKbps(QString var);
};

#endif // UTILS_H
