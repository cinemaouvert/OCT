#ifndef CONFIGOCT_H
#define CONFIGOCT_H

#include <QObject>

namespace configOCT {
    const QString URL = "http://cinemaouvert.fr/";
    const QString VERSION = "v0.1-alpha";

    #if defined(Q_OS_MAC)
        const QString LINK_UPDATE = "macos/latest/";
        const QString NAME_INSTALLER = "oppFinal.pkg";
    #elif defined(Q_OS_WIN)
        const QString LINK_UPDATE = "windows/latest/";
        const QString NAME_INSTALLER = "setup_opp.exe";
    #elif defined(Q_OS_UNIX)
        const QString LINK_UPDATE = "unix/latest/";
        const QString NAME_INSTALLER = "OPP_1.0-stable_amd64.deb";
    #endif
}

#endif // CONFIGOCT_H
