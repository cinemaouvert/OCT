#ifndef CONFIGOCT_H
#define CONFIGOCT_H

#include <QObject>

namespace configOCT {
    const QString NAME = "OCT";

    const QString URL = "http://cinemaouvert.fr/";

    const QString VERSION = "v0.1-alpha";

    #if defined(Q_OS_MAC)
        const QString LINK_UPDATE = NAME + "macos/latest/";
        const QString NAME_INSTALLER = "";
    #elif defined(Q_OS_WIN)
        const QString LINK_UPDATE = NAME + "windows/latest/";
        const QString NAME_INSTALLER = "";
    #elif defined(Q_OS_UNIX)
        const QString LINK_UPDATE = NAME + "unix/latest/";
        const QString NAME_INSTALLER = "";
    #endif
}

#endif // CONFIGOCT_H
