#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QMap>
#include "Parameter.h"

namespace Model {
    class Parameter;
    class Parameters;
}

namespace Model {
    class Parameters
    {
        private:
            static QMap<QString, Parameter *> m_audioParameters;
            static QMap<QString, Parameter *> m_videoParameters;
            static QMap<QString, Parameter *> m_subtitleParameters;

        public:
            static Parameter *getVideoParameter(QString key);
            static Parameter *getAudioParameter(QString key);
            static Parameter *getSubtitleParameter(QString key);
            static void init();
    };
}
#endif // PARAMETERS_H
